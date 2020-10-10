//
//  main.cpp
//  hw3
//
//  Created by Cavit on 24.11.2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//

#include <iostream>
#include <stdlib.h> // random
#include "HashTable.h"
#include <fstream>
#include <iomanip> // std::setprecision

using namespace std;

struct element {
    element(): probe(0),transactions(0){}
    double probe ;
    int transactions;
};

void toFile(double** insertionSuccess2D,double** insertionFailure2D,double** removeSuccess2D,double** removeFailure2D,double** findSuccess2D,double** findFailure2D,int size){
    ofstream insertSuccessOS,insertFailureOS,removeSuccessOS,removeFailureOS,findSuccessOS,findFailureOS;
    insertSuccessOS.open("insertSuccess.csv");
    insertFailureOS.open("insertFailure.csv");
    removeSuccessOS.open("removeSuccess.csv");
    removeFailureOS.open("removeFailure.csv");
    findSuccessOS.open("findSuccess.csv");
    findFailureOS.open("findFailure.csv");
    
    insertSuccessOS << fixed << setprecision(4);
    insertFailureOS << fixed << setprecision(4);
    removeSuccessOS << fixed << setprecision(4);
    removeFailureOS << fixed << setprecision(4);
    findSuccessOS << fixed << setprecision(4);
    findFailureOS << fixed << setprecision(4);
    
    
    
    
    for(int a = 0; a <= size; a++)
    {
        double r = (double) a/size;
        
        insertSuccessOS << r;
        for(int i = 0; i<3; i++){
            if( insertionSuccess2D[i][a])
                insertSuccessOS << "," << insertionSuccess2D[i][a];
        }
        insertSuccessOS << endl;
        
        insertFailureOS << r ;
        for(int i = 0; i<3; i++){
            insertFailureOS << "," << insertionFailure2D[i][a];
        }
        insertFailureOS << endl;
        
        removeSuccessOS << r;
        for(int i = 0; i<3; i++){
            removeSuccessOS << "," << removeSuccess2D[i][a];
        }
        removeSuccessOS << endl;
        
        removeFailureOS << r ;
        for(int i = 0; i<3; i++){
            removeFailureOS << "," << removeFailure2D[i][a];
        }
        removeFailureOS << endl;
        
        findSuccessOS << r;
        for(int i = 0; i<3; i++){
            findSuccessOS << "," << findSuccess2D[i][a];
        }
        findSuccessOS << endl;
        
        findFailureOS << r ;
        for(int i = 0; i<3; i++){
            findFailureOS << "," << findFailure2D[i][a];
        }
        findFailureOS << endl;
    }
    insertSuccessOS.close();
    insertFailureOS.close();
    removeSuccessOS.close();
    removeFailureOS.close();
    findSuccessOS.close();
    findFailureOS.close();
}

int chooseSelect(const int & number , const int & combination){ // 0 for 6-1-1 ~~ 1 for 4-2-2 ~~ 2 for 2-1-5
    if(combination == 0){
        if(number < 6)
            return 0; // insert
        else if(number < 7)
            return 1; // delete
        else
            return 2; // find
    }
    else if(combination == 1){
        if(number < 4)
            return 0; // insert
        else if(number < 6)
            return 1; // delete
        else
            return 2; // find
    }else{
        if(number < 2)
            return 0; // insert
        else if(number < 3)
            return 1; // delete
        else
            return 2; // find
    }
}

int main() {
    
    HashTable table;
    int size = table.getTotalSize();
    
    double** insertionSuccess2D = new double*[3];
    for(int i = 0; i < 3; i++){
        insertionSuccess2D[i] = new double[size+1];
    }
    for(int i = 0 ; i <size+1; i++){
        insertionSuccess2D[0][i] = 0.0;
        insertionSuccess2D[1][i] = 0.0;
        insertionSuccess2D[2][i] = 0.0;
    }
    
    double** insertionFailure2D = new double*[3];
    for(int i = 0; i < 3; i++)
        insertionFailure2D[i] = new double[size+1];
    
    for(int i = 0 ; i <size+1; i++){
        insertionFailure2D[0][i] = 0.0;
        insertionFailure2D[1][i] = 0.0;
        insertionFailure2D[2][i] = 0.0;
    }
    
    double** removeSuccess2D = new double*[3];
    for(int i = 0; i < 3; i++)
        removeSuccess2D[i] = new double[size+1];
    
    for(int i = 0 ; i <size+1; i++){
        removeSuccess2D[0][i] = 0.0;
        removeSuccess2D[1][i] = 0.0;
        removeSuccess2D[2][i] = 0.0;
    }
    
    
    double** removeFailure2D = new double*[3];
    for(int i = 0; i < 3; i++)
        removeFailure2D[i] = new double[size+1];
    for(int i = 0 ; i <size+1; i++){
        removeFailure2D[0][i] = 0.0;
        removeFailure2D[1][i] = 0.0;
        removeFailure2D[2][i] = 0.0;
    }
    
    double** findSuccess2D = new double*[3];
    for(int i = 0; i < 3; i++)
        findSuccess2D[i] = new double[size+1];
    for(int i = 0 ; i <size+1; i++){
        findSuccess2D[0][i] = 0.0;
        findSuccess2D[1][i] = 0.0;
        findSuccess2D[2][i] = 0.0;
    }
    
    
    double** findFailure2D = new double*[3];
    for(int i = 0; i < 3; i++)
        findFailure2D[i] = new double[size+1];
    for(int i = 0 ; i <size+1; i++){
        findFailure2D[0][i] = 0.0;
        findFailure2D[1][i] = 0.0;
        findFailure2D[2][i] = 0.0;
    }
    
    
    for(int i = 0; i < 3 ; i++){
        table.makeEmpty();
        
        element* insertionSuccess = new element[size+1];
        element* insertionFailure = new element[size+1];
        element* removeSuccess = new element[size+1];
        element* removeFailure = new element[size+1];
        element* findSuccess = new element[size+1];
        element* findFailure = new element[size+1];
        
        srand(1);
        int transactions = 1000000;
        while(transactions && table.getCurrentSize() < size){
            
            int choose = chooseSelect(rand() % 8, i);
            
            int toTransaction = rand() % (size * 10);
            
            int currentsize = table.getCurrentSize();
            
            
            if(choose == 0){ // insert
                returnType probeOfInsertion = table.insert(toTransaction);
                
                if( probeOfInsertion.Type){
                    insertionSuccess[currentsize].probe += probeOfInsertion.probe;
                    insertionSuccess[currentsize].transactions++;
                }else{
                    insertionFailure[currentsize].probe += probeOfInsertion.probe;
                    insertionFailure[currentsize].transactions++;
                }
            }else if(choose == 1){ // delete
                returnType probeOfRemove = table.remove(toTransaction);
                
                if( probeOfRemove.Type){
                    removeSuccess[currentsize].probe += probeOfRemove.probe;
                    removeSuccess[currentsize].transactions++;
                }else{
                    removeFailure[currentsize].probe += probeOfRemove.probe;
                    removeFailure[currentsize].transactions++;
                }
            }else{ // find
                returnType probeOfFind = table.contains(toTransaction);
                
                if( probeOfFind.Type){
                    findSuccess[currentsize].probe += probeOfFind.probe;
                    findSuccess[currentsize].transactions++;
                }else {
                    findFailure[currentsize].probe += probeOfFind.probe;
                    findFailure[currentsize].transactions++;
                }
            }
            
            transactions--;
        }
        for(int j = 0; j < size+1; j++)
        {
            if(insertionSuccess[j].transactions != 0)
                insertionSuccess2D[i][j] = insertionSuccess[j].probe / insertionSuccess[j].transactions;
            if(insertionFailure[j].transactions != 0)
                insertionFailure2D[i][j] = insertionFailure[j].probe / insertionFailure[j].transactions;
            
            if(removeSuccess[j].transactions != 0)
                removeSuccess2D[i][j] = removeSuccess[j].probe / removeSuccess[j].transactions;
            if(removeFailure[j].transactions != 0)
                removeFailure2D[i][j] = removeFailure[j].probe / removeFailure[j].transactions;
            
            if(findSuccess[j].transactions != 0)
                findSuccess2D[i][j] = findSuccess[j].probe / findSuccess[j].transactions;
            if(findFailure[j].transactions != 0)
                findFailure2D[i][j] = findFailure[j].probe / findFailure[j].transactions;
        }
    }
    toFile(insertionSuccess2D,insertionFailure2D,removeSuccess2D,removeFailure2D,findSuccess2D,findFailure2D,size);
    return 0;
}
