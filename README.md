## Minh Nhat Nguyen
## Assignment 1 - Producer-Consumer Problem
## CS33211 - OPERATING SYSTEMS 
## Dr. Qiang Guan
## Kent State University
## 04/05/2024

<br><br>

### Description
The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

In this implementation, I ran the producer and consumer processes 5 times each. This can be changed within the codes. The items are of type integers, from 0 to 50 for simplicity. These values can be changed if necessary.

<br>

### How to run
This code will only run in a Linux or Unix environment. Once you have the code, navigate to the main folder that contains the Makefile and type
```
make all
```
All codes in the ```code``` folder will compile, including the shared buffer in the header. For more details please consult the documentation.

<br>

### Example
![image](https://github.com/DerrekNguyen/CS33211_Operating-Systems_Assignment-1/assets/143032197/4467260d-bae0-4942-b62e-5c01b7217063)


### Reference links
https://man7.org/linux/man-pages/man3/shm_open.3.html

https://man7.org/linux/man-pages/man3/shm_unlink.3p.html

https://www.geeksforgeeks.org/use-posix-semaphores-c/

https://man7.org/linux/man-pages/man3/pthread_create.3.html

https://man7.org/linux/man-pages/man3/pthread_join.3.html

