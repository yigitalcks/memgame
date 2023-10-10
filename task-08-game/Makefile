APPLICATION := task-08
BOARD := nrf52840dk
RIOTBASE := $(CURDIR)/../RIOT
PROGRAMMER ?= openocd

DEVELHELP ?= 1
QUIET ?= 1

USEMODULE += ps
USEMODULE += saul_default
USEMODULE += shell
USEMODULE += shell_cmds_default
USEMODULE += ztimer_msec

include $(RIOTBASE)/Makefile.include
