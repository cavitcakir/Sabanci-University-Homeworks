//
//  main.cpp
//  hw4-cs300
//
//  Created by Cavit on 12.12.2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "MPQ.h"

using namespace std;

struct coordinate{
    int label, side, coord, heigth;
};

bool lessThan(coordinate & c1, coordinate c2){
    if((c1.coord < c2.coord) || (c1.coord == c2.coord && c1.side < c2.side) || (c1.coord == c2.coord && c1.side == c2.side && c1.side == 0 && c1.heigth > c2.heigth) || (c1.coord == c2.coord && c1.side == c2.side && c1.side == 1 && c1.heigth < c2.heigth))
        return true;
    return false;
}

void equals( vector<coordinate> & array, int  hole, int  child){
    array[hole].coord = array[child].coord;
    array[hole].heigth = array[child].heigth;
    array[hole].label = array[child].label;
    array[hole].side = array[child].side;
}


void percolateDown( int hole , int  currentSize , vector<coordinate> & array)
{
    int child;
    // tmp is the item that will
    coordinate tmp;
    
    tmp.coord = array[hole].coord;
    tmp.heigth = array[hole].heigth;
    tmp.label = array[hole].label;
    tmp.side = array[hole].side;
    // be percolated down
    
    for( ; hole * 2  < currentSize; hole = child )
    {
        child = hole * 2 ;
        if( child != currentSize-1 && lessThan(array[ child ], array[ child + 1]) )
            child++;  // child is the max of the children
        if( lessThan( tmp , array[ child ]) )
            equals(array,hole,child); // swap hole and min child
        else
            break;
    }
    // place tmp in its final position
    array[hole].coord = tmp.coord;
    array[hole].heigth = tmp.heigth;
    array[hole].label = tmp.label;
    array[hole].side = tmp.side;
}



void buildHeap( vector<coordinate> & array) // for the sorting
{
    
    for( int i = array.size() / 2; i >= 0; i-- )
        percolateDown( i, array.size() , array);

    for (int i=array.size()-1 ; i > 0; i--)
    {
        //Move current root to end
        coordinate temp;
        temp.coord = array[0].coord;
        temp.heigth = array[0].heigth;
        temp.label = array[0].label;
        temp.side = array[0].side;

        equals(array, 0, i);

        array[i].coord=temp.coord ;
        array[i].heigth=temp.heigth;
        array[i].label=temp.label;
        array[i].side=temp.side;

        // call max heapify on the reduced heap
        percolateDown(0, i, array);
    }
}

int main() {
    ifstream file;
    file.open("input.txt");
    
    int buildings, zero, height ,one, itr = 0;
    file >> buildings;
    
    vector<coordinate> coordinates(buildings*2);
    
    for(int i = 1; i <= buildings; i++ ){
        file >> zero >> height >> one;
        
        coordinates[itr].side = 0; // if the side is left
        coordinates[itr].coord = zero;
        coordinates[itr].heigth = height;
        coordinates[itr].label = i;
        
        itr++;
        
        coordinates[itr].side = 1; // if the side is right
        coordinates[itr].coord = one;
        coordinates[itr].heigth = height;
        coordinates[itr].label = i;

        itr++;
    }
    
    buildHeap(coordinates);
    
    //sortla bu listeyi
    //sonra tek tek al ve bak nedir bu ona gore insert-remove yap ve current max'i kontrol et
    // max degistiyse output ver degismediyse devam -> sortlu listenin sonuna kadar
    int currentMax = -1;
    
    BinaryHeap maxHeap(buildings); // created the MPQ object
    
    if (coordinates[0].coord != 0) // if the list is empty
        cout << 0 << " " << 0 << endl;
    
    for(int i = 0; i < coordinates.size();i++){
        if(coordinates[i].side == 0){ // if the coordinate is left one
            maxHeap.insert(coordinates[i].heigth, coordinates[i].label);
        }
        else{ // if the coordinate is right one
            maxHeap.deleteItem(coordinates[i].label);
        }
        if(maxHeap.findMax() != currentMax){ // if the height changes
            currentMax = maxHeap.findMax();
            cout << coordinates[i].coord << " " <<currentMax << endl;
        }
    }
    file.close();
    return 0;
}
