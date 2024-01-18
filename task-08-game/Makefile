APPLICATION := task-08
BOARD := nrf52840dk
RIOTBASE := $(CURDIR)/../RIOT
PROGRAMMER ?= openocd

DEVELHELP ?= 1
QUIET ?= 1

USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_cmds_default
USEMODULE += ztimer_msec
USEMODULE += ztimer_sec

include $(RIOTBASE)/Makefile.include
