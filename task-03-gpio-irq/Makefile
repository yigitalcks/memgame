APPLICATION := task-03
BOARD := nrf52840dk
RIOTBASE := $(CURDIR)/../RIOT
PROGRAMMER ?= openocd

DEVELHELP ?= 1
QUIET ?= 1

FEATURES_REQUIRED += periph_gpio_irq

USEMODULE += shell
USEMODULE += shell_cmds_default
USEMODULE += ps
USEMODULE += ztimer_msec

include $(RIOTBASE)/Makefile.include
