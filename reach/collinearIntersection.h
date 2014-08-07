#ifndef COLLINEARINTERSECTION_H_INCLUDED
#define COLLINEARINTERSECTION_H_INCLUDED
#include <stdio.h>


/* collinearIntersection finds the intersection of the line found
   from intervalRange and a given line, it is the final step
   of finding the line of reachability of a given edge */
line collinearIntersection(line, line);

/* isCollinear determines whether two line segments are collinear,
   meaning that their Ax + By = C expressions are identical, or that
   they are both discrete segments of the same line of infinite length*/
bool isCollinear(line, line);

/* isCollinearIntersection determines whether two line segments have a
   collinear intersection, meaning that they are both collinear and that there
   is an computable line where the two line segments intersect with each other */
bool isCollinearIntersection(line, line);

/* isSomeCollinearIntersection is for if there is any intersection at all,
   not just if the first line is entirely contained within the second one*/
bool isSomeCollinearIntersection(line, line);

/* lineSetMinusLine minuses the second argument from the first one */
line lineSetMinusLine(line, line);

#endif
