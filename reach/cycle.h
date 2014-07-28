#ifndef CYCLE_H_INCLUDED
#define CYCLE_H_INCLUDED
#include <stdio.h>


/* patternDetection detects whether there is a pattern in a given edge
   cycle where any particular sequence of edges is repeated three times */
bool patternDetection(line [], int);

/* cycleNumber finds a cycle in an edge list where a cycle is any particular sequence
   of edges that is repeated three times and then returns the size of the cycle */
int cycleNumber(line [], int);


#endif
