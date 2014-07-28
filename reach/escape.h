#ifndef ESCAPE_H_INCLUDED
#define ESCAPE_H_INCLUDED
#include <stdio.h>


/* findLineIndexInArray returns the index number of a given line
   in an array of lines and returns -1 if it is not found */
int findLineIndexInArray(line [], int, int, line);

/* limit returns a particular line segment of an invariance kernel
   with the line segment being the limits of a particular edge where
   if a trajectory were to be within that line segment then it will
   be within the invariance kernel and therefore will never leave that
   set. I find this hard to test */
line limit(line, line, line [], int, int, region [], int);

/* isLimitWithinRange checks if the limit of a kernel for a particular
   edge lies within that edge, it is equivalent to finding if the kernel
   is inescapable from that edge */
bool isLimitWithinEdge(line, line, line [], int, int, region [], int);


#endif

