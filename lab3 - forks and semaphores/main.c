#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <semaphore.h>
#include "pqueue.h"

char *filename = "queue.dat";

int itemId = 0;

typedef struct item item;
struct item {
	int id;
};


item * produce() {
	int time = rand() % 5 + 1;
	item *it = (item *)malloc(sizeof(item));
	
	sleep(time);
	it->id = itemId;
	itemId += 1;
	return it;
}

void consume(item *it) {
	int time = rand() % 5 + 1;
	sleep(time);
	free(it);
}


void producer(pid_t childPid, pqueue *queuehead, sem_t* sem) {
	for(int i=1;i<=5;i++)
	{
		sem_wait(sem);
		item* product = produce();
		qunserialize(&queuehead, sizeof(item), filename);
		product->id = i;
		printf("Produced product widh id %d\n", product->id);
		qinsert(&queuehead, product, 1);
		qserialize(queuehead, sizeof(item), filename);
		sleep(5);
		sem_post(sem);
	}
}

void consumer(pid_t childPid, pqueue *queuehead, sem_t* sem) {
	for(int i=1;i<=5;i++)
	{
		sleep(5);
		sem_wait(sem);
		qunserialize(&queuehead, sizeof(item), filename);
		pqueue* package = qpop(&queuehead);
		item* product = package->data;
		printf("Consuming product with id %d\n", product->id);
		consume(product);
		qserialize(queuehead, sizeof(item), filename);
		sem_post(sem);
	}
}

int main(int argc, char **argv) {
	//pid_t pid;
	pqueue *qu = NULL;
	
	sem_t sem;
	/* watch -n 1 ps -l --forest */
	
	/* create empty queue */
	qserialize(qu, sizeof(item), filename);
	
	if(sem_init(&sem, 0, 1) != 0)
        return 1;
	
	int pid = fork();

	if(pid == 0)
	{
		producer(pid,qu, &sem);
	}
	else
	{
		pid = fork();
		if(pid==0)
		{
			consumer(pid,qu, &sem);
		}
	}

	return 0;
}

// produkować 1-5 produktów

// a konsumnet 1-5 produktow o konkretnym priorytecie