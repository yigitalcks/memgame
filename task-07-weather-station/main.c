/*
 * Copyright (C) 2008, 2009, 2010 Kaspar Schleiser <kaspar@schleiser.de>
 * Copyright (C) 2013 INRIA
 * Copyright (C) 2013 Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Default application that shows a lot of functionality of RIOT
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"
#include "saul.h"
#include "saul_reg.h"
#include "phydat.h"
#include "ztimer.h"

void light_led(int i, int val)
{
    phydat_t data;
    data.scale = 0;
    data.val[0] = val;
    data.unit = UNIT_PERCENT;

    saul_reg_write(saul_reg_find_nth(4 + i), &data);
}

int get_degree(void)
{
    phydat_t data;
    saul_reg_read(saul_reg_find_nth(8), &data);
    return data.val[0];
}

char thread_stacks[THREAD_STACKSIZE_MAIN];
void *thread_func(void *arg)
{
    (void)arg;

    while (1)
    {
        int degree = get_degree();

        if (degree < 1800)
        {
            light_led(0, 0);
            light_led(1, 0);
            light_led(2, 0);
            light_led(3, 0);
        }
        else if (degree < 2000)
        {
            light_led(0, 100);
            if (degree > 1900)
                light_led(1, 50);
            else
                light_led(1, 0);
            light_led(2, 0);
            light_led(3, 0);
        }
        else if (degree < 2200)
        {
            light_led(0, 100);
            light_led(1, 100);
            if (degree > 2100)
                light_led(2, 50);
            else
                light_led(2, 0);
            light_led(3, 0);
        }
        else if (degree < 2400)
        {
            light_led(0, 100);
            light_led(1, 100);
            light_led(2, 100);
            if (degree > 2300)
                light_led(3, 50);
            else
                light_led(3, 0);
        }
        else
        {
            light_led(0, 100);
            light_led(1, 100);
            light_led(2, 100);
            light_led(3, 100);
        }
        
        ztimer_sleep(ZTIMER_MSEC, 1000);
    }

    UNREACHABLE();
    return NULL;
}

int main(void)
{
    puts("Welcome to RIOT!");

    thread_create(thread_stacks, sizeof(thread_stacks), THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST, thread_func, NULL, "my_thread");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
