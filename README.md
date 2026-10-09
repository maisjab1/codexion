*This activity has been created as part of the 42 curriculum by mjabarin*

# **Codexion**

## **Description**

### **The Dining Philosophers Problem**

The dining philosophers problem is a classic computer science illustration of synchronization and resource allocation issues in concurrent programming and operating systems.

![Dining Philosophers](https://github.com/user-attachments/assets/fe25094e-1a74-43cb-8e9a-173eea77c801)

**The Analogy:**
- **Philosophers** represent concurrent CPU processes or threads.
- **Forks** represent shared resources that only one process can use at a time.
- **Eating** requires holding two shared resources simultaneously (left and right forks).

**Core Issues in Concurrency:**

1. **Deadlock:** If every philosopher grabs the left fork at the same time, all right forks are taken. Every process waits forever for a second resource, freezing the system.
2. **Starvation:** A process might continually get blocked from acquiring both resources because neighboring processes keep monopolizing them.
3. **Mutual Exclusion:** Two processes cannot safely access the same shared resource simultaneously.

### **Codexion**

**Codexion** is a concurrency simulation in C, based on the Dining Philosophers problem. Several **coder** threads compete for a limited pool of USB **dongles**, and a coder must hold **two dongles** (one in each hand) before it can compile.

**Mapping:**
- **Coder** → Philosopher
- **Dongle** → Fork
- **Compiling** → Eating

**Rules:**
- There are as many dongles as coders, arranged in a circle.
- Each coder can do **one thing at a time**: compile, debug, or refactor.
- To compile, a coder needs **both** the left and right dongle.
- Once compiling is done, the coder **releases both dongles** and starts debugging, then refactoring, then repeats.
- If a coder does not **start compiling** within `time_to_burnout` ms since their last compile (or since simulation start), they **burn out**.
- The simulation stops when a coder burns out, or when every coder has compiled at least `number_of_compiles_required` times.
- Coders **cannot communicate** and do not know when another coder will burn out.


## **Instructions**

**Compile:**
```bash
make
```

**Run:**
```bash
./codexion 5 2000 100 100 100 3 500 fifo
```

## **Usage**

| Argument | Description |
|---|---|
| `number_of_coders` | Number of coder threads (and dongles) |
| `time_to_burnout` | ms before a coder burns out without compiling |
| `time_to_compile` | ms spent compiling (holding two dongles) |
| `time_to_debug` | ms spent debugging (no dongles needed) |
| `time_to_refactor` | ms spent refactoring (no dongles needed) |
| `number_of_compiles_required` | Stop simulation after all coders reach this count |
| `dongle_cooldown` | ms before a released dongle can be reused |
| `scheduler` | `fifo` (first-in-first-out) or `edf` (earliest-deadline-first) |

## **Technical Choices**

**TODO:** Heap-based priority queue for FIFO/EDF scheduling (to be implemented)

## **Blocking Cases Handled**

**TODO:** 
- Deadlock prevention via asymmetric pickup
- Starvation prevention via EDF scheduling
- Dongle cooldown handling

## **Thread Synchronization Mechanisms**

**TODO:** 
- `pthread_mutex_t` for dongle state protection

## **Some Terminologies**

### **Concurrency**
In computer science, concurrency refers to the ability of a system to execute multiple tasks through simultaneous execution or time-sharing (context switching), sharing resources and managing interactions.
[Concurrency (Wikipedia)](https://en.wikipedia.org/wiki/Concurrency_(computer_science))

### **POSIX Threads**
POSIX Threads (pthreads) is an execution model that exists independently from a programming language, allowing a program to control multiple flows of work that overlap in time.
[Pthreads (Wikipedia)](https://en.wikipedia.org/wiki/Pthreads)

### **Mutual Exclusion**
Mutual exclusion is a property of concurrency control that prevents race conditions by ensuring one thread never enters a critical section while another is already accessing it.
[Mutual Exclusion (Wikipedia)](https://en.wikipedia.org/wiki/Mutual_exclusion)

## **Comparisons**

### **Multi-threading vs Multi-processing**
Multi-threading uses multiple threads inside a single process to share memory, while multi-processing runs completely separate processes with their own memory spaces.

### **Concurrency vs parallelism**
<img width="1280" height="1664" alt="image" src="https://github.com/user-attachments/assets/5ad4f748-43d1-43b4-a152-ba6667446ad0" />

## **Resources**

**Articles & References:**
- [Understanding Mutexes and Semaphores](https://medium.com/@sylvain.tiset/understanding-mutexes-and-semaphores-preventing-deadlocks-and-starvation-in-concurrent-programming-6bc477b7b7a9)
- [The Critical Section Problem](https://medium.com/@drajput_14416/os-understanding-the-critical-section-problem-and-its-solutions-2eb34f09e868)
- [Software Execution Models](https://medium.com/@lalosaimi/software-execution-models-bf9ae753e910)
- [What is a Mutex?](https://stackoverflow.com/questions/34524/what-is-a-mutex)
- [Race Condition](https://www.geeksforgeeks.org/operating-systems/race-condition-in-operating-systems/)
- [Asymmetric Solution](https://diningphilosophers.eu/hierarchy_asymmetric)
- [clock_gettime](https://www.qnx.com/developers/docs/8.0/com.qnx.doc.neutrino.lib_ref/topic/c/clock_gettime.html)

**Videos:**
- [Youtube playlist to understand threads in C](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- [Semaphores](https://youtu.be/XDIOC2EY5JE)
- [The Dining Philosophers Problem](https://www.youtube.com/watch?v=FYUi-u7UWgw&list=TLPQMTIwOTIwMjaUGbdWMS_Bvg&index=2)
