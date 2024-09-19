#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>
#include "Fonts.h"
#include "Colours.h"

#define NUM_LEDS 400      //  Number of LEDs on a curtain
#define ROWS 20           //  The number of rows used
#define COLUMNS 20       //  The number of columns enabled

#define LETTERWIDTH 8     //  The width of a letter
#define LETTERHEIGHT 10
#define SPACEWHITESPACE 8 //  Number of whitespaces per space
#define WHITESPACE 4      //  Number of whitespaces between letters

#define DATA_PIN 1        //  Pin the LED data is being driven on

#define FORWARD 0

#define ALPHA 0.3     // IIR Filter coefficient

#define INTERVAL 60

//#define SERPENTINE
  #ifdef SERPINTINE
    #define DISTBETWEENLIGHTS 0.05
    #define STARTCOLUMN 2
    #define ENDCOLUMN 37
    #define SCALING 1
    #define ROWSPERCOLUMN 10   //  The number of rows that makes up a column
  #endif

  #ifndef SERPINTINE
    #define DISTBETWEENLIGHTS 0.1 // Distance between lights on the curtain (meters) 
    #define STARTCOLUMN 0
    #define ENDCOLUMN 19
    #define SCALING 1
    #define ROWSPERCOLUMN 20   //  The number of rows that makes up a column
  #endif

#define SERIALDEBUG

//  Each of the 26 letters represented in 4 bytes - see Letter converter
/*const long LETTERS[27] = {  
31626430 ,  //    A
11196095 ,  //    B
18400831 ,  //    C
15255103 ,  //    D
18536127 ,  //    E
1217727 ,   //    F
31114815 ,  //    G
32641183 ,  //    H
18415153 ,  //    I
1113657 ,   //    J
567455 ,    //    K
17318431 ,  //    L
32575583 ,  //    M
32772191 ,  //    N
33080895 ,  //    O
2266303 ,   //    P
24430143 ,  //    Q
19305663 ,  //    R
31119031 ,  //    S
1113121 ,   //    T
16269839 ,  //    U
3555715 ,   //    V
32772383 ,  //    W
18157905 ,  //    X
1142849 ,   //    Y
18470705 ,  //    Z
0,          //    SPACE
};*/

#endif