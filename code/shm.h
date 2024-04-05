#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <ctype.h>
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

// Size of table
#define BUF_SIZE 2

// Shared buffer
struct shmbuf {
	sem_t empty;
	sem_t full;
	sem_t mutex;
	int indexIn, indexOut;
	int table[BUF_SIZE];
};