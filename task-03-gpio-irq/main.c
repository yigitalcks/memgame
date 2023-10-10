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

static void on_button_pressed(void *_arg)
{
    uintptr_t idx = (uintptr_t)_arg;

    // FIXME: Add debouncing

    gpio_toggle(leds[idx]);
}

static void init_gpios_and_irqs(void)
{
    for (unsigned i = 0; i < ARRAY_SIZE(leds); i++) {
        gpio_init(leds[i], GPIO_OUT);
    }

    for (unsigned i = 0; i < ARRAY_SIZE(buttons); i++) {
        gpio_init(buttons[i], button_modes[i]);
        // FIXME: Don't execute on_button_pressed here, but from an ISR that is executed when
        // a rising edge on the GPIO buttons[i] is detected.
        on_button_pressed((void *)i);
    }
}

int main(void)
{
    puts("Welcome to RIOT!");

    init_gpios_and_irqs();

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
