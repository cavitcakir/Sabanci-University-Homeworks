//
//  HashTable.h
//  hw3
//
//  Created by Cavit on 24.11.2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct returnType
{
    int probe;
    bool Type;
    
    returnType(int p = 1, bool t = true) : probe(p), Type(t)
    {
    }
};

bool isPrime ( int x ){ // returns if x is a prime number
    for(int i = 2; i <= x / 2; ++i)
    {
        if(x % i == 0)
        {
            return false;
        }
    }
    return true;
}

int nextPrime( int n ) // finds smallest next prime number
{
    if( n % 2 == 0 )
        n++;
    
    for( ; !isPrime( n ); n += 2 )
        ;
    
    return n;
}

class HashTable
{
public:
    explicit HashTable(int size = 10000 ); // constructor
    returnType contains( const int & x) const; // tries to find and returns probe number
    
    void makeEmpty( ); // make the table empty
    returnType insert( const int & x ); // inserting new number to the table
    returnType remove( const int & x ); // removing from table
    int getCurrentSize(){ // returns currentSize
        return currentSize;
    };
    int getTotalSize(){ // returns totalSize
        return totalSize;
    };
    enum EntryType { ACTIVE, EMPTY, DELETED }; // types to check if its active, empty or deleted
    
private:
    struct HashEntry
    {
        int element;
        EntryType info;
        
        HashEntry( const int & e = int( ), EntryType i = EMPTY )
        : element( e ), info( i ) { }
    };
    
    vector<HashEntry> array;
    int currentSize;
    int totalSize;
    
    bool isActive( int currentPos ) const{ // returns if currentPos is active or not
        return array[currentPos].info == ACTIVE;
    };
    
    int findPos( const int & x, int & probe ) const; // finds position of x and returns it, increments probe count too.
    int myhash(const int & x) const{ // x mod M
        return x % totalSize;
    };
};


void HashTable::makeEmpty()
{
    currentSize = 0;
    for (auto & entry : array)
        entry.info = EMPTY;
}

int HashTable::findPos(const int & x,int & probe) const{
    int pos = myhash(x);
    while(array[pos].info == ACTIVE && array[pos].element != x){
        pos++;
        probe++;
        
        if( pos >= array.size( ) )
            pos -= array.size( );
    }
    return pos;
}

HashTable::HashTable( int size ) :  array(nextPrime( size )), totalSize(nextPrime(size))
{
    makeEmpty();
}


returnType HashTable::contains( const int & x) const{
    int probe = 1;
    if(isActive( findPos( x, probe ) ))
        return returnType(probe,true);
    else
        return returnType(probe,false);
}

returnType HashTable::insert( const int & x ){
    int probe = 1;
    int currentPos = findPos( x , probe );
    if(isActive( currentPos ) )
        return returnType(probe,false);
    
    array[ currentPos ].element = x;
    array[ currentPos ].info = ACTIVE;
    currentSize++;
    
    return returnType(probe,true);
}

returnType HashTable::remove(const int & x){
    
    int probe = 1;
    int currentPos = findPos( x, probe );
    if(!isActive(currentPos))
        return returnType(probe,false);
    
    array[currentPos].info = DELETED;
    currentSize--;
    return returnType(probe,true);
}



#endif /* HashTable_h */
