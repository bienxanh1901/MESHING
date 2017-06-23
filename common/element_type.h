// The libMesh Finite Element Library.
// Copyright (C) 2002-2017 Benjamin S. Kirk, John W. Peterson, Roy H. Stogner

#ifndef ELEMENT_TYPE_H_INCLUDED
#define ELEMENT_TYPE_H_INCLUDED

enum elemType {EDGE2=0,         // 0
               EDGE3,           // 1
               EDGE4,           // 2

               TRI3,            // 3
               TRI6,            // 4

               QUAD4,           // 5
               QUAD8,           // 6
               QUAD9,           // 7

               TET4,            // 8
               TET10,           // 9

               HEX8,            // 10
               HEX20,           // 11
               HEX27,           // 12

               PRISM6,          // 13
               PRISM15,         // 14
               PRISM18,         // 15

               PYRAMID5,        // 16
               PYRAMID13,       // 17
               PYRAMID14,       // 18

               INFEDGE2,        // 19

               INFQUAD4,        // 20
               INFQUAD6,        // 21

               INFHEX8,         // 22
               INFHEX16,        // 23
               INFHEX18,        // 24

               INFPRISM6,       // 25
               INFPRISM12,      // 26

               NODEELEM,        // 27

               REMOTEELEM,      // 28

               TRI3SUBDIVISION, // 29
               TRISHELL3,       // 30
               QUADSHELL4,      // 31

               INVALID_ELEM};   // 32 - should always be last


#endif // ELEMENT_TYPE_H_INCLUDED
