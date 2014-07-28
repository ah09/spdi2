#ifndef IMMEDIATEREACHABILITY_H_INCLUDED
#define IMMEDIATEREACHABILITY_H_INCLUDED
#include <stdio.h>


/* isImmediatelyReachable determines whether any part of a line is reachable
   given just one starting interval and one pair of vectors. This is useful
   for finding the edges of a region that are reachable from an entry interval */
bool isImmediatelyReachable(line, vector, vector, line);

/* immediateReachability finds the line segment of reachability
   of a line from an interval and a pair of vectors */
line immediateReachability(line, vector, vector, line);

/* immediateReachabilityReverse works the same way as immediateReachability,
   except that the directions of the vectors are reversed. This is useful
   when finding a list of preceding intervals */
line immediateReachabilityReverse(line, vector, vector, line);


#endif
