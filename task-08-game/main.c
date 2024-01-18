#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "board.h"
#include "periph/gpio.h"
#include "kernel_defines.h"
#include "shell.h"
#include "thread.h"
#include "ztimer.h"
#include "random.h"

#define MSG_QUEUE_SIZE 2

static gpio_t buttons[] = { BTN0_PIN, BTN1_PIN, BTN2_PIN, BTN3_PIN };
static gpio_mode_t button_modes[] = { BTN0_MODE, BTN1_MODE, BTN2_MODE, BTN3_MODE };
static gpio_t leds[] = { LED0_PIN, LED1_PIN, LED2_PIN, LED3_PIN };

char thread_stack[THREAD_STACKSIZE_LARGE];

kernel_pid_t main_pid;

static void init_gpios(void)
{
    for (unsigned i = 0; i < ARRAY_SIZE(buttons); i++) {
        if(gpio_init(buttons[i], button_modes[i]) < 0) {
            puts("Initialization Error");
        }
    }

    for (unsigned i = 0; i < ARRAY_SIZE(leds); i++) {
        gpio_init(leds[i], GPIO_OUT);
    }
}
static void set_pid(void) {
    main_pid = thread_getpid();
}

void* record_buttons(void* _arg)
{
    msg_t msg;

    int diff = (int)_arg;
    int* records = (int*)malloc(5*diff*sizeof(int)); //difficulty 1 => 5 integer(light), difficulty 2 => 10 integer(light)

    int inp;
    int c = 0;
    while (1) {
        if(c >= 5*diff) {
            printf(" mesaj gonderdim");
            msg.content.ptr = (void*)records;
            if(msg_send(&msg, main_pid) > 0) {
                printf("  Basarili");
            }
            break;
        }
        ztimer_sleep(ZTIMER_MSEC, 100);
        for (int i = 0; i < 4; i++) {
            ztimer_sleep(ZTIMER_MSEC, 1);
            inp = gpio_read(buttons[i]);
            if(inp == 0) {
                printf("%d ", i + 1);
                records[c] = i + 1;
                c++;
            }
        }
        
    }

    return NULL;
}

void* light_leds(int difficulty, uint32_t lights[]) {
    
        for(int i = 0; i < 5*difficulty; i++) {
                switch (lights[i]) {
            case 1:
                LED0_ON;
                ztimer_sleep(ZTIMER_MSEC, 500);
                LED0_OFF;
                break;
            case 2:
                LED1_ON;
                ztimer_sleep(ZTIMER_MSEC, 500);
                LED1_OFF;
                break;
            case 3:
                LED2_ON;
                ztimer_sleep(ZTIMER_MSEC, 500);
                LED2_OFF;
                break;
            case 4:
                LED3_ON;
                ztimer_sleep(ZTIMER_MSEC, 500);
                LED3_OFF;
                break;
            default:
                puts("Wrong light number");
                break;
            }
        }

    return NULL;
}

int test_level(int difficulty) {  

    msg_t msg;
    msg.content.ptr = NULL;

    //ztimer_now_t t = ztimer_now(ZTIMER_MSEC);
    uint32_t lights[10] = {1, 2, 3, 4, 1};

    //for (int i = 0; i < 5*difficulty; i++) {
    //    //lights[i] = (t % 4) + 1;
    //    //t = ztimer_now(ZTIMER_MSEC);
    //    lights[i] = random_uint32_range(1, 5);
    //}
    for(int i = 0; i < 5*difficulty; i++) {
        printf("%lu", lights[i]);
    }

    puts("Prepare yourself!\n");
    ztimer_sleep(ZTIMER_SEC, 1);
    puts("3!\n");
    ztimer_sleep(ZTIMER_SEC, 1);
    puts("2!\n");
    ztimer_sleep(ZTIMER_SEC, 1);
    puts("1!\n");
    ztimer_sleep(ZTIMER_SEC, 1);
    puts("WATCH!\n");

    light_leds(difficulty, lights);
    
    puts("BEGIN! YOU HAVE 3 SECONDS\n");
    thread_create(thread_stack, sizeof(thread_stack), THREAD_PRIORITY_MAIN - 1, 
                    THREAD_CREATE_STACKTEST, record_buttons, (void*)difficulty, "Buttons push recorder");
    
    if(ztimer_msg_receive_timeout(ZTIMER_MSEC, &msg, 3000) < 0) {
        puts("You are too late :(\n");
        return -1;
    }

    int* response = (int*)msg.content.ptr;
    
    for(int i = 0; i < 5*difficulty; i++) {
        printf("%d ", response[i]);
    }

    for (int i = 0; i < 5*difficulty; i++) {
        if(response[i] == (int)lights[i]) {
            continue;
        }
        puts("You have failed!\n");
        return -1;
    }
    puts("YOU HAVE WON!!!\n");
    free(msg.content.ptr);
    return 0;
}

int main(void)
{
    init_gpios();
    set_pid();

    int difficulty = 0;
    int n;
    char inp[2];

    puts("Welcome to The Memory Game\n");

    while (1) {
        puts("Please choose a difficulty level:\n\n1.)Easy\n2.)Hard\n\nDifficulty:");
        fgets(inp, 2, stdin);
        
        if(inp[0] != 49 && inp[0] != 50) { // checks if the input is a number
            while ((n = getchar()) != '\n' && n != EOF);
            puts("Please enter 1 or 2!");
            continue;
        }
        difficulty = inp[0] - 48;

        test_level(difficulty);

        while ((n = getchar()) != '\n' && n != EOF);

    }

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
