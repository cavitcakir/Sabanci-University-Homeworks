//
//  MPQ.h
//  hw4-cs300
//
//  Created by Cavit on 12.12.2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//

#ifndef MPQ_h
#define MPQ_h

#include <vector>
using namespace std;

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 0)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( value , label )       --> Insert value and label
// deleteItem( item )   --> Remove item
// Comparable findMax( )  --> Return biggest item
// bool isEmpty( )        --> Return true if empty; else false
// ******************ERRORS********************************
// If you don't enter wrong input there will be no errors :)


struct queueObject{
    int value;
    int label;
};


class BinaryHeap
{
public:
    explicit BinaryHeap( int capacity = 0 )
    : array( capacity + 1 ), locations(capacity + 1), currentSize{ 0 }
    {
    }
    
    ~BinaryHeap() {}
    
    bool isEmpty( ) const{
        return currentSize == 0;
    }
    
    const int  findMax( ) const{
        if( isEmpty( ) )
            return 0;
        return array[ 1 ].value;
    }
    
    void insert(const int & value, const int & label);
    int deleteItem( int & Item );
    
private:
    int currentSize; // Number of elements in heap
    
    vector<queueObject> array;   // The heap array
    vector<int> locations;
    
    void percolateDown( int hole );
};


void BinaryHeap::insert( const int & value, const int & label )
{
    int hole = ++currentSize;
    
    for( ; hole > 1 && value > array[ hole / 2 ].value; hole /= 2 ){
        array[ hole ].value = array[ hole / 2 ].value;
        array[ hole ].label = array[ hole/2 ].label;
        locations[array[hole].label] = hole ;
    }
    array[hole].value = value;
    array[hole].label = label;
    locations[array[hole].label] = hole ;
}



int BinaryHeap:: deleteItem( int & label ){
    int value = -1;
    if( !isEmpty( ) || locations[label] > 0 ){
        value = array[locations[label]].value;
    
        array[locations[label]].value = array[ currentSize ].value;
        array[locations[label]].label = array[currentSize].label;
        currentSize--;
        percolateDown(locations[label]);
        locations[label] = 0;
    }
    return value;
}

void BinaryHeap:: percolateDown( int hole ){
    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
        int child;
        int tmpValue = array[ hole ].value; // tmp is the item that will
        int tmpLabel = array[hole].label;
        // be percolated down
        
    for( ; hole * 2 <= currentSize; hole = child ){
        
        child = hole * 2;
        
        if( child != currentSize && array[ child + 1 ].value > array[ child ].value )
            child++;  // child is the minimum of the children
        
        if( array[ child ].value > tmpValue ){
            
            array[ hole ].value = array[ child ].value; // swap hole and min child
            array[hole].label = array[child].label;
            locations[array[hole].label] = hole;
        }
        else
            break;
    }
    array[ hole ].value = tmpValue; // place tmp in its final position
    array[hole].label = tmpLabel;
    locations[array[hole].label] = hole;
}



#endif /* MPQ_h */
