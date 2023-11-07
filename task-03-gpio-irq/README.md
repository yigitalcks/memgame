Task 03: GPIOs and IRQs
=======================

General Understanding
---------------------

[RIOT's GPIO API](https://api.riot-os.org/group__drivers__periph__gpio.html) also provides functions to enable interrupts on GPIO pins and to register a callback function to be executed from within the ISR.

1. What do the following terms mean?
    - IRQ
    - ISR
    - interrupt handler
    - thread context
    - interrupt context
1. What is the difference between nested interrupts and sequential interrupts?
1. RIOT disabled nested interrupts even on platforms that support them (but allows the user to alter the behavior).
   What could be the reasons for this?
1. In RIOT a [mutex](https://api.riot-os.org/group__core__sync__mutex.html) is often used to synchronize two threads.
    1. Is it safe to call `mutex_lock()` from interrupt context?
    1. Is it safe to call `mutex_unlock()` from interrupt context?
       (Note: Unlike POSIX mutexes it is absolutely valid to unlock a RIOT mutex that was locked by a different thread.)
1. What is the difference between edge and level triggered IRQs?
1. Does RIOT support edge triggered IRQs, level triggered IRQs, or both?
1. What is does [debouncing noisy buttons](https://hackaday.com/2015/12/10/embed-with-elliot-debounce-your-noisy-buttons-part-ii/) mean?

The Programming Task
-------------------------

The program should:

1. Toggle the corresponding LED whenever one of the four buttons is pushed down
1. Releasing a button is ignored
1. No additional threads should be launched and the main thread (and only thread) should be fully dedicated to running the shell (after doing some setup when starting)

Answers
=======================

General Understanding
---------------------

1. IRQ: An interrupt request (IRQ) is a signal sent to a computer's processor to momentarily stop (interrupt) its operations.
   ISR: ISR is a specific type of software routine or function associated with a specific interrupt condition.
   Interrupt handler: Also known as ISR.
   Thread context: Thread context is the current state of a thread and information associated with the thread.
   Interrupt context: Interrupt context is when the interrupt occurs state goes to interrupt handler, and current process stops/saves until we complete interrupt.

2. All sequential interrupts will be processed sequentially and interrupt requests is disabled while an interrupt is being processed. On the other Hand all nested interrupts may be assigned different priorities, so that
whenever an interrupt occurs while an interrupt handler is running, will be compared first, then the further action will be determined according to the result.
3. The stack usage of user tasks becomes unpredictable when you allow interrupt nesting.
4. No, must be called in thread context.
   Yes, it is safe to call this function from IRQ context.
5. Edge-triggered interrupts are based on a specific transition or change in the interrupt signal's state(rising edge, falling edge). Level-triggered interrupts are based on the continuous state of the interrupt signal. The interrupt is recognized and serviced as long as the signal remains in the active state.
6. I think both of them.
7. It occurs when a button is pressed or released, and the electrical contacts inside the button make rapid, unintended, and multiple transitions between open and closed states.