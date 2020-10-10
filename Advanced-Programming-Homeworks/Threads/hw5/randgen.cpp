#include <time.h>                // for time()
#include <stdlib.h>              // for rand/srand
#include "randgen.h"
#include <cmath>

#include <iostream>
using namespace std;

int RandGen::ourInitialized = 0;

void RandGen::SetSeed(int seed)
// postcondition: system srand() used to initialize seed
//                once per program (this is a static function)    
{
    if (0 == ourInitialized)
    {   ourInitialized = 1;   // only call srand once
	srand(seed);          // randomize
    }
}


RandGen::RandGen()
// postcondition: system srand() used to initialize seed
//                once per program     
{
    if (0 == ourInitialized)
    {   ourInitialized = 1;          // only call srand once


	    time_t now;
        time (&now); // localtime bir zamandan itibaren geçen saniye formatında
                     // now değişkenine kaydedilir.
        srand(int((sin(double(now))*1000000)));//Gökhan
		// seed'imiz her saniye bir artmasın diye
                                        // daha random artsın diye sinusunu alıyorum 
 //       srand(unsigned(time(0)));    // randomize
    }
}

int RandGen::RandInt(int max)
// precondition: max > 0
// postcondition: returns int in [0..max)     
{  
    return int(RandReal() * max);
}

int RandGen::RandInt(int low, int max)
// precondition: low <= max     
// postcondition: returns int in [low..max]     
{ 
    return low + RandInt(max-low+1);
}

double RandGen::RandReal()
// postcondition: returns double in [0..1)     
{     
    return rand() / (double(RAND_MAX) + 1); 
}

double RandGen::RandReal(double low, double high)
{
    double width = fabs(high-low);
    double thelow = low < high ? low : high;
    return RandReal()*width + thelow;
}