#ifndef REACH_H_INCLUDED
#define REACH_H_INCLUDED
#include <stdio.h>


line inescapable[1000];
//line * inescapable;
int inescapableInt;
/* earlier reach attemt involving an array and two pointers was too simplistic,
   a truly recursive function that generates branches is needed, is unfinished */
line reach(region [], int, line [], line [], int, line);


#endif
