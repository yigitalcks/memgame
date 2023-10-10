#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"

int main(void)
{
    puts("Welcome to RIOT!");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
