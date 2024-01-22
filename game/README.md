Task 08: Gaming in RIOT
=======================

The Programming Task
--------------------

Implement a game on the nRF52840 DK that interacts with the player in some way.
Below are some ideas:

1. Dice Game
    - The LEDs are used to indicate the score
    - Any button can be used to roll the dice
    - The time between two button presses (or between boot and the first button press) can be used to generate some randomness, e.g. by computing a cryptographic hash of that value
    - Single player (against the computer) or two player games would be possible.
      Higher number wins
2. The LED Ladder Game
    - See https://projects.drogon.net/raspberry-pi/gpio-examples/ladder-game/ for details
3. Fast Reaction Game
    - After a random delays (0.5 ... 5 seconds) a random LEDs lights up
    - The player has to press the corresponding button to turn the LED back off
    - If a wrong button is pressed, the player looses
    - If a button is pressed without an LED lighting up, the player looses
    - If the right button is pressed, the player scores at least 10 ms
        - If the delay between LED lighting up is at most 90 ms, the player scores 20 points
        - For every additional 10 ms shorter response time, 10 additional points are earned
4. A Classical Text Adventure
    - Use the console of the board to implement a classical text adventure (e.g. something like [Zork](https://en.wikipedia.org/wiki/Zork))

Note: You can use any feature or RIOT and the board, including all sensors, actuators, the network interface, and the shell.
You may also attach additional hardware (such as additional LEDs, LCD screens, additional buttons, joysticks, ...) to the board.
However, the exact hardware setup has to be documented and all components have to be commonly available, so that we can reproduce the setup for grading.
