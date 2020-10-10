#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <queue>
#include <semaphore.h>
#include <time.h>
#include "linkedList.h"
using namespace std;

#define NUM_THREADS 3
#define MEMORY_SIZE 10

struct queueNode
{
	int id;
	int size;
};

linkedlist memList;
bool releaseCheck = true;
bool threadsControl = true;
queue<queueNode> myqueue; // shared que
pthread_mutex_t sharedLock = PTHREAD_MUTEX_INITIALIZER; // mutex
pthread_t server; // server thread handle
sem_t semlist[NUM_THREADS]; // thread semaphores

int thread_message[NUM_THREADS]; // thread memory information
int memory[MEMORY_SIZE]; // memory size
void dump_memory();

void release_function()
{
	pthread_mutex_lock(&sharedLock);
  releaseCheck = false;
	memList.deleteAll();
	// for (size_t i = 0; i < MEMORY_SIZE; i++) {
	// 	memory[i] = -1;
	// }
	//dump_memory();
	while (!myqueue.empty()) {
		myqueue.pop();
	}
	for (size_t i = 0; i < NUM_THREADS; i++) {
		sem_destroy(&semlist[i]);
	}
		pthread_mutex_unlock(&sharedLock);
}

void dump_memory()
{
	cout << "List:\n";
	memList.printList();
	cout << "Memory Dump:\n";
	for (size_t i = 0; i < MEMORY_SIZE; i++) {
		if(memory[i] != -1)
			cout << memory[i];
		else{
			cout << "X";
		}
	}
	cout << "\n**********************************************\n";
}

//This function will add the struct to the queue
int my_malloc(int thread_id, int size)
{
	queueNode temp;
	temp.id = thread_id;
	temp.size = size;

	pthread_mutex_lock(&sharedLock);
	myqueue.push(temp);
	pthread_mutex_unlock(&sharedLock);
	//Block
	sem_wait(&semlist[thread_id]); // down
	return thread_message[thread_id];
}


//This function should grant or decline a thread depending on memory size.
void * server_function(void *)
{
	int MEMORY_INDEX;
	while (releaseCheck) {
		pthread_mutex_lock(&sharedLock);
		if(!myqueue.empty()){
			queueNode tempNode = myqueue.front();
			MEMORY_INDEX = memList.checkList(tempNode.size);
			if(MEMORY_INDEX != -1){
				memList.allocateMemory(tempNode.id, tempNode.size);
				for (size_t i = 0; i < tempNode.size; i++) {
					memory[MEMORY_INDEX+i] = tempNode.id;
				}
				//cout << "id: " << tempNode.id << " allocated: " << tempNode.size << endl;
				dump_memory();
				thread_message[tempNode.id] = MEMORY_INDEX;
			}
			else{
				thread_message[tempNode.id] = -1;
			}
			myqueue.pop();
			sem_post(&semlist[tempNode.id]);
		}
		pthread_mutex_unlock(&sharedLock);
	}
}

void * use_mem(int id){
	srand (time(NULL) +id);
	int randSize = rand() % 4;
	randSize++;
	sleep(randSize);
}

void * free_mem(int thread_id, int size){
	pthread_mutex_lock(&sharedLock);
	//cout << "id: " << thread_id << " DEallocated: " << size << endl;
	memList.freeTheMemory(thread_id, size, MEMORY_SIZE);
	for (size_t i = 0; i < size; i++){
		memory[thread_message[thread_id]+i] = -1;
	}
	pthread_mutex_unlock(&sharedLock);
}


void * thread_function(void * id_param)
{
	int cnt=0;
	int * id = (int*) id_param;
	srand (time(NULL) + *id);
	while (threadsControl) {
	  int randSize = rand() % (MEMORY_SIZE/3);
		int returnOfMalloc = my_malloc(*id,randSize+1);

		if(returnOfMalloc != -1){
			use_mem(*id);
			free_mem(*id,randSize+1);
		}
	}
}

void init()
{
	pthread_mutex_lock(&sharedLock);	//lock
	for(int i = 0; i < NUM_THREADS; i++) //initialize semaphores
	{
		sem_init(&semlist[i],0,0);
	}
	for (int i = 0; i < MEMORY_SIZE; i++)	//initialize memory
	{
			int x = -1; memory[i] = x;
	}
	memList.allocateMemory(-1,MEMORY_SIZE);
  pthread_create(&server,NULL,server_function,NULL); //start server
	pthread_mutex_unlock(&sharedLock); //unlock
}


int main (int argc, char *argv[])
 {
	//You need to create a thread ID array here
	pthread_t threads[NUM_THREADS];
  int thread_id[NUM_THREADS];

	for (size_t i = 0; i < NUM_THREADS; i++) {
		pthread_t temp;
		threads[i] = temp;
		thread_id[i] = i;
	}

 	init();	// call init

	for (int j = 0; j < NUM_THREADS; j++) {
		pthread_create( &threads[j], NULL, thread_function, (void *) & thread_id[j]);
	}


	sleep(10);
	threadsControl = false; // stopping threads

	// for (size_t k = 0; k < NUM_THREADS; k++) {
	// 	pthread_join(threads[k], NULL);
	// }
	release_function();


 	printf("\nTerminating...\n");
 }
