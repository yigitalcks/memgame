Task 07: Weather Station
========================

General Understanding
---------------------

The following documentations will be useful:

1. [The PWM API](https://api.riot-os.org/group__drivers__periph__pwm.html)
1. [The SAUL Registry API](https://api.riot-os.org/group__sys__saul__reg.html)

Answer the following questions:

1. How can one dim the LEDs of the nRF52840DK?
1. How can the internal temperature sensor of the nRF52840DK be accessed?

The Programming Task
--------------------

1. Add a background thread that periodically polls the current temperature and visualises it using the LEDs
    - All LEDs off should indicate 18 °C
    - All LEDs fully on should indicate +26C
    - One LED fully on for 20 °C, two for +22 °C, three for +24 °C
    - (Each additional LED represents 2 °C)
    - Dim the lastly enabled LED to represent values in between (e.g. an additional LED lightning at 50% intensity represents 1 °C)
