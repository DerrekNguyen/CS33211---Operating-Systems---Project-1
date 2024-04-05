## Minh Nhat Nguyen
## Assignment 1 - Producer-Consumer Problem
## CS33211 - OPERATING SYSTEMS 
## Dr. Qiang Guan
## Kent State University
## 04/05/2024

<br><br>

### Description
The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

<br>

### How to run
This code will only run in a Linux or Unix environment. Once you have the code, navigate to the main folder that contains the Makefile and type
```
make all
```
All codes in the ```code``` folder will compile, including the shared buffer in the header. For more details please consult the documentation.

### Reference links
https://man7.org/linux/man-pages/man3/shm_open.3.html
https://man7.org/linux/man-pages/man3/shm_unlink.3p.html
https://man7.org/linux/man-pages/man3/shm_open.3.html
https://man7.org/linux/man-pages/man3/pthread_create.3.html
https://man7.org/linux/man-pages/man3/pthread_join.3.html

