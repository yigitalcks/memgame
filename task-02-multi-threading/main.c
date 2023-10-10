#include <stdio.h>
#include <string.h>

#include "board.h"
#include "kernel_defines.h"
#include "periph/gpio.h"
#include "shell.h"
#include "thread.h"
#include "ztimer.h"

static gpio_t buttons[] = { BTN0_PIN, BTN1_PIN, BTN2_PIN, BTN3_PIN };
static gpio_mode_t button_modes[] = { BTN0_MODE, BTN1_MODE, BTN2_MODE, BTN3_MODE };
static gpio_t leds[] = { LED0_PIN, LED1_PIN, LED2_PIN, LED3_PIN };

/* Note: LEDs are already initialized during in the board init function, but there is no harm
 * in doing so twice. This way the gpio_init() function can be showcased */
static void init_gpios(void)
{
    for (unsigned i = 0; i < ARRAY_SIZE(buttons); i++) {
        gpio_init(buttons[i], button_modes[i]);
    }

    for (unsigned i = 0; i < ARRAY_SIZE(leds); i++) {
        gpio_init(leds[i], GPIO_OUT);
    }
}

static void * check_button(void *_arg)
{
    uintptr_t idx = (uintptr_t)_arg;

    while (1) {
        ztimer_sleep(ZTIMER_MSEC, 1);
        gpio_write(leds[idx], gpio_read(buttons[idx]));
    }

    UNREACHABLE();
    return NULL;
}

int main(void)
{
    puts("Welcome to RIOT!");

    init_gpios();

    check_button((void *)0);

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}