//
//  main.cpp
//  hw2 decompressor
//
//  Created by Cavit on 13.11.2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    int index = 256;
    
    string a[4096];
    for(int i = 0; i<256 ; i++){
        a[i] = i;
    }
    
    ifstream file;
    string fileName = "compout.txt", line;
    file.open(fileName.c_str());
    
    ofstream myfile;
    myfile.open ("decompout.txt");
    
    int code;
    string w, temp;
    string outText = "";
    
    file >> code;
    w = a[code];
    outText += w;
    
    while (file >> code) { // while we can read input
        if(a[code] != ""){ // if we have that in our array
            temp = w;
            w = a[code];
            a[index] = temp + w[0];
            index++;
        }else{ // if we dont have that input in our array
            a[index] = w + w[0];
            w = a[code];
            index++;
        }
        outText += w;
    }
    myfile << outText;
    
    myfile.close();
    file.close();
    return 0;
}
