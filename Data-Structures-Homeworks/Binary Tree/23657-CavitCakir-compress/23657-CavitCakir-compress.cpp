//
//  main.cpp
//  hw2 :(
//
//  Created by Cavit on 13.11.2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include "bts.h"
#include <fstream>
#include "strutils.h"

using namespace std;

int main( )
{
    int index = 256;
    
    const string ITEM_NOT_FOUND = "";
    BinarySearchTree<string> t( ITEM_NOT_FOUND );
    
    ifstream file;
    string fileName = "compin.txt";
    file.open(fileName.c_str());
    
    ofstream myfile;
    myfile.open ("compout.txt");
    
    string theOutput = "";
    bool empty = false;
    string s;
    char ch;
    file>>ch;
    s = ch;

    while(file.get(ch)){ // while we can read
        if(t.find(s+ch) != -1){ // if that sequence exists
            s = s+ch;
        }else{
            if(t.find(s) == -1){ // if its before 256
                theOutput += itoa((int)s[0]) + " ";
            }else
                theOutput += itoa(t.find(s)) + " ";
            
            if((s+ch).length() > 1){ // if length is bigger than 1
                t.insert(s+ch, index);
                index++;
            }
            s=ch;
        }
        empty = true;
    }
    if(empty){ // for last input
        if(t.find(s) == -1){
            theOutput += itoa((int)s[0]) + " ";
        }else
            theOutput += itoa(t.find(s)) + " ";
    }
      
    myfile << theOutput;
    myfile.close();

    file.close();
    return 0;
}


