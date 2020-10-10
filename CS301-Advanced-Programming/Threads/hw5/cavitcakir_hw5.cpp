//
//  main.cpp
//  hw5
//
//  Created by cavit on 05/08/2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//


#include <iostream>
#include <thread>
#include "randgen.h"
#include "Queue.h"
#include <string>
#include <fstream>
#include <ostream>
#include "DynamicStringStack.h"
#include <mutex>
#include <chrono>
#include <sstream>

using namespace std;

mutex consMutex;
mutex prodMutex;
mutex coutMutex;

bool endd = false;
bool conss=false;


void consumer(Queue & mainQue, int i)    // These threads love sleeping as well, as we all do. They sleep for a random
//time between 2500 to 3500 milliseconds before trying ​to do anything.
//These threads will first try to dequeue a file name from the main queue.
//If the dequeuing is successful (i.e, queue is not empty), the thread will open the file, decrypt it
//and write the result to another file.
{
    
    while(!conss)
    {
        RandGen a;
        int randomNum =a.RandInt(2500, 3500);
        
        coutMutex.lock();
        cout << "Consumer Thread - "<< i+1 <<" starts sleeping for " << randomNum <<" milliseconds\n";
        coutMutex.unlock();
        
        this_thread::sleep_for (chrono::milliseconds(randomNum));
        
        consMutex.lock();
        if(!mainQue.isEmpty())
        {
            int total[26] = {0};
            
            string name;
            string line;
            mainQue.dequeue(name);
            
            consMutex.unlock();
            
            coutMutex.lock();
            cout <<"Consumer Thread - "<< i+1 <<" is now handling "<< "\"" << name << "\""<< endl;
            coutMutex.unlock();
            
            
            
            ifstream file;
            file.open(name.c_str());
            if(!file.fail())
            {
                
                while(getline(file, line))
                {
                    stringstream ss(line);
                    char word;
                    while(ss >> word)
                    {
                        if((word >= 'a' && word <= 'z'))
                        {
                            int i = int(word) - int('a');
                            total[i]++;
                        }
                    }
                }
                int maxx = 0;
                char maxChar = '\0';
                int count = 0;
                for(int g = 0; g<26; g++)
                {
                    count = total[g];
                    if(count > maxx)
                    {
                        maxx = count;
                        maxChar = char('a'+ g);
                    }
                }
                
                
                int shift = int(maxChar) - int('e');
                
                file.clear();
                file.seekg(0);
                
                string filename = name.substr(0,name.length()-4);
                filename = filename + "_decrypted.txt";
                ofstream outFile;
                outFile.open(filename.c_str());
                char input;
                while(file.get(input))
                {
                    
                    if((input >= 'a' && input <= 'z'))
                    {
                        if((input-shift) < 'a')
                        {
                            input = char(input + 26);
                        }
                        else if((input-shift) > 'z')
                        {
                            input = char(input - 26);
                        }
                        else
                            input = input;
                        
                        input = char(input - shift);

                        outFile << input;
                    }
                    else
                    {
                        outFile << input;
                    }
                }
                outFile.close();
                
                
                coutMutex.lock();
                cout <<"Consumer Thread - "<< i+1 <<" is done handling " << "\"" << name << "\"" << " with a shift of "<< shift <<" and written the result to  " << "\"" << filename <<"\"\n";
                coutMutex.unlock();
                
                consMutex.lock();
                if(endd)
                {
                    consMutex.unlock();
                    RandGen a;
                    int randomNum =a.RandInt(2500, 3500);
                    
                    coutMutex.lock();
                    cout << "Consumer Thread - "<< i+1 <<" starts sleeping for " << randomNum <<" milliseconds\n";
                    coutMutex.unlock();
                    
                    this_thread::sleep_for (chrono::milliseconds(randomNum));
                }
                else
                    consMutex.unlock();
                
            }
            else
            {
                coutMutex.lock();
                cout << "Consumer Thread - "<<i+1<<" cannot process " << "\"" << name << "\"" << ", there is no such file!\n";
                coutMutex.unlock();
                file.close();
                consMutex.lock();
                if(endd)
                {
                    consMutex.unlock();
                    RandGen a;
                    int randomNum =a.RandInt(2500, 3500);
                    
                    coutMutex.lock();
                    cout << "Consumer Thread - "<< i+1 <<" starts sleeping for " << randomNum <<" milliseconds\n";
                    coutMutex.unlock();
                    
                    this_thread::sleep_for (chrono::milliseconds(randomNum));
                }
                else
                    consMutex.unlock();
                
                
            }
            
        }
        else
        {
            
            consMutex.unlock();
            if (endd == false)
            {
                coutMutex.lock();
                cout << "Consumer Thread - "<< i+1 <<" cannot find any file to dequeue for now.\n";
                coutMutex.unlock();
            }
            else
            {
                conss =true;
            }
        }
        
    }
    ostringstream os;
    os << "Consumer Thread - "<< i+1 <<" cannot find any file to dequeue, joining...\n";
    cout<<os.str();
}

void producer(DynamicStringStack & fileNames, Queue & mainQue, int i)   //These threads have one simple duty: They need to get a file name from the
//structure of your choice and place it into the main queue.
{
    
    
    while(!endd){
        
        RandGen a;
        int randomNum =a.RandInt(1000, 4000);
        coutMutex.lock();
        cout << "Producer Thread - "<< i+1 <<" starts sleeping for "<< randomNum <<" milliseconds\n";
        coutMutex.unlock();
        
        this_thread::sleep_for (chrono::milliseconds(randomNum));
        string name;
        
        prodMutex.lock();
        
        if(!fileNames.isEmpty())
        {
            fileNames.pop(name);
            mainQue.enqueue(name);
            
            prodMutex.unlock();
            
            coutMutex.lock();
            cout << "Producer Thread - " << i+1 << " is now enqueuing \""<< name << "\""<< endl;
            coutMutex.unlock();
            
        }
        else
        {
            endd = true;
            prodMutex.unlock();
        }
    }
    ostringstream os;
    os << "Producer Thread - "<< i+1 <<" cannot find any file to enqueue, joining...\n";
    cout<<os.str();
}


int main()
{
    string input;
    DynamicStringStack fileNames;
    Queue mainQue;
    do {
        cout << "Please enter a file name:";
        cin >> input;
        cout << endl;
        if(input != "-")
        {
            fileNames.push(input);
        }
        
    } while (input != "-");
    
    thread threads[2];
    thread threadss[3];
    
    for(int i = 0; i<2; i++)
        threads[i] = thread(&producer,ref(fileNames),ref(mainQue),i);
    
    for(int i =0; i<3; i++)
        threadss[i] = thread(&consumer, ref(mainQue),i);
    
    for(int i =0; i<2; i++)
    {
        threads[i].join();

        
    }
    for(int i =0; i<3; i++)
    {
        threadss[i].join();

    }
    cout << "All threads have joined with main, exiting...\n";
    mainQue.clear();
    
    return 0;
}










