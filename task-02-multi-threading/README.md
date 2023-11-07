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

Answers
=======================

Introducing GPIOs
-----------------

1. GPIOs on a Integrated circuit (IC) or Boards(Single board computers, etc.) are pins that can be used as input or output, also can be controlled by software.
2. The default state of a GPIO pin varies according to hardware and software configuration but if state of a pin is HIGH, it means that there is a default pull up resistor on the pin and is LOW, it means that tehre is a default pull down resistor on the pin.
3. Initialize the given pin as general purpose input or output.
4. gpio_write : set the pin to given value (takes pin and value as argument)
   gpio_set   : set the pin to HIGH        (takes pin as argument)
   gpio_clear : set the pin to LOW         (takes pin as argument)
   gpio_toggle: if the pin is LOw, set to HIGH, if the pin is HIGH, set to LOW (takes pin as argument)
5. Question 4
6. A: HIGH
   B: LOW
   C: HIGH
   If the value of the pin is >0, it means HIGH.
   If the value of the pin is 0, it means LOW.

Threads
-------

1. Processes are basically the programs that are scheduled in CPU for execution. Threads are segment of a process. Processes are isoleted of each other, threds share memory. Process has its own Process Control Block, Stack, and Address Space, Thread has Parents’ PCB, its own Thread Control Block, and Stack and common Address space.
2. 
3. Threads run as there are processors, and they stay on their processor until they yield.
4. Being tickless means it does not have a timer that fires periodically in order to emulate concurrent execution by switching threads continuously.
5. Unless an interrupt happens, threads with the same priority will only switch due to voluntary or implicit context switches.
6. 
   The new thread's stack is initialized     depending on the platform.
   The new thread is added to the scheduler and the scheduler is run (if not indicated otherwise)
7. It can causes stack owerflow, if the call stack pointer exceeds the stack bound and undefined Behaviors.
8. Normally each thread should have its own stack. i think, it can cause data loss, because they use the same memory space.
9. it can be done, when a thread is created. thread_create function takes a argument of type void* named arg.
10. A reasonable default stack size that will suffice most smaller tasks. 
