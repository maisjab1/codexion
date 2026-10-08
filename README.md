*This activity has been created as part of the 42 curriculum by mjabarin*
# Codexion
# Description

## The dining philosophers problem
The dining philosophers problem is a classic computer science illustration of synchronization and resource allocation issues in concurrent programming and operating systems.

The Analogy

• Philosophers represent concurrent CPU processes or threads.
• Forks or chopsticks represent shared hardware or software resources (like memory blocks, I/O devices, or locks) that only one process can use at a time.
• Eating requires holding two shared resources simultaneously (left and right forks)


Core Issues in CPU/Concurrency

1. Deadlock: If every philosopher/process grabs the left fork at the exact same time, all right forks are taken. Every process waits forever for a second resource, freezing the system.
2. Starvation: A process might continually get blocked from acquiring both resources because neighboring processes keep monopolizing them.
3. Mutual Exclusion: Two processes cannot safely access the same shared resource (fork) simultaneously
   
## Codexion
Codexion is a concurrency simulation in C, based on the Dining Philosophers problem. Several "coder" threads compete for a limited pool of USB dongles, and a coder must hold a dongle before it can compile.

where:
coder -> philosopher
dongle -> fork
eating -> compiling


The goal is to create a competition between differents coders using thread.
There is one or more coders. Each can do 3 things at a time:

compile
debug
refactor


They compile, then debug, then refactor and repeat.
Coders can burns out starting the simulation or when they finish compiling. They need to compile before the timer hits 0.
Do to that, they need both USB dongles. They are many dongles that coders. To compile, they need a dongle in each hands. Once compiling is done,they release the dongles.
If each coders have compiled a certain amount of time, the simulation can stop.
They can't communicate and they do not know when a coder will burns out.


<img width="757" height="772" alt="image" src="https://github.com/user-attachments/assets/f1122823-bc4f-4f89-89eb-0849c3fe5b59" />

## Some terminologies
### Concurrency
In computer science, concurrency refers to the ability of a system to execute multiple tasks through simultaneous execution or time-sharing (context switching), sharing resources and managing interactions. Concurrency improves responsiveness, throughput, and scalability in modern computing, including: [1][2][3][4][5]

    Operating systems and embedded systems
    Distributed systems, parallel computing, and high-performance computing
    Database systems, web applications, and cloud computing
'''
    https://en.wikipedia.org/wiki/Concurrency_(computer_science)
### POSIX threads
POSIX Threads, commonly known as pthreads (after its header <pthread.h>), is an execution model that exists independently from a programming language, as well as a parallel execution model. It allows a program to control multiple different flows of work that overlap in time. Each flow of work is referred to as a thread, and creation and control over these flows is achieved by making calls to the POSIX Threads API.
https://en.wikipedia.org/wiki/Pthreads

### Mutual exclusion
mutual exclusion is a property of concurrency control, which is instituted for the purpose of preventing race conditions. It is the requirement that one thread of execution never enters a critical section while a concurrent thread of execution is already accessing said critical section, which refers to an interval of time during which a thread of execution accesses a shared resource or shared memory.

https://en.wikipedia.org/wiki/Mutual_exclusion

## comparisons
### <span style="color: #4A90E2">Multi-threading vs multiprocessing</span>
Multi-threading uses multiple threads inside a single process to share memory, 
while multiprocessing runs completely separate processes with their own memory spaces
# Instructions
# Resources
. [understanding-mutexes-and-semaphores-preventing-deadlocks-and-starvation-in-concurrent-programming](https://medium.com/@sylvain.tiset/understanding-mutexes-and-semaphores-preventing-deadlocks-and-starvation-in-concurrent-programming-6bc477b7b7a9)

. [os-understanding-the-critical-section-problem-and-its-solutions](https://medium.com/@drajput_14416/os-understanding-the-critical-section-problem-and-its-solutions-2eb34f09e868)

. [Software Execution Models](https://medium.com/@lalosaimi/software-execution-models-bf9ae753e910)

. [Mutex](https://stackoverflow.com/questions/34524/what-is-a-mutex)

. [Race condition](https://www.geeksforgeeks.org/operating-systems/race-condition-in-operating-systems/)

. [A video on 'Semaphores'](https://youtu.be/XDIOC2EY5JE?si=nbppYzrV0DSG76ln)

. [A video on 'The dining philosophers problem'](https://www.youtube.com/watch?v=FYUi-u7UWgw&list=TLPQMTIwOTIwMjaUGbdWMS_Bvg&index=2)

. ['Asymmetric solution'](https://diningphilosophers.eu/hierarchy_asymmetric)

. ['clock_gettime'](https://www.qnx.com/developers/docs/8.0/com.qnx.doc.neutrino.lib_ref/topic/c/clock_gettime.html)
