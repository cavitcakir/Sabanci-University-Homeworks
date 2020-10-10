#ifndef _STRUTILS_H
#define _STRUTILS_H

#include <iostream>
#include <string>
using namespace std;

void ToLower(string & s);
// postcondition: all alphabetic characters in s changed to lowercase
//                (only uppercase letters changed)

void ToUpper(string & s);
// postcondition: all alphabetic characters in s changed to uppercase
//                (only uppercase letters changed)

void StripPunc(string & s);
// postcondition: s has no leading/trailing punctuation

void StripWhite(string & s);
// postcondition: s has no leading/trailing white space

string LowerString(const string & s);
// postcondition: return lowercase equivalent of s

string UpperString(const string & s);
// postcondition: return uppercase equivalent of s


int atoi(const string & s);         // returns int equivalent
double atof(const string & s);      // returns double equivalent
string itoa(int n);                 // returns string equivalent
string tostring(int n);             // like itoa, convert int to string
string tostring(double d);          // convert double to string
    
#endif 