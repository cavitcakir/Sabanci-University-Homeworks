//
//  cavitcakir_hw1.cpp
//  homework1
//
//  Created by cavitcakir on 29/06/2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//
// The aim of this program is to recall CS201 material and practice on matrices (i.e., two
// dimensional vectors). Program asked to search for a list of words in a character matrix, just
// like we would do with Sunday morning puzzles. A score will be calculated at the end of the
// program according to the existence of the words and their directions in the matrix.

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

bool ToUpLeftJoker(vector<vector<string> > & puzzle,int & score, string input) // searches all matrix diagonal to find a keyword with one letter missing
{
    int length = int(input.length());
    bool flag = true;
    string first = input.substr(0,1);
    for (int j=0; j < puzzle.size(); j++)
    {
        for (int k=0; k < puzzle[0].size(); k++)
        {
            int count = 1, indexCount = 1, error = 0;
            if(first == puzzle[j][k] && j >= length-1 && k >= length-1)
            {
                
                bool flag2 = true;
               
                while(flag2 && indexCount < length && error < 2)
                {
                   
                    if(input.substr(indexCount,1) == puzzle[j-indexCount][k-indexCount] )
                    {
                        indexCount++;
                        count++;
                    }
                    else
                    {
                        indexCount++;
                        count++;
                        error++;
                    }
                    
                    if(error >1)
                    {
                        flag2 = false;
                        
                    }
                }
            }
            else
            {
                if(j >= length-1 && k >= length-1)
                {
                    bool flag2 = true;
                    while(flag2 && indexCount < length)
                    {
                        if(input.substr(indexCount,1) == puzzle[j-indexCount][k-indexCount] )
                        {
                            indexCount++;
                            count++;
                        }
                        else
                            flag2 = false;
                    }
                }
            }
            
            if (length == count && error < 2)
            {
                if(length>5)
                {
                    score = score + (length*2) ;
                    cout << input << " is found in the diagonal level. One letter was replaced by joker. It contributes "<<(length*2) <<" points." << endl;
                }
                else
                {
                    score = score + (length*2) -2 ;
                    cout << input << " is found in the diagonal level. One letter was replaced by joker. It contributes "<<(length*2) - 2 <<" points." << endl;
                }
                
       
                
                return true;
            }
            else
                flag = false;
        }
    }
    return flag;
}


bool ToUpLeft(vector<vector<string> > & puzzle,int & score, string input)  // searches all matrix diagonal to find a keyword
{
   int length = int(input.length());
    bool flag = true;
    string first = input.substr(0,1);
    for (int j=0; j < puzzle.size(); j++)
    {
        for (int k=0; k < puzzle[0].size(); k++)
        {
            int count = 1, indexCount = 1;
            if(first == puzzle[j][k] && j >= length-1 && k >= length-1)
            {
                
                bool flag2 = true;
                while(flag2 && indexCount < length)
                {
                    if(input.substr(indexCount,1) == puzzle[j-indexCount][k-indexCount] )
                    {
                        indexCount++;
                        count++;
                    }
                    else
                        flag2 = false;
                }
            }
            
            if (length == count)
            {
                if(length>5)
                {
                    score = score + (length*2) + 2;
                    cout << input << " is found in the diagonal level. It contributes "<<(length*2) + 2<<" points." << endl;
                }
                else
                {
                    score = score + (length*2);
                    cout << input << " is found in the diagonal level. It contributes "<<(length*2)<<" points." << endl;
                }
                
                return true;
            }
            else
                flag = false;
        }
    }
    return flag;
}

bool ToDownRightJoker(vector<vector<string> > & puzzle,int & score, string input) // searches all matrix diagonal to find a keyword with one letter missing
{
    int length = int(input.length());
    bool flag = true;
    string first = input.substr(0,1);
    for (int j=0; j < puzzle.size(); j++)
    {
        for (int k=0; k < puzzle[0].size(); k++)
        {
            int count = 1, indexCount = 1, error = 0;
            if(first == puzzle[j][k] && puzzle.size()-j >= length && puzzle[0].size()-k >= length)
            {
                
                bool flag2 = true;
                
                while(flag2 && indexCount < length && error < 2)
                {
                    
                    if(input.substr(indexCount,1) == puzzle[j+indexCount][k+indexCount] )
                    {
                        indexCount++;
                        count++;
                    }
                    else
                    {
                        indexCount++;
                        count++;
                        error++;
                    }
                    
                    if(error >1)
                    {
                        flag2 = false;
                        
                    }
                }
            }
            else
            {
                if(puzzle.size()-j >= length && puzzle[0].size()-k >= length)
             {
                bool flag2 = true;
                while(flag2 && indexCount < length)
                {
                    if(input.substr(indexCount,1) == puzzle[j+indexCount][k+indexCount] )
                    {
                        indexCount++;
                        count++;
                    }
                    else
                        flag2 = false;
                }
             }
            }
             
            if (length == count && error < 2)
            {
               
                if(length>5)
                {
                    score = score + (length*2) ;
                    cout << input << " is found in the diagonal level. One letter was replaced by joker. It contributes "<<(length*2) <<" points." << endl;
                }
                else
                {
                    score = score + (length*2) -2 ;
                    cout << input << " is found in the diagonal level. One letter was replaced by joker. It contributes "<<(length*2) - 2 <<" points." << endl;
                }
                
              
                
                
                
                
                return true;
            }
            else
                flag = false;
        }
    }
    return flag;
}



bool ToDownRight(vector<vector<string> > & puzzle,int & score, string input) // searches all matrix diagonal to find a keyword
{
   int length = int(input.length());
    bool flag = true;
    string first = input.substr(0,1);
    for (int j=0; j < puzzle.size(); j++)
    {
        for (int k=0; k < puzzle[0].size(); k++)
        {
            int count = 1, indexCount = 1;
            if(first == puzzle[j][k] && puzzle.size()-j >= length && puzzle[0].size()-k >= length)
            {
                
                bool flag2 = true;
                while(flag2 && indexCount < length)
                {
                    if(input.substr(indexCount,1) == puzzle[j+indexCount][k+indexCount] )
                    {
                        indexCount++;
                        count++;
                    }
                    else
                        flag2 = false;
                }
            }
            
            if (length == count)
            {
                
                if(length>5)
                {
                    score = score + (length*2) + 2;
                    cout << input << " is found in the diagonal level. It contributes "<<(length*2) + 2<<" points." << endl;
                }
                else
                {
                    score = score + (length*2);
                    cout << input << " is found in the diagonal level. It contributes "<<(length*2)<<" points." << endl;
                }
      
                
                
                return true;
            }
            else
                flag = false;
        }
    }
    return flag;
}

bool ToDown(vector<vector<string> > & puzzle,int & score, string input) // searches all matrix columns to find a keyword
{
   int length = int(input.length());
    bool flag = true;
    string first = input.substr(0,1);
    for (int j=0; j < puzzle.size(); j++)
    {
        for (int k=0; k < puzzle[0].size(); k++)
        {
            int count = 1, indexCount = 1;
            if(first == puzzle[j][k] && puzzle.size()-j >= length)
            {
                
                bool flag2 = true;
                while(flag2 && indexCount < length)
                {
                    if(input.substr(indexCount,1) == puzzle[j+indexCount][k] )
                    {
                        indexCount++;
                        count++;
                    }
                    else
                        flag2 = false;
                }
            }
            
            if (length == count)
            {
                if(length>5)
                {
                    score = score + length + 2;
                    cout << input << " is found in the column level. It contributes "<<length+2<<" points." << endl;
                }
                else
                {
                    score = score + length;
                    cout << input << " is found in the column level. It contributes "<<length<<" points." << endl;
                }
                
            
                
                
                return true;
            }
            else
                flag = false;
        }
    }
    return flag;
}

bool ToUp(vector<vector<string> > & puzzle,int & score, string input) // searches all matrix column to find a keyword
{
    int length = int(input.length());
    bool flag = true;
    string first = input.substr(0,1);
    for (int j=0; j < puzzle.size(); j++)
    {
        for (int k=0; k < puzzle[0].size(); k++)
        {
            int count = 1, indexCount = 1;
            if(first == puzzle[j][k] && j >= length-1)
            {
                
                bool flag2 = true;
                while(flag2 && indexCount < length)
                {
                    if(input.substr(indexCount,1) == puzzle[j-indexCount][k] )
                    {
                        indexCount++;
                        count++;
                    }
                    else
                        flag2 = false;
                }
            }
            
            if (length == count)
            {
                if(length>5)
                {
                    score = score + length + 2;
                    cout << input << " is found in the column level. It contributes "<<length+2<<" points." << endl;
                }
                else
                {
                    score = score + length;
                    cout << input << " is found in the column level. It contributes "<<length<<" points." << endl;
                }
                
          
                
                
                return true;
            }
            else
                flag = false;
        }
    }
    return flag;
}

bool ToLeft(vector<vector<string> > & puzzle,int & score, string input) // searches all matrix row to find a keyword
{
    int length = int(input.length());
    bool flag = true;
    string first = input.substr(0,1);
    int count = 1, indexCount = 1;
    for (int j=0; j < puzzle.size(); j++)
    {
        for (int k=0; k < puzzle[0].size(); k++)
        {
            if(first == puzzle[j][k] && k >= length-1)
            {
                
                bool flag2 = true;
                while(flag2 && indexCount < length)
                {
                    if(input.substr(indexCount,1) == puzzle[j][k-indexCount] )
                    {
                        indexCount++;
                        count++;
                    }
                    else
                        flag2 = false;
                }
            }
            
            if (length == count)
            {
                if(length>5)
                {
                    score = score + length + 2;
                    cout << input << " is found in the row level. It contributes "<<length+2<<" points." << endl;
                }
                else
                {
                    score = score + length;
                     cout << input << " is found in the row level. It contributes "<<length<<" points." << endl;
                }
               
           
              
                
                return true;
            }
            else
                flag = false;
        }
    }
    return flag;
}

bool ToRight(vector<vector<string> > & puzzle,int & score, string input) // searches all matrix row to find a keyword
{
    int length = int(input.length());
    bool flag = true;
    string first = input.substr(0,1);
    for (int j=0; j < puzzle.size(); j++)
    {   
        for (int k=0; k < puzzle[0].size(); k++)
            {
                int count = 1, indexCount = 1;
                if(first == puzzle[j][k] && puzzle[j].size()-k >= length)
                {
                    
                    bool flag2 = true;
                    while(flag2 && indexCount < length)
                    {
                        if(input.substr(indexCount,1) == puzzle[j][k+indexCount] )
                        {
                            indexCount++;
                            count++;
                        }
                        else
                            flag2 = false;
                    }
                }
                
               if (length == count)
                {
                    if(length>5)
                    {
                        score = score + length + 2;
                        cout << input << " is found in the row level. It contributes "<<length+2<<" points." << endl;
                    }
                    else
                    {
                        score = score + length;
                        cout << input << " is found in the row level. It contributes "<<length<<" points." << endl;
                    }
                    
                    
                    
                    return true;
                }
                else
                    flag = false;
            }
    }
    return flag;
}


void matrixFill(vector<vector<string> > & puzzle, ifstream & file) // fills the matrix with strings taken from txt
{
    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string ch;
        vector<string> temp;
        
        while(ss >> ch)
        {
            for(int a = 0; a< ch.length();a++)
            {
                string b = ch.substr(a,1);
                temp.push_back(b);
            }
        }
        puzzle.push_back(temp);
    }
}

void fileOpener(ifstream & fileConstructor,string & fileName) // opens txt file
{
    fileConstructor.open(fileName.c_str());
    
    while (fileConstructor.fail())
    {
        cout <<"Invalid file name!"<< endl; 
        cout << "---" << endl;
        cout <<"Enter the matrix file name: "; 
        cin >> fileName;
        fileConstructor.open(fileName.c_str());
    }
}

int main()
{
    string inputFile,input;
    ifstream file;
    vector<vector<string> > puzzle;
    int score = 0;
    cout << "This program allows you to play a Sunday morning puzzle on your computer."<< endl;
    cout << "---"<< endl;
    cout <<"Enter the matrix file name: "; 
    cin >> inputFile;
    fileOpener(file,inputFile);
    
    matrixFill(puzzle, file);
    long rows = puzzle.size();
    int temp = 0;
    bool flag = true;
    long cols = puzzle[0].size();
   
     while(temp < rows && flag)
     {
     if(cols != puzzle[temp].size())
     flag = false;
         temp++;
     }
    
    if(flag)
    {
        do {
            cout << "---"<< endl;
                cout << "Enter a word: ";
                cin >> input;
                if(input.length()>2)
                {
                    if(!ToRight(puzzle,score,input))
                    {
                        if(!ToLeft(puzzle,score,input))
                        {
                            if(!ToUp(puzzle, score, input))
                            {
                                if(!ToDown(puzzle, score, input))
                                {
                                    if(!ToDownRight(puzzle, score, input))
                                    {
                                        if(!ToUpLeft(puzzle, score, input))
                                        {
                                           if(!ToDownRightJoker(puzzle,score,input))
                                           {
                                                 if(ToUpLeftJoker(puzzle, score, input))
                                                    {
                                                    
                                                    }
                                               else
                                               {
                                                   cout<< input << " is not found in the matrix. 5 points are deducted."<< endl;
                                                  
                                                   score= score-5;
                                               }
                                            }
                                                    
                                         
                                        }
                                       
                                    }
                                            
                                }
                            }
                        }
                    }
                }
            
            
            
    
    }while(input.length() > 2);

        cout  << "---"<< endl;
        cout << "Game has ended." << endl;
        cout << "Total score of the words: " << score<< endl;
    }
    else 
        cout << "The matrix does not have row equality, terminating..." << endl;
    return 0;
}


