*This activity has been created as part of the 42 curriculum by mjabarin*
# Codexion
# Description
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
### multi-threading vs multiprocessing
Multi-threading uses multiple threads inside a single process to share memory, 
while multiprocessing runs completely separate processes with their own memory spaces
# Instructions
# Resources
. https://medium.com/@sylvain.tiset/understanding-mutexes-and-semaphores-preventing-deadlocks-and-starvation-in-concurrent-programming-6bc477b7b7a9
. https://medium.com/@drajput_14416/os-understanding-the-critical-section-problem-and-its-solutions-2eb34f09e868
. Software Execution Models: https://medium.com/@lalosaimi/software-execution-models-bf9ae753e910
. Mutex : https://stackoverflow.com/questions/34524/what-is-a-mutex
. Race condition : https://www.geeksforgeeks.org/operating-systems/race-condition-in-operating-systems/
