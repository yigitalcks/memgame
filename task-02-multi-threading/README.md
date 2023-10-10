Task 02: Multithreading
=======================

Introducing GPIOs
-----------------

For answering the following questions, refer to the [Wikipedia article about GPIOs](https://en.wikipedia.org/wiki/General-purpose_input/output) and RIOT OS API documentation of [the GPIO API](https://api.riot-os.org/group__drivers__periph__gpio.html).
Note: Ignore everything related to IRQ for now, that will be covered by next weeks task.

1. What is a GPIO?
1. What is the default state of a GPIO?
1. What is the purpose of the `gpio_init()` function.
1. What is difference between `gpio_write()`, `gpio_set()`, `gpio_clear()`, and `gpio_toggle()`?
1. What do these functions (listed in the previous question) have in common?
1. Assume that calls to `gpio_read()` for the GPIOs *A*, *B*, and *C* return the values `1`, `0`, `8`.
   What is the state of the GPIOs?

Threads
-------

For answering the following questions, refer to the RIOT OS API documentation of [the threading API](https://api.riot-os.org/group__core__thread.html).
You might also want to check the TI-1 and TI-2 lecture slides, or consult the Wikipedia articles [on threads](https://en.wikipedia.org/wiki/Thread_(computing)) and [MMUs](https://en.wikipedia.org/wiki/Memory_management_unit).

1. What was the difference between a thread and a process?
1. Why does RIOT only support threads, but not processes?
1. What is cooperative multi-threading?
1. RIOT is said to use a "tickless scheduler", what does this mean?
1. Assuming thread *A* and *B* have the same priority and *A* is currently running and *B* is on the run queue.
   How long does it take that RIOT schedules thread *B* if *A* never yields nor blocks?
1. How can a thread in RIOT be created?
1. What happens, if a thread with too little stack is created?
1. What happens, if a second thread is created with the same memory buffer used as stack as for the first - assuming the first thread has not yet terminated yet and both threads will eventually run?
1. How can an argument be passed to a thread in RIOT?
1. What is the purpose of the macro `THREAD_STACKSIZE_DEFAULT`?


The Programming Task
-------------------------

The program should:

1. Check the status of each of the four buttons on the board and turn on the corresponding LED exactly when a button is pressed
1. A dedicated thread should be launched for each button to monitor
    - Do not use IRQs, but just read out the button's state over and over again (polling)
1. The main thread should still run the shell, so that you can still run commands like `saul` and `ps`
1. Verify that there is exactly one thread per button using the `ps` shell command
