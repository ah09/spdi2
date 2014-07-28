#include <stdbool.h>
#include <stdlib.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "compare.h"
#include "distance.h"
#include "lineIntersection.h"
#include "minmax.h"
#include "innerAndOuterKernel.h"


struct point * innerKernel(line kernel[], int numberOfEdges){
    int i = 0;
    line l1;
    line l2; // for each region, l1 and l2 go across the region linking the edges of the edge list
    point * array1 = malloc(sizeof(point) * numberOfEdges);
    point * array2 = malloc(sizeof(point) * numberOfEdges);
    point temp;
    for (i = 0; i < numberOfEdges; ++i){
        if (i == 0){l1.pt1 = kernel[i].pt1;}
        else {l1.pt1 = l1.pt2;}
        l1.pt2 = kernel[(i+1)%numberOfEdges].pt1;
        if (i == 0){l2.pt1 = kernel[i].pt2;}
        else {l2.pt1 = l2.pt2;}
        l2.pt2 = kernel[(i+1)%numberOfEdges].pt2;
        if (samePointAs(l1.pt1, l1.pt2) || samePointAs(l2.pt1, l2.pt2)) { // tangent on one side
            array1[i] = l1.pt1;
            array1[i+1] = l1.pt2;
            array2[i] = l2.pt1;
            array2[i+1] = l2.pt2;
        }
        if (samePointAs(l1.pt1, l2.pt2) || samePointAs(l2.pt1, l1.pt2)) { // tangent on the other side
            array1[i] = l1.pt1;
            array1[i+1] = l2.pt2;
            array2[i] = l2.pt1;
            array2[i+1] = l1.pt2;
        }
        if ((l1.pt2.y - l1.pt1.y) / (l1.pt2.x - l1.pt1.x) == (l2.pt2.y - l2.pt1.y) / (l2.pt2.x - l2.pt1.x)){ // lines are parallel
            array1[i] = l1.pt1;
            array1[i+1] = l1.pt2;
            array2[i] = l2.pt1;
            array2[i+1] = l2.pt2;
        }
        else { // lines are not parallel and cross somewhere, either within the region or outside
            point ip = lineIntersection(l1, l2);
            if (ip.x > min(l1.pt1.x, l1.pt2.x, l2.pt1.x, l2.pt2.x)
             && ip.x < max(l1.pt1.x, l1.pt2.x, l2.pt1.x, l2.pt2.x)
             && ip.y > min(l1.pt1.y, l1.pt2.y, l2.pt1.y, l2.pt2.y)
             && ip.y < max(l1.pt1.y, l1.pt2.y, l2.pt1.y, l2.pt2.y)){ // lines cross within the region
                temp = l1.pt2;
                l1.pt2 = l2.pt2;
                l2.pt2 = temp; // now they don't cross within the region
                array1[i] = l1.pt1;
                array1[i+1] = l1.pt2;
                array2[i] = l2.pt1;
                array2[i+1] = l2.pt2;
            }
        }
    }
    double length1 = 0;
    double length2 = 0;
    for (i = 0; i < numberOfEdges - 1; ++i){
        length1 = length1 + distance(array1[i], array1[i+1]);
        length2 = length2 + distance(array2[i], array2[i+1]);
    }
    if (length1 < length2) {return array1;}
    else {return array2;}
}

struct point * outerKernel(line kernel[], int numberOfEdges){
    int i = 0;
    line l1;
    line l2; // for each region, l1 and l2 go across the region linking the edges of the edge list
    point * array1 = malloc(sizeof(point) * numberOfEdges);
    point * array2 = malloc(sizeof(point) * numberOfEdges);
    point temp;
    for (i = 0; i < numberOfEdges; ++i){
        if (i == 0){l1.pt1 = kernel[i].pt1;}
        else {l1.pt1 = l1.pt2;}
        l1.pt2 = kernel[(i+1)%numberOfEdges].pt1;
        if (i == 0){l2.pt1 = kernel[i].pt2;}
        else {l2.pt1 = l2.pt2;}
        l2.pt2 = kernel[(i+1)%numberOfEdges].pt2;
        if (samePointAs(l1.pt1, l1.pt2) || samePointAs(l2.pt1, l2.pt2)){ // tangent on one side
            array1[i] = l1.pt1;
            array1[i+1] = l1.pt2;
            array2[i] = l2.pt1;
            array2[i+1] = l2.pt2;
        }
        if (samePointAs(l1.pt1, l2.pt2) || samePointAs(l2.pt1, l1.pt2)){ // tangent on the other side
            array1[i] = l1.pt1;
            array1[i+1] = l2.pt2;
            array2[i] = l2.pt1;
            array2[i+1] = l1.pt2;
        }
        if ((l1.pt2.y - l1.pt1.y) / (l1.pt2.x - l1.pt1.x) == (l2.pt2.y - l2.pt1.y) / (l2.pt2.x - l2.pt1.x)){ // lines are parallel
            array1[i] = l1.pt1;
            array1[i+1] = l1.pt2;
            array2[i] = l2.pt1;
            array2[i+1] = l2.pt2;
        }
        else { // lines are not parallel and cross somewhere, either within the region or outside
            point ip = lineIntersection(l1, l2);
            if (ip.x > min(l1.pt1.x, l1.pt2.x, l2.pt1.x, l2.pt2.x)
             && ip.x < max(l1.pt1.x, l1.pt2.x, l2.pt1.x, l2.pt2.x)
             && ip.y > min(l1.pt1.y, l1.pt2.y, l2.pt1.y, l2.pt2.y)
             && ip.y < max(l1.pt1.y, l1.pt2.y, l2.pt1.y, l2.pt2.y)){ // lines cross within the region
                temp = l1.pt2;
                l1.pt2 = l2.pt2;
                l2.pt2 = temp; // now they don't cross within the region
                array1[i] = l1.pt1;
                array1[i+1] = l1.pt2;
                array2[i] = l2.pt1;
                array2[i+1] = l2.pt2;
            }
        }
    }
    double length1 = 0;
    double length2 = 0;
    for (i = 0; i < numberOfEdges - 1; ++i){
        length1 = length1 + distance(array1[i], array1[i+1]);
        length2 = length2 + distance(array2[i], array2[i+1]);
    }
    if (length1 > length2) {return array1;}
    else {return array2;}
}

bool isInnerKernel(point innerKernel[], int numberOfEdges){
    int i = 0;
    double xmin = 0;
    double xmax = 0;
    double ymin;
    double ymax;
    double length = 0;
    for (i = 0; i < numberOfEdges - 1; ++i){
        length = length + distance(innerKernel[i], innerKernel[i+1]);
        xmin = MIN(innerKernel[i].x, innerKernel[i+1].x);
        xmax = MAX(innerKernel[i].x, innerKernel[i+1].x);
        ymin = MIN(innerKernel[i].y, innerKernel[i+1].y);
        ymax = MAX(innerKernel[i].y, innerKernel[i+1].y);
    }
    if (xmax - xmin > 0 && ymax - ymin > 0){return true;}
    else {return false;}
}
