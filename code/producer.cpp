/*
    Minh Nhat Nguyen
    Operating Systems - CS33211, Project 1
    Producer file
*/

#include "shm.h"

using std::cout;

// Variables for the shared memory buffer
int fd;
char *shmpath;
shr_mem *buf;

// Prodcuer thread
void *producer(void *argc)
{
    // item for buffer
    int item1;

    // run production 5 times
    int i = 0;
    while (i < 5)
    {
        item1 = rand() % 50;

        // Wait
        sem_wait(&buf->empty);
        sem_wait(&buf->mutex);

        // Critical section
        cout << "Produced: " << item1 << std::endl;
        buf->table[buf->indexIn] = item1;
        buf->indexIn = (buf->indexIn + 1) % BUF_SIZE;

        // Signal
        sem_post(&buf->mutex);
        sem_post(&buf->full);
        ++i;

        // Waits 1 second
        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // Initialize shared memory
    shmpath = argv[1];
    fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, 0600);
    ftruncate(fd, sizeof(shr_mem));
    buf = static_cast<struct shmbuf *>(mmap(NULL, sizeof(shr_mem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    
    // Initialize semaphores and indexes
    sem_init(&buf->mutex, 1, 1);
    sem_init(&buf->empty, 1, BUF_SIZE);
    sem_init(&buf->full, 1, 0);
    buf->indexIn = 0;
    buf->indexOut = 0;

    // Runs producer thread
    cout << "Producer thread starting" << std::endl;
    pthread_t pro;
    pthread_create(&pro, NULL, &producer, NULL);
    pthread_join(pro, NULL);

    // Remove the name of the shared memory object
    shm_unlink(shmpath);

    // End program
    return 0;
}
