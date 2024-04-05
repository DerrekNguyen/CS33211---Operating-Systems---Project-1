all: build
	./producer shmPath & ./consumer shmPath 

build: 
	g++ shm.h ./code/producer.cpp -pthread -lrt -o producer
	g++ shm.h ./code/consumer.cpp -pthread -lrt -o consumer