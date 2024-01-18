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

#define LED_ON(x) LED##x##_ON
#define LED_OFF(x) LED##x##_OFF
#define LED_ON_OFF(led, duration) \
    do { \
        ztimer_sleep(ZTIMER_MSEC, duration); \
        LED_ON(led); \
        ztimer_sleep(ZTIMER_MSEC, duration); \
        LED_OFF(led); \
    } while (0)

static gpio_t buttons[] = { BTN0_PIN, BTN1_PIN, BTN2_PIN, BTN3_PIN };
static gpio_mode_t button_modes[] = { BTN0_MODE, BTN1_MODE, BTN2_MODE, BTN3_MODE };
static gpio_t leds[] = { LED0_PIN, LED1_PIN, LED2_PIN, LED3_PIN };

char thread_stack[THREAD_STACKSIZE_LARGE];

kernel_pid_t main_pid;
kernel_pid_t thread_pid;

static void on_button_pressed(void *_arg)
{
    msg_t msg;
    msg.content.value = (int)_arg;
    msg_send_int(&msg, thread_pid);
}

static void init_gpios(void)
{
    for (unsigned i = 0; i < ARRAY_SIZE(buttons); i++) {
        gpio_init_int(buttons[i], button_modes[i], GPIO_RISING, on_button_pressed, (void*)(i + 1));   
        gpio_irq_disable(buttons[i]);     
    }

    for (unsigned i = 0; i < ARRAY_SIZE(leds); i++) {
        gpio_init(leds[i], GPIO_OUT);
    }
}
static void set_pid(void) {
    main_pid = thread_getpid();
}
static void enable_irqs(void) {
    for (unsigned i = 0; i < ARRAY_SIZE(buttons); i++) {   
        gpio_irq_enable(buttons[i]);     
    }
}
static void disable_irqs(void) {
    for (unsigned i = 0; i < ARRAY_SIZE(buttons); i++) {   
        gpio_irq_disable(buttons[i]);     
    }
}

void* record_buttons(void* _arg)
{
    thread_pid = thread_getpid();

    msg_t msg;

    int diff_scaler = (int)_arg;
    int* records = (int*)malloc((4 + diff_scaler)*sizeof(int)); //difficulty 1 => 4 integer(light), difficulty 2 => 6 integer(light)

    enable_irqs();
    int c = 0;
    for (int i = 0; i < 4 + diff_scaler; i++) {

        msg_receive(&msg);
        printf(" recieved: %d\n", (int)msg.content.value);
        records[c] = msg.content.value;
        c++;

    }

    msg_t res;
    res.content.ptr = (void*)records;
    msg_try_send(&res, main_pid);

    return NULL;
}

void* light_leds(int diff_scaler, uint32_t lights[]) {
    
    for(int i = 0; i < 4 + diff_scaler; i++) {
        switch (lights[i]) {
            case 1:
                LED_ON_OFF(0, 500);
                break;
            case 2:
                LED_ON_OFF(1, 500);
                break;
            case 3:
                LED_ON_OFF(2, 500);
                break;
            case 4:
                LED_ON_OFF(3, 500);
                break;
            default:
                puts("Wrong led number");
                break;
        }
    }

    return NULL;
}

int test_level(int difficulty) {  

    int diff_scaler = (difficulty == 1) ? 0: 2;

    msg_t msg;
    msg.content.ptr = NULL;

    uint32_t lights[4 + diff_scaler];;

    for (int i = 0; i < 4 + diff_scaler; i++) {
        lights[i] = random_uint32_range(1, 5);
    }
    //for(int i = 0; i < 4 + diff_scaler; i++) { // cheat mode
    //    printf("%lu", lights[i]);
    //}

    puts("Prepare yourself!\n");
    puts("3!\n");
    ztimer_sleep(ZTIMER_MSEC, 1000);
    puts("2!\n");
    ztimer_sleep(ZTIMER_MSEC, 1000);
    puts("1!\n");
    ztimer_sleep(ZTIMER_MSEC, 1000);
    puts("WATCH!\n");

    light_leds(diff_scaler, lights);
    
    int sc = 0;
    if(diff_scaler == 0) {
        puts("BEGIN! YOU HAVE 3 SECONDS\n");
    }
    else {
        puts("BEGIN! YOU HAVE 4 SECONDS\n");
        sc = 1000;
    }
    
    thread_create(thread_stack, sizeof(thread_stack), THREAD_PRIORITY_MAIN - 1, 
                    THREAD_CREATE_STACKTEST, record_buttons, (void*)diff_scaler, "Buttons push recorder");
    
    if(ztimer_msg_receive_timeout(ZTIMER_MSEC, &msg, 3000 + sc) < 0) {
        puts("--- You are too late :(\n");
        disable_irqs();
        return -1;
    }
    disable_irqs();

    int* response = (int*)msg.content.ptr;

    for (int i = 0; i < 4 + diff_scaler; i++) {
        if(response[i] == (int)lights[i]) {
            continue;
        }
        puts("--- You have failed!\n");
        return -1;
    }
    puts("--- You Have Won!!!\n");
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
        puts("Please choose a difficulty level or quit:\n\n1. Easy\n2. Hard\nq. Quit\n");
        fgets(inp, 2, stdin);
        
        if(inp[0] != 49 && inp[0] != 50 && inp[0] != 113) { // checks if the input is 1, 2 or q
            while ((n = getchar()) != '\n' && n != EOF);
            puts("Please enter 1 or 2!");
            continue;
        }
        else if (inp[0] == 113) {
            break;
        }
        difficulty = inp[0] - 48;

        test_level(difficulty);

        while ((n = getchar()) != '\n' && n != EOF);

    }
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
