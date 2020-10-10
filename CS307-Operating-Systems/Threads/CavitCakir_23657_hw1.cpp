/*
* For compilation: g++ -o pthread3.out pthread3.cpp -lpthread
*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
using namespace std;

//global variables
int turn = 0;
bool isPlaneFull = false;
int count = 100;
vector<vector<int> > planeVector(2,vector<int>(50));

void * travelAgencyThread(void * param)
{
  srand(time(NULL));
  int * paramPointer = (int*) param;
  while(!isPlaneFull){ // thredler cikabilsin diye
    while(!isPlaneFull && turn != *paramPointer); // busy wait
    bool emptyFound = false, out = false;
    while(!isPlaneFull && !emptyFound){ // koltuk bulana kadar
      if(!out){
        cout << "ATTENTION!! Agency "<< *paramPointer+1 <<" is talking I AM IN CRITICAL REGION!!!!\n";
        out = true;
      }
      int row = rand() % 2;
      int col = rand() % 50;
      if(!planeVector[row][col]){ // if we found a empty seat
        emptyFound = true;
        planeVector[row][col] = *paramPointer+1;
        count--;
        int seat;
        if(!((row)%2)){
          seat = (row+2)*(col+1);
          seat--;
        }
        else{
          seat = (row+1)*(col+1);
        }
        cout << "            Seat Number "<< seat <<" is reserved by TravelAgency"<<*paramPointer+1<<"\n";
        cout << "ATTENTION!! Agency "<< *paramPointer+1 <<" is talking I AM LEAVING CRITICAL REGION!!!!\n\n\n";
        if(turn == 0){
          turn = 1;
        }
        else if(turn == 1){
          turn = 2;
        }
        else{
          turn = 0;
        }
      }
    }
  }
}


int main()
{
	pthread_t thread1, thread2, thread3;
  int TravelAgency1 = 0, TravelAgency2 = 1, TravelAgency3 = 2;
	pthread_create( &thread1, NULL, travelAgencyThread, (void *) & TravelAgency1);
	pthread_create( &thread2, NULL, travelAgencyThread, (void *) & TravelAgency2);
  pthread_create( &thread3, NULL, travelAgencyThread, (void *) & TravelAgency3);

  while(!isPlaneFull)if(!count)isPlaneFull=true;

	pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

  cout << "Printing the plane\n";
  for (size_t i = 0; i < 2; i++) {
    cout << "Seat "<<i+1<<": ";
    for (size_t j = 0; j < 50; j++) {
      cout << planeVector[i][j] << " ";
    }
    cout << "\n";
  }
	return 0;
}
