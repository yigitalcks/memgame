APPLICATION := task-06
BOARD := nrf52840dk
RIOTBASE := $(CURDIR)/../RIOT
PROGRAMMER ?= openocd

DEVELHELP ?= 1
QUIET ?= 1

USEMODULE += netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_default
USEMODULE += gcoap
USEMODULE += gnrc_icmpv6_echo
USEMODULE += od
USEMODULE += fmt
USEMODULE += netutils
USEMODULE += shell
USEMODULE += shell_cmds_default
USEMODULE += saul_default
USEMODULE += ps

include $(RIOTBASE)/Makefile.include
