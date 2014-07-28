#include <stdbool.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "distance.h"
#include "findRegionOrEdge.h"
#include "immediateReachability.h"
#include "sort.h"
#include "escape.h"


int findLineIndexInArray(line array[], int start, int num_elements, line element){
    int i;
    for (i=start; i < num_elements; ++i){
        if (array[i].pt1.x == element.pt1.x && array[i].pt1.y == element.pt1.y && array[i].pt2.x == element.pt2.x && array[i].pt2.y == element.pt2.y){
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
    if (e1.pt1.x == e.pt1.x && e1.pt1.y == e.pt1.y && e1.pt2.x == e.pt2.x && e1.pt2.y == e.pt2.y){
        x1 = I;
        ++numberOfPoints;
    }
    i = findLineIndexInArray(edgeList, start, numberOfEdges, e1);
    while (numberOfPoints < 3){
        R = findRegionWithEntryEdge(s, edgeList[i], size);
        l = immediateReachability(I, R.v.a, R.v.b, edgeList[(i+1)%numberOfEdges]);
        e1 = findEdgeWithLineSegment(s, size, l);
        if (e1.pt1.x == e.pt1.x && e1.pt1.y == e.pt1.y && e1.pt2.x == e.pt2.x && e1.pt2.y == e.pt2.y){
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
    double u1 = distance(x1.pt1, x2.pt1);
    double u2 = distance(x2.pt1, x3.pt1);
    double d1 = distance(x1.pt2, x2.pt2);
    double d2 = distance(x2.pt2, x3.pt2);
    double ur;
    if (u2 == 0){ur = 0;}
    else {ur = u2 / u1;}
    double dr;
    if (d2 == 0){dr = 0;}
    else {dr = d2 / d1;}
    line x;
    if (ur < 1){
        x.pt1.x = x1.pt1.x + (u1 / (1 - ur));
        x.pt1.y = x1.pt1.y + (u1 / (1 - ur));
    }
    else {
        x.pt1.x = e.pt1.x;
        x.pt1.y = e.pt1.y;
    }
    if (dr < 1){
        x.pt2.x = x1.pt2.x + (d1 / (1 - dr));
        x.pt2.y = x1.pt2.y + (d1 / (1 - dr));
    }
    else {
        x.pt2.x = e.pt2.x;
        x.pt2.y = e.pt2.y;
    }
    return x;
}

bool isLimitWithinEdge(line e, line I, line edgeList[], int start, int numberOfEdges, region s[], int size) {
    line l = limit(e, I, edgeList, start, numberOfEdges, s, size);
    line li = collinearIntersection(l, e);
    if (li.pt1.x == l.pt1.x && li.pt1.y == l.pt1.y && li.pt2.x == l.pt2.x && li.pt2.y == l.pt2.y
        && !(l.pt1.x == e.pt1.x && l.pt1.y == e.pt1.y) && !(l.pt2.x == e.pt2.x && l.pt2.y == e.pt2.y)) {return true;}
    else {return false;}
}
