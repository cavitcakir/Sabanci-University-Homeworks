//
//  main.cpp
//  hw3
//
//  Created by cavit on 16/07/2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//

#include <iostream>
#include "DynIntStack.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void accordingToOne(DynIntStack & temp,DynIntStack & firstStack, DynIntStack & secondStack) // Option “1” means that the common words will be
                                                                                            // displayed in the order that they appear in the
{                                                                                           // first file.
    string first,second,temp2;

    while(!firstStack.isEmpty())
    {
        int countSec = 0, countFirst = 1;
        firstStack.pop(first);
        while(!secondStack.isEmpty())
        {
            secondStack.pop(second);
            
            if(first == second)
            {
                countSec++;
            }
            else
                temp.push(second);
        }
        while(!temp.isEmpty())
        {
            temp.pop(second);
            secondStack.push(second);
        }
        
        while(!firstStack.isEmpty())
        {
            firstStack.pop(temp2);
                
                if(first == temp2)
                {
                    countFirst++;
                }
                else
                    temp.push(temp2);
        }
        while(!temp.isEmpty())
        {
            temp.pop(temp2);
            firstStack.push(temp2);
        }
        
        if( countFirst <= countSec  && (countFirst != 0 && countSec != 0))
            cout << "The word \""<< first <<"\" occurred at least "<< countFirst <<" time(s) in both files.\n";
        else if ( countFirst >= countSec  && (countFirst != 0 && countSec != 0))
            cout << "The word \""<< first <<"\" occurred at least "<< countSec <<" time(s) in both files.\n";
    }
}


void accordingToTwo(DynIntStack & temp,DynIntStack & secondStack, DynIntStack & firstStack) // Option “1” means that the common words will be
                                                                                            // displayed in the order that they appear in the
{                                                                                           // first file.
    string first,second,temp2;
    
    while(!firstStack.isEmpty())
    {
        int countSec = 0, countFirst = 1;
        firstStack.pop(first);
        while(!secondStack.isEmpty())
        {
            secondStack.pop(second);
            
            if(first == second)
            {
                countSec++;
            }
            else
                temp.push(second);
        }
        while(!temp.isEmpty())
        {
            temp.pop(second);
            secondStack.push(second);
        }
        
        while(!firstStack.isEmpty())
        {
            firstStack.pop(temp2);
            
            if(first == temp2)
            {
                countFirst++;
            }
            else
                temp.push(temp2);
        }
        while(!temp.isEmpty())
        {
            temp.pop(temp2);
            firstStack.push(temp2);
        }
        
        if( countFirst <= countSec  && (countFirst != 0 && countSec != 0))
            cout << "The word \""<< first <<"\" occurred at least "<< countFirst <<" time(s) in both files.\n";
        else if ( countFirst >= countSec  && (countFirst != 0 && countSec != 0))
            cout << "The word \""<< first <<"\" occurred at least "<< countSec <<" time(s) in both files.\n";
    }
}
void stackFiller(ifstream & file1, ifstream & file2, DynIntStack & temp, DynIntStack & firstStack, DynIntStack & secondStack)
{                                                                                                                       // This function fills the
                                                                                                                        // stacks.
    string line;
    while(getline(file1, line))
    {
        stringstream ss(line);
        string word;
        while(ss >> word)
        {
            temp.push(word);
        }
    }
    while(!temp.isEmpty())
    {
        string word;
        temp.pop(word);
        firstStack.push(word);
    }
    
    while(getline(file2, line))
    {
        stringstream ss(line);
        string word;
        while(ss >> word)
        {
            temp.push(word);
        }
    }
    while(!temp.isEmpty())
    {
        string word;
        temp.pop(word);
        secondStack.push(word);
    }
}

void fileOpener(ifstream & fileConstructor,string & fileName, string count) // opens txt file
{
    fileConstructor.open(fileName.c_str());
    
    while (fileConstructor.fail())
    {
        cout <<"Enter the "<<count<<" file name: ";
        cin >> fileName;
        fileConstructor.open(fileName.c_str());
    }
}

int main()
{
    ifstream file1, file2;
    string first, second;
    cout <<"This program finds the common words of two files using stacks.\n---\n";
    cout <<"Enter the first file name: ";
    cin >> first;
    fileOpener(file1, first, "first");
    cout <<"Enter the second file name: ";
    cin >> second;
    fileOpener(file2, second, "second");
    
    DynIntStack temp, firstStack, secondStack;

    stackFiller(file1,file2,temp, firstStack, secondStack);
    
    int select;
    do
    {
    cout << "Choose with respect to which file the result will be sorted to (1: first file, 2: second file): ";
    
    cin >> select;
    
    if(cin.fail() || (select != 1 && select != 2))
    {
        cout << "---\n" << "Invalid choice\n---\n";
        cin.clear();
        cin.ignore(1024, '\n');
    }
    }while(cin.fail() || (select != 1 && select != 2));
    
    cout << "---\n";
    
    if(select == 1)
        accordingToOne(temp, firstStack, secondStack);
    else
        accordingToTwo(temp, firstStack, secondStack);
    
    return 0;
}
