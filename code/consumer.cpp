#include "shm.h"

using std::cout;

int fd;
char *shmpath;
shr_mem *buf;

void *consumer(void *argc) {

	int i = 0;
	int item2;
	while (i < 5) {	
		sem_wait(&buf->full);
		sem_wait(&buf->mutex);
		item2 = buf->table[buf->indexOut];
		cout << "Consumed: " << item2 << std::endl;
		buf->indexOut = (buf->indexOut + 1) % BUF_SIZE;
		cout << "Table: | ";
		if (buf->indexOut == 0) cout << "out |  |" << std::endl;
		else cout << " | out |" << std::endl;
		sem_post(&buf->mutex);
		sem_post(&buf->empty);
		++i;
		sleep(1);
	}	
	return NULL;

}

int main(int agrc, char* argv[]) {
	srand(time(NULL));
	shmpath = argv[1];
	fd = shm_open(shmpath, O_RDWR, 0);
	ftruncate(fd, sizeof(shr_mem));
	buf = static_cast<shr_mem*>(mmap(NULL, sizeof(shr_mem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
	cout << "Consumer thread starting" << std::endl;
	pthread_t con;
	pthread_create(&con, NULL, &consumer, NULL);
	pthread_join(con, NULL);
	shm_unlink(shmpath);
	return 0;
}

