#include "strutils.h"
#include <cctype>
#include <cstdlib>
#include <cassert>
#include <sstream>
using namespace std;

void ToLower(string & s)
// postcondition: s all lower case     
{
    int len = s.length();
    for(int k=0; k < len; k++)
    {
        s[k] = tolower(s[k]);
    }
}

void ToUpper(string & s)
// postcondition: s all lower case     
{
    int len = s.length();
    for(int k=0; k < len; k++)
    {
        s[k] = toupper(s[k]);
    }
}

string UpperString(const string & s)
{
    string word = s;
    ToUpper(word);
    return word;
}

string LowerString(const string & s)
{
    string word = s;
    ToLower(word);
    return word;
}


void StripPunc(string & word)
{
    int first = 0;
    int len = word.length();
    
    while (first < len && ispunct(word[first]))
    {    
        first++;
    }
    // assert: first indexes either '\0' or non-punctuation
    
    // now find last non-nonpunctuation character

    int last = len - 1;  // last char in s
    
    while(last >= 0 && ispunct(word[last]))
    {
        last--;
    }
    word = word.substr(first,last-first+1);
}

void StripWhite(string & word)
{
    int first = 0;
    int len = word.length();
    
    while (first < len && isspace(word[first]))
    { 
        first++;
    }
    // assert: first indexes either '\0' or non-punctuation
    
    // now find last non-nonpunctuation character

    int last = len - 1;  // last char in s
    
    while(last >= 0 && isspace(word[last]))
    {
        last--;
    }
    word = word.substr(first,last-first+1);
}

string itoa(int n)
// postcondition: return string equivalent of int n
{
    ostringstream output;
    output << n;   
    return output.str();
}

string tostring(int n)
// postcondition: return string equivalent of int n
{
    return itoa(n);
}
string tostring(double n)
// postcondition: return string equivalent of double n
{
    ostringstream output;
    output << n;   
    return output.str();
}

int atoi(const string & s)
// precondition: s is a sequence of digits
// postcondition: returns integer equivalent of s
// exception: if s is not valid integer, 0 is returned
{
    return atoi(s.c_str());
}

double atof(const string & s)
// precondition: s is a sequence of digits
// postcondition: returns double equivalent of s
// exception: if s is not valid double, 0 is returned
{
    return atof(s.c_str());
}

