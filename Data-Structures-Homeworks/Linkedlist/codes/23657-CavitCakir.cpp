//
//  main.cpp
//  CS-300-HW1
//
//  Created by Cavit on 22.10.2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "strutils.h"
#include "linkedlist.h"

using namespace std;

void loopF(LinkedList<string> & list , string firstInput, int wordNum, stringstream & ss2 ){ // this function takes inputs and compares them and gives output
    vector<int> commonFiles;
    vector<int> compare1;
    vector<int> compare2;

    bool flag = true;

    node<string> * checker = list.returnNode(firstInput);
    if(checker != NULL){
        compare1 = checker->numList->infos();

        for(wordNum; wordNum > 0 ; wordNum--){
            string tempInput;
            ss2 >> tempInput;
            cout << tempInput << " ";
            node<string> * checker2 = list.returnNode(tempInput);
            if(checker2 == NULL){
                flag = false;
                continue;
            }
            compare2 = checker2->numList->infos();
            int j = 0, i = 0;
            while(i< compare1.size() && j < compare2.size()){
                if(compare1[i] == compare2[j]){
                    commonFiles.push_back(compare1[i]);
                    i++;
                    j++;
                }
                else if(compare1[i] < compare2[j]){
                    i++;
                }
                else if(compare1[i] > compare2[j]){
                    j++;
                }
            }
            while(compare1.size() != 0){
                compare1.pop_back();
            }
            unsigned long size = commonFiles.size();

            while (size != 0) {
                int a;
                a = commonFiles[size-1];
                commonFiles.pop_back();

                compare1.insert(compare1.begin(), a);
                size--;
            }
        }

    }
    else{
        flag = false;
        string tempInput;
        while (ss2 >> tempInput)
            cout << tempInput << " ";
    }


    if(flag){

        cout << compare1.size() << " ";
        for(int a = 0; a < compare1.size() ; a++){
            cout << compare1[a] << " " ;
        }
        cout << endl;
    }
    else{
        cout << "0" << endl;
    }
}

int main() {
    ifstream file;
    string fileName = "docdb.txt", line;
    file.open(fileName.c_str());
    LinkedList<string> list;
    
    while(getline(file, line)){ // this while fills the linked lists
        stringstream ss(line);
        string name;
        int docNum;
        ss >> name;
        ss >> docNum;
        
        node<string> * checker = list.returnNode(name);
        if(checker == NULL)
            list.AddInOrder(name, docNum);
        else
            checker->numList->AddInOrder(docNum);
    }

    // list.printList();
    int wordNum;

    while(true){ // this while takes inputs
        cout << "enter input: ";
        string input;
        getline(cin, input);
        stringstream ss2(input);
        ss2>>wordNum;
        if (wordNum == 0)
            return 0;
        string firstInput;
        ss2 >> firstInput;
        cout << firstInput << " ";
        wordNum--;
        loopF(list,firstInput,wordNum,ss2);
    }
    return 0;
}
