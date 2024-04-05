#include "shm.h"

using std::cout;

int fd;
char *shmpath;
shr_mem *buf;

void *producer(void *argc)
{

    int item1;
    int i = 0;
    while (i < 5)
    {
        item1 = rand() % 50;
        sem_wait(&buf->empty);
        sem_wait(&buf->mutex);
        cout << "Produced: " << item1 << std::endl;
        buf->table[buf->indexIn] = item1;
        buf->indexIn = (buf->indexIn + 1) % BUF_SIZE;
        cout << "Table: | ";
        if (buf->indexIn == 0)
           cout << "in |  |" << std::endl;
        else
            cout << " | in |" << std::endl;
        sem_post(&buf->mutex);
        sem_post(&buf->full);
        ++i;
        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    shmpath = argv[1];
    fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, 0600);
    ftruncate(fd, sizeof(shr_mem));
    buf = static_cast<struct shmbuf *>(mmap(NULL, sizeof(shr_mem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    sem_init(&buf->mutex, 1, 1);
    sem_init(&buf->empty, 1, BUF_SIZE);
    sem_init(&buf->full, 1, 0);
    buf->indexIn = 0;
    buf->indexOut = 0;
    cout << "Producer thread starting" << std::endl;
    pthread_t pro;
    pthread_create(&pro, NULL, &producer, NULL);
    pthread_join(pro, NULL);
    shm_unlink(shmpath);
    return 0;
}
