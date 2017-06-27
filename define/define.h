#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include "../include/Point.h"
#include <vector>

using namespace std;

typedef vector<unsigned> containerIDs;
typedef vector<Point> containerPoints;
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

#endif // DEFINE_H_INCLUDED


