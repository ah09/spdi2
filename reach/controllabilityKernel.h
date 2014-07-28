#ifndef CONTROLLABILITYKERNEL_H_INCLUDED
#define CONTROLLABILITYKERNEL_H_INCLUDED
#include <stdio.h>


/* succ returns an array of lines representing the reachable line segments of
   successor edges of a given edge list starting from a given starting interval */
struct line * succ(line [], line [], int, line, region [], int);

/* pred returns an array of lines representing the reachable line segments of
   predecessor edges of a given edge list starting backwards from a given starting interval */
struct line * pred(line [], line [], int, line, region [], int);

/* controllabilityKernel returns an array of lines representing all the line segments
   of a controllability kernel given an edge list starting from a starting interval.
   At the moment it calculates the successor and predecessor line segments itself
   rather than making use of other functions specifically made to do the job */
struct line * controllabilityKernel(line [], line [], int, line, region [], int);


#endif
