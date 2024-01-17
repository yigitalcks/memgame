#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/time.h>

#include "periph/gpio.h"
#include "kernel_defines.h"
#include "thread.h"
#include "shell.h"
#include "ztimer.h"
#include "random.h"

static gpio_t buttons[] = { BTN0_PIN, BTN1_PIN, BTN2_PIN, BTN3_PIN };
//static gpio_mode_t button_modes[] = { BTN0_MODE, BTN1_MODE, BTN2_MODE, BTN3_MODE };
static gpio_t leds[] = { LED0_PIN, LED1_PIN, LED2_PIN, LED3_PIN };

char thread_stack[THREAD_STACKSIZE_LARGE];
char thread_stack_2[THREAD_STACKSIZE_LARGE];

mutex_t mut;
int indexes[10];
int is_given = 0;
kernel_pid_t main_pid;

static void init_gpios(void)
{
    for (unsigned i = 0; i < ARRAY_SIZE(buttons); i++) {
        gpio_init(buttons[i], GPIO_IN_PD);
    }

    for (unsigned i = 0; i < ARRAY_SIZE(leds); i++) {
        gpio_init(leds[i], GPIO_OUT);
    }
}

void* record_buttons(void* _arg)
{
    mutex_lock(&mut);

    int diff = (int)_arg;
    int records[10];

    int inp;
    int c = 0;
    while (1) {
        
        if(c >= 5*diff) {
            memcpy(indexes, records, sizeof(int)*5*diff);
            is_given = 1;
            mutex_unlock(&mut);
        }
        for (int i = 0; i < 4; i++) {
            inp = gpio_read(buttons[i]);
            if(inp > 0) {
                printf("%d", i);
                records[c] = i + 1;
                c++;
            }
        }
        ztimer_sleep(ZTIMER_MSEC, 1);
    }

    return NULL;
}

void* light_leds(int difficulty, uint32_t lights[]) {
    
    for(int i = 0; i < 5*difficulty; i++) {
        gpio_set(leds[lights[i] - 1]);
        ztimer_sleep(ZTIMER_MSEC, 500);
        gpio_write(leds[lights[i] - 1], 0);
    }
    
    return NULL;
}

int test_level(int difficulty) {  
    memset(indexes, '\0', sizeof(int) * 10);
    is_given = 0;

    ztimer_now_t t = ztimer_now(ZTIMER_MSEC);
    uint32_t lights[10];

    for (int i = 0; i < 5*difficulty; i++) {
        lights[i] = (t % 4) + 1;
        t = ztimer_now(ZTIMER_MSEC);
    }
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
    //ztimer_sleep(ZTIMER_SEC, 3);
    

    if(is_given == 0) {
        puts("You are too late :(\n");
        return -1;
    }
    
    for(int i = 0; i < 5*difficulty; i++) {
        printf("%d ", indexes[i]);
    }

    for (int i = 0; i < 5*difficulty; i++) {
        if(indexes[i] == (int)lights[i]) {
            continue;
        }
        puts("You have failed!\n");
        return -1;
    }
    puts("YOU HAVE WON!!!\n");
    return 0;
}

int main(void)
{
    init_gpios();
    mutex_init(&mut);  

    int diffc = 0;
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
        diffc = inp[0] - 48;

        test_level(diffc);

        while ((n = getchar()) != '\n' && n != EOF);

    }

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
