Task 05: UDP Server and Client
==============================

General Understanding
---------------------

Read the following documentations:

1. [The UDP sock API](https://api.riot-os.org/group__net__sock__udp.html)
1. [The POSIX sockets in RIOT](https://api.riot-os.org/group__posix__sockets.html)
1. The man pages of [recvfrom()](https://linux.die.net/man/3/recvfrom), [sendto()](https://linux.die.net/man/3/sendto), [socket()](https://linux.die.net/man/3/socket)
1. This [article about memory alignment](https://hackaday.com/2022/05/10/data-alignment-across-architectures-the-good-the-bad-and-the-ugly/)
1. This [Wikipedia entry about endianness](https://en.wikipedia.org/wiki/Endianness)
1. The [man pages about `htons()`, `ntohs()`, `htonl()`, `ntohl()`](https://linux.die.net/man/3/htons)

1. What are the advantages of the RIOT sock API over the POSIX socket API?
1. What are the advantages of the POSIX socket API over the RIOT sock API?
1. Which of the APIs is used to implement the UDP server in `exmaples/gnrc_networking`?
1. Why can a `struct` with the same contents have a different representation in memory on two different CPUs with the same alignment requirements?
1. Why can a `struct` with the same contents have a different representation in memory on two different CPUs with the same endianness?
1. Why can bus errors occur when casting data received into a buffer `char buf[128];` when accessed via `struct *foo = (void *)buf; foo->bar;`?

The Programming Task
--------------------

1. Implement a UDP server that is running in background (in its own thread) and started before the shell is displayed.
    - This server should expose the SAUL devices of your board for read and write access
    - Come up with your own message format that
        - provides two requests types (read and write)
        - both types have a field that allow specifying a single SAUL device by its number
        - the write message type contains a field to specify the data to write
        - provides two response types (data and status)
        - in case of writes a status reply is given that indicates success or failure
        - in case of reads either a status reply is given (to indicate a failre) or a data reply (to provide the data that was read)
    - Optionally, you can add a third request and response type to allow retrieving the SAUL devices and their details
2. Implement a UDP client that can be invoked via the shell
    - This must allow sending the request messages specified above
    - It must wait for the corresponding response and print it
    - The client must retry the request after 100 ms, 200 ms, 400 ms and 800 ms if it fails
    - After 5 unsuccessful attempts (the original transmissions and the four retransmissions) the client gives up and print an error in the shell instead
