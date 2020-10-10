#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <queue>
#include <semaphore.h>
#include <time.h>
using namespace std;

#define NUM_THREADS 5
#define MEMORY_SIZE 1000

struct node
{
	int id;
	int size;
};

bool releaseCheck = true;
queue<node> myqueue; // shared que
pthread_mutex_t sharedLock = PTHREAD_MUTEX_INITIALIZER; // mutex
pthread_t server; // server thread handle
sem_t semlist[NUM_THREADS]; // thread semaphores

int thread_message[NUM_THREADS]; // thread memory information
char memory[MEMORY_SIZE]; // memory size

//This function will be called
//whenever the memory is no longer needed.
//It will kill all the threads and deallocate all the data structures.
void release_function()
{
  releaseCheck = false;
	while (!myqueue.empty()) {
		myqueue.pop();
	}
	for (size_t i = 0; i < NUM_THREADS; i++) {
		sem_destroy(&semlist[i]);
	}
}

//This function will add the struct to the queue
void my_malloc(int thread_id, int size)
{
	node temp;
	temp.id = thread_id;
	temp.size = size;
	myqueue.push(temp);
}

//This function should grant or decline a thread depending on memory size.
void * server_function(void *)
{
	int MEMORY_INDEX = 0;
	while (releaseCheck) {
		pthread_mutex_lock(&sharedLock);
		if(!myqueue.empty()){
			node tempNode = myqueue.front();
			myqueue.pop();
			if(tempNode.size < MEMORY_SIZE-MEMORY_INDEX){
				thread_message[tempNode.id] = MEMORY_INDEX;
				MEMORY_INDEX += tempNode.size;
        //cout << "memory " << MEMORY_INDEX << "  -" << tempNode.id<< endl;
			}
			else{
				thread_message[tempNode.id] = -1;
			}
			sem_post(&semlist[tempNode.id]);
		}
		pthread_mutex_unlock(&sharedLock);
	}
}

//This function will create a random size, and call my_malloc
void * thread_function(void * id_param)
{
  int * id = (int*) id_param;
	srand (time(NULL) + *id);
  int randSize = rand() % MEMORY_SIZE;

	pthread_mutex_lock(&sharedLock);
	if(randSize < MEMORY_SIZE){
		my_malloc(*id,randSize);
		pthread_mutex_unlock(&sharedLock);

		//Block
		sem_wait(&semlist[*id]); // down

		//Then fill the memory with 1's or give an error prompt
		if(thread_message[*id] == -1){
			printf("thread[%d]: Not enough memory\n" ,*id);
		}
		else{
			for (size_t i = 0; i < randSize; i++)
	      memory[thread_message[*id]+i] = '1';
		}
	}
	else
		pthread_mutex_unlock(&sharedLock);
  return NULL;
}

void init()
{
	pthread_mutex_lock(&sharedLock);	//lock
	for(int i = 0; i < NUM_THREADS; i++) //initialize semaphores
	{sem_init(&semlist[i],0,0);}
	for (int i = 0; i < MEMORY_SIZE; i++)	//initialize memory
  	{char zero = '0'; memory[i] = zero;}
   	pthread_create(&server,NULL,server_function,NULL); //start server
	pthread_mutex_unlock(&sharedLock); //unlock
}

// You need to print the whole memory array here.
void dump_memory()
{
	cout << "Memory Dump: \n";
	for (size_t i = 0; i < MEMORY_SIZE; i++) {
		cout << memory[i];
	}
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

 	//You need to create threads with using thread ID array, using pthread_create()
	for (int j = 0; j < NUM_THREADS; j++) {
		pthread_create( &threads[j], NULL, thread_function, (void *) & thread_id[j]);
	}

 	//You need to join the threads
	for (size_t k = 0; k < NUM_THREADS; k++) {
		pthread_join(threads[k], NULL);
	}

 	dump_memory(); // this will print out the memory
 	printf("\nMemory Indexes:\n" );
 	for (int i = 0; i < NUM_THREADS; i++)
 	{
 		printf("[%d]" ,thread_message[i]); // this will print out the memory indexes
 	}
 	printf("\nTerminating...\n");
	release_function();
 }
