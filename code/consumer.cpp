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

// Consumer thread
void *consumer(void *argc) {

	// item for buffer
	int item2;

	// run consumption 5 times
	int i = 0;
	while (i < 5) 
	{	
		// Wait
		sem_wait(&buf->full);
		sem_wait(&buf->mutex);

		// Critical section
		item2 = buf->table[buf->indexOut];
		cout << "Consumed: " << item2 << std::endl;
		buf->indexOut = (buf->indexOut + 1) % BUF_SIZE;

		// Signal
		sem_post(&buf->mutex);
		sem_post(&buf->empty);
		++i;

		// Waits 1 second
		sleep(1);
	}	
	return NULL;

}

int main(int agrc, char* argv[]) {
	srand(time(NULL));

	// Opens shared memory
	shmpath = argv[1];
	fd = shm_open(shmpath, O_RDWR, 0);
	ftruncate(fd, sizeof(shr_mem));
	buf = static_cast<shr_mem*>(mmap(NULL, sizeof(shr_mem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
	
	// Runs consumer thread
	cout << "Consumer thread starting" << std::endl;
	pthread_t con;
	pthread_create(&con, NULL, &consumer, NULL);
	pthread_join(con, NULL);
	
	// Remove the name of the shared memory object
	shm_unlink(shmpath);

	// End program
	return 0;
}

