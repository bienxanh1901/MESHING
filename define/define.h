#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <vector>
#include "../include/Point.h"
#include "../include/arrayTemplate.h"

using namespace std;

typedef vector<unsigned> ContainerIDs;
typedef vector<Point> ContainerPoints;
typedef vector<Point*> ContainerPrtPoints;
typedef Array<double> ArrDouble;
typedef Array<unsigned> ArrUnsgn;
typedef vector<ArrDouble> ContainerArrD;
typedef vector<ArrUnsgn> ContainerArrU;

/*=============================================================================
Macros
=============================================================================*/
// round
#define ROUNDED( a, b )		( ( a >= 0 ) ? _ROUNDED( a, b ) : ( (-1)*( _ROUNDED( -a, b ) ) ) )
#define _ROUNDED( a, b )	( fmod( a * pow( 1,b ), 1. ) < 0.5 ) ? ( floor( a * pow( 1,b ) ) / pow( 1,b ) ) \
                                                           : ( ceil(  a * pow( 1,b ) ) / pow( 1,b ) )
// KEYBOARD
#define ENTER   "\n"
#define TAB     "\t"

// math define
#define PI 3.14159265358979
#define EPS 0.00000001
#endif // DEFINE_H_INCLUDED

//loop define (reference by openFoam)

#define forAll(list, i) for(unsigned i = 0; i < (list).size(); i++)
#define forAllIter(Container,container,iter)                                    \
     for                                                                        \
     (                                                                          \
         Container::iterator iter = (container).begin();                        \
         iter != (container).end();                                             \
         ++iter)                                                                 \

