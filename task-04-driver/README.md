Task 04: Implementing a Simple Device Driver
============================================

General Understanding
---------------------

Read the section 12.1.16 and following in [the datasheet](https://infocenter.nordicsemi.com/pdf/nRF52840_OPS_v0.5.pdf) of the nRF52840 MCU.
Make yourself familiar with the concept of [memory mapped I/O](https://en.wikipedia.org/wiki/Memory-mapped_I/O).
Try to understand what the [`volatile` qualifier](https://blog.regehr.org/archives/28) in the C language is used for, and what not.
Check in `drivers/dht/dht_saul.c` how a SAUL integration of sensor and actuator drivers can be implemented.

1. What of the following statements about the `volatile` qualifier are correct?
    - Accesses to memory marked as `volatile` are memory barriers
    - A compiler may reorder any non-`volatile` memory access across a `volatile` memory access
    - A compiler may reorder two `volatile` memory accesses in regard to each other
    - Using the `volatile` qualifier will turn off even basic optimization for every access to such marked memory
    - Accessing a 32 bit memory location marked as `volatile` will result in the compiler using only 32 bit loads and stores, if supported
    - All accesses to `volatile` memory are atomic
    - For inter-thread communication via shared memory marking that memory as `volatile` is sufficient
    - Accessing memory mapped hardware register does not require the `volatile` keyword
    - There is hardly a legitimate use case for `volatile` besides memory mapped I/O
    - The declaration `const volatile uint32_t *timer_counter = 0x8000010` is both valid and possible sensible
    - In `volatile uint32_t *a` the pointer is volatile, in `uint32_t * volatile a` the location `a` is pointing to is `volatile`
1. What does the return value of the `read()` and `write()` function pointers in a `saul_driver_t` structure say?
1. How can code running on an MCU very that it is indeed a nRF52840 and not e.g. a nRF52832 MCU?
1. How can the revision be obtained?


The Programming Task
--------------------

Add drivers and SAUL integrations to access the following hardware infos:

1. The part number of the nRF52xxx MCU (assume BCD encoding and decode it)
1. The variant ID of the nRF52xxx MCU
1. The package of the MCU
1. The RAM size
1. The FLASH size

You can either be creative when mapping the variant ID to something representable to SAUL or skip this in the SAUL integration.
All other things have to be mapped to SAUL.

Answers
=======

General Understanding
---------------------

1. 
    - The keyword volatile does not guarantee a memory barrier to enforce cache-consistency. Therefore, the use of volatile alone is not sufficient to use a variable for inter-thread communication on all systems and processors.
    - Correct. Non-volatile accesses can be reordered across volatile accesses.
    - Incorrect. Volatile accesses are generally not reordered with respect to each other to maintain the order specified in the code.
    - Correct but i am not sure. Volatile is a type qualifier in ‘C’ used with variables to instruct the compiler not to invoke any optimization on the variable operation.
    - Incorrect. Volatile qualifier doesn't dictate the size of loads and stores.
    - Incorrect. The volatile keyword eradicates visibility problems, but it does not deal with atomicity. 
    - Incorrect. It doesn't provide atomicity or synchronization.
    - Incorrect. Volatile is mainly used with memory-mapped registers to avoid compiler optimizations.
    - Incorrect. Volatile has legitimate uses in multithreaded programming and memory-mapped I/O operations.
    - Correct. It's a constant pointer to volatile data.
    - Correct.
2. 
    - read(): Read a value (a set of values) from a device Simple sensors, as e.g. a temperature sensor, will return exactly one value together with the values scale and unit(saul_read_t).
    - write(): Write a value (a set of values) to a device Most sensors will probably just return -ENOTSUP, as writing values to a sensor is often without purpose(saul_write_t).
3.  MCU vendors often provide registers containing information about the MCU model. In nRF52840, there is INFO.PART register.
4.