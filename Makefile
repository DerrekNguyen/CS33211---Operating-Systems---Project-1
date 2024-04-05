all: build
	./producer shmPath & ./consumer shmPath

build: clean
	g++ ./code/shm.h ./code/producer.cpp -pthread -lrt -o producer
	g++ ./code/shm.h ./code/consumer.cpp -pthread -lrt -o consumer

clean:
	rm -f producer consumer