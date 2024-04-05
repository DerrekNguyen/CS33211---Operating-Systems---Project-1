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
struct shmbuf *proBuf;

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
        sem_wait(&proBuf->empty);
        sem_wait(&proBuf->mutex);

        // Critical section
        cout << "Produced: " << item1 << std::endl;
        proBuf->table[proBuf->indexIn] = item1;
        proBuf->indexIn = (proBuf->indexIn + 1) % BUF_SIZE;

        // Signal
        sem_post(&proBuf->mutex);
        sem_post(&proBuf->full);
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
    ftruncate(fd, sizeof(*proBuf));
    proBuf = static_cast<shmbuf*>(mmap(NULL, sizeof(*proBuf), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    
    // Initialize semaphores and indexes
    sem_init(&proBuf->mutex, 1, 1);
    sem_init(&proBuf->empty, 1, BUF_SIZE);
    sem_init(&proBuf->full, 1, 0);
    proBuf->indexIn = 0;
    proBuf->indexOut = 0;

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
