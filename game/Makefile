APPLICATION := game
BOARD := nrf52840dk
RIOTBASE := $(CURDIR)/../RIOT
PROGRAMMER ?= openocd

DEVELHELP ?= 1
QUIET ?= 1

USEMODULE += shell
USEMODULE += shell_cmds_default
USEMODULE += ps
USEMODULE += ztimer_msec
USEMODULE += ztimer_sec
USEMODULE += periph_gpio_irq
USEMODULE += random

include $(RIOTBASE)/Makefile.include
