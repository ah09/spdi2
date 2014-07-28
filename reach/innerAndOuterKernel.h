#ifndef INNERANDOUTERKERNEL_H_INCLUDED
#define INNERANDOUTERKERNEL_H_INCLUDED
#include <stdio.h>


/* innerKernel is meant to return an array of points representing the points
   of the inner part of a kernel which can be joined together with straight
   lines to find the inner kernel. At the moment, both the inner and outer
   points of the kernel are worked out in this function and having another
   function for finding the outer kernel would be recomputing the same
   results, as both the inner and outer points of the kernel need to be
   compared in order for each of them to be identified */
struct point * innerKernel(line [], int);

/* outerKernel is the same as innerKernel except it returns the outer kernel,
   frankly I think that this is recomputing the same non-trivial results */
struct point * outerKernel(line [], int);

/* isInnerKernel determines whether a calculated inner kernel actually is
   an inner part of a kernel as a given kernel is not guaranteed to have an
   inner kernel although all kernels are guaranteed to have outer kernels */
bool isInnerKernel(point [], int);


#endif
