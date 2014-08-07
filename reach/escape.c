#include <stdbool.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "compare.h"
#include "distance.h"
#include "findRegionOrEdge.h"
#include "immediateReachability.h"
#include "sort.h"
#include "escape.h"


int findLineIndexInArray(line array[], int start, int num_elements, line element){
    int i;
    for (i=start; i < start + num_elements; ++i){
        //printf("line index edge [%d] is (%f, %f) to (%f, %f)\n", i, array[i].pt1.x, array[i].pt1.y, array[i].pt2.x, array[i].pt2.y);
        if (sameLineAs(array[i], element)){
            return i;
        }
    }
    return -1;
}

int findLineSubsetInArray(line array[], int num_elements, line element){
    int i;
    for (i = 0; i < num_elements; ++i){
        if (isSomeCollinearIntersection(element, array[i])) {
            return i;
        }
    }
    return -1;
}

line limit(line e, line I, line edgeList[], int start, int numberOfEdges, region s[], int size){
    int numberOfPoints = 0;
    int i = 0;
    region R;
    line l;
    line x1;
    line x2;
    line x3;
    line e1 = findEdgeWithLineSegment(s, size, I);
    if (sameLineAs(e1, e)){
        x1 = I;
        ++numberOfPoints;
    }
    int initial = findLineIndexInArray(edgeList, start, numberOfEdges, e1);
    //i = 0;
    //printf("initial is %d\n", initial);
    //printf("edgeList[%d] is (%f, %f) to (%f, %f)\n", initial, edgeList[initial].pt1.x, edgeList[initial].pt1.y, edgeList[initial].pt2.x, edgeList[initial].pt2.y);
    l = immediateReachability(I, R.v.a, R.v.b, edgeList[initial + 1]);
    //printf("l is (%f, %f) to (%f, %f)\n", l.pt1.x, l.pt1.y, l.pt2.x, l.pt2.y);
    //printf("edgeList[%d] is (%f, %f) to (%f, %f)\n", initial+1, edgeList[initial+1].pt1.x, edgeList[initial+1].pt1.y, edgeList[initial+1].pt2.x, edgeList[initial+1].pt2.y);
    //printf("i is %d\n", i);
    while (numberOfPoints < 3){
        //break;
        R = findRegionWithEntryEdge(s, edgeList[initial + i], size);
        //l = immediateReachability(I, R.v.a, R.v.b, edgeList[((i+1)%numberOfEdges)+initial]);
        l = immediateReachability(I, R.v.a, R.v.b, edgeList[initial + ((i + 1) % numberOfEdges)]);
        //printf("l is (%f, %f) to (%f, %f)\n", l.pt1.x, l.pt1.y, l.pt2.x, l.pt2.y);
        e1 = findEdgeWithLineSegment(s, size, l);
        if (sameLineAs(e1, e)){
            if (numberOfPoints == 0){
                x1 = l;
                ++numberOfPoints;
            }
            else if (numberOfPoints == 1){
                x2 = l;
                ++numberOfPoints;
            }
            else if (numberOfPoints == 2){
                x3 = l;
                ++numberOfPoints;
            }
        }
        I = l;
        i = (i + 1) % numberOfEdges;
    }
    sort(&x1.pt1.x, &x1.pt1.y, &x1.pt2.x, &x1.pt2.y);
    sort(&x2.pt1.x, &x2.pt1.y, &x2.pt2.x, &x2.pt2.y);
    sort(&x3.pt1.x, &x3.pt1.y, &x3.pt2.x, &x3.pt2.y);
    //printf("x1 is (%f, %f) to (%f, %f)\n", x1.pt1.x, x1.pt1.y, x1.pt2.x, x1.pt2.y);
    //printf("x2 is (%f, %f) to (%f, %f)\n", x2.pt1.x, x2.pt1.y, x2.pt2.x, x2.pt2.y);
    //printf("x3 is (%f, %f) to (%f, %f)\n", x3.pt1.x, x3.pt1.y, x3.pt2.x, x3.pt2.y);
    double u1 = distance(x1.pt1, x2.pt1);
    double u2 = distance(x2.pt1, x3.pt1);
    double d1 = distance(x1.pt2, x2.pt2);
    double d2 = distance(x2.pt2, x3.pt2);
    //printf("u1 is %f\n", u1);
    //printf("u2 is %f\n", u2);
    //printf("d1 is %f\n", d1);
    //printf("d2 is %f\n", d2);
    double ur;
    if (u2 == 0){ur = 0;}
    else {ur = u2 / u1;}
    //printf("ur is %f / %f = %f\n", u2, u1, ur);
    double dr;
    if (d2 == 0){dr = 0;}
    else {dr = d2 / d1;}
    //printf("dr is %f / %f = %f\n", d2, d1, dr);
    line x;
    //printf("1line x is (%f, %f) to (%f, %f)\n", x.pt1.x, x.pt1.y, x.pt2.x, x.pt2.y);
    //printf("e is (%f, %f) to (%f, %f)\n", e.pt1.x, e.pt1.y, e.pt2.x, e.pt2.y);
    if (ur < 1){
        if (e.pt1.x == e.pt2.x){
            x.pt1.x = x1.pt1.x;
            x.pt1.y = x1.pt1.y + (u1 / (1 - ur));
        }
        else{
            x.pt1.x = x1.pt1.x + (u1 / (1 - ur));
            x.pt1.y = x1.pt1.y;
        }
    }
    else {
        if (e.pt1.x == e.pt2.x){
            x.pt1.x = e.pt1.x;
            x.pt1.y = e.pt1.y - 0.1;
        }
        else{
            x.pt1.x = e.pt1.x - 0.1;
            x.pt1.y = e.pt1.y;
        }
        //x.pt1.x = e.pt1.x;
        //x.pt1.y = e.pt1.y;
    }
    //printf("2line x is (%f, %f) to (%f, %f)\n", x.pt1.x, x.pt1.y, x.pt2.x, x.pt2.y);
    if (dr < 1){
        if (e.pt1.x == e.pt2.x){
            x.pt2.x = x1.pt2.x;
            x.pt2.y = x1.pt2.y + (d1 / (1 - dr));
        }
        else{
            x.pt2.x = x1.pt2.x + (d1 / (1 - dr));
            x.pt2.y = x1.pt2.y;
        }
    }
    else {
        if (e.pt1.x == e.pt2.x){
            x.pt2.x = e.pt2.x;
            x.pt2.y = e.pt2.y + 0.1;
        }
        else{
            x.pt2.x = e.pt2.x + 0.1;
            x.pt2.y = e.pt2.y;
        }
        //x.pt2.x = e.pt2.x;
        //x.pt2.y = e.pt2.y;
    }
    //printf("3line x is (%f, %f) to (%f, %f)\n", x.pt1.x, x.pt1.y, x.pt2.x, x.pt2.y);
    return x;
}

bool isLimitWithinEdge(line e, line I, line edgeList[], int start, int numberOfEdges, region s[], int size) {
    line l = limit(e, I, edgeList, start, numberOfEdges, s, size);
    //printf("limit is (%f, %f) to (%f, %f)\n", l.pt1.x, l.pt1.y, l.pt2.x, l.pt2.y);
    //printf("of the edge (%f, %f) to (%f, %f)\n", e.pt1.x, e.pt1.y, e.pt2.x, e.pt2.y);
    //line li = collinearIntersection(l, e);
    /*if (li.pt1.x == l.pt1.x && li.pt1.y == l.pt1.y && li.pt2.x == l.pt2.x && li.pt2.y == l.pt2.y
        && !(l.pt1.x == e.pt1.x && l.pt1.y == e.pt1.y) && !(l.pt2.x == e.pt2.x && l.pt2.y == e.pt2.y)) {return true;}
    else {return false;}*/
    if (lineSetMinusLine(l, e).pt1.x != -1){
        return false;
    }
    else{
        return true;
    }
}
