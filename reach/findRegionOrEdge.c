#include <math.h>
#include <stdbool.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "compare.h"
#include "minmax.h"
#include "immediateReachability.h"
#include "findRegionOrEdge.h"


line hasEdgeWithLineSegment(region R, line l){
    if (isCollinearIntersection(l, R.e.e1)){return R.e.e1;}
    if (isCollinearIntersection(l, R.e.e2)){return R.e.e2;}
    if (isCollinearIntersection(l, R.e.e3)){return R.e.e3;}
    if (isCollinearIntersection(l, R.e.e4)){return R.e.e4;}
    return lineNotFound;
}

line findEdgeWithLineSegment(region s[], int size, line l){
    int i;
    for (i = 0; i < size; ++i){
        line e = hasEdgeWithLineSegment(s[i], l);
        if (e.pt1.x != -1){
            return e;
        }
    }
    return lineNotFound;
}

bool hasEdge(region R, line e) {
    if (sameLineAs(R.e.e1, e)){return true;}
    else if (sameLineAs(R.e.e2, e)){return true;}
    else if (sameLineAs(R.e.e3, e)){return true;}
    else if (sameLineAs(R.e.e4, e)){return true;}
    else {return false;}
}

bool hasEntryEdge(region R, line e) {
    if (!hasEdge(R, e)){return false;}
    point edgeMiddle;
    edgeMiddle.x = (e.pt2.x + e.pt1.x) / 2;
    edgeMiddle.y = (e.pt1.y + e.pt2.y) / 2;
    point regionMiddle;
    double xmax = MAX(max(R.e.e1.pt1.x, R.e.e2.pt1.x, R.e.e3.pt1.x, R.e.e4.pt1.x), max(R.e.e1.pt2.x, R.e.e2.pt2.x, R.e.e3.pt2.x, R.e.e4.pt2.x));
    double xmin = MIN(min(R.e.e1.pt1.x, R.e.e2.pt1.x, R.e.e3.pt1.x, R.e.e4.pt1.x), min(R.e.e1.pt2.x, R.e.e2.pt2.x, R.e.e3.pt2.x, R.e.e4.pt2.x));
    regionMiddle.x = (xmax + xmin) / 2;
    double ymax = MAX(max(R.e.e1.pt1.y, R.e.e2.pt1.y, R.e.e3.pt1.y, R.e.e4.pt1.y), max(R.e.e1.pt2.y, R.e.e2.pt2.y, R.e.e3.pt2.y, R.e.e4.pt2.y));
    double ymin = MIN(min(R.e.e1.pt1.y, R.e.e2.pt1.y, R.e.e3.pt1.y, R.e.e4.pt1.y), min(R.e.e1.pt2.y, R.e.e2.pt2.y, R.e.e3.pt2.y, R.e.e4.pt2.y));
    regionMiddle.y = (ymax + ymin) / 2;
    vector edgeToMiddle;
    edgeToMiddle.x = regionMiddle.x - edgeMiddle.x;
    edgeToMiddle.y = regionMiddle.y - edgeMiddle.y;
    double aScalarProduct = edgeToMiddle.x*R.v.a.x + edgeToMiddle.y*R.v.a.y;
    double bScalarProduct = edgeToMiddle.x*R.v.b.x + edgeToMiddle.y*R.v.b.y;
    double edgeToMiddleMagnitude = sqrt(edgeToMiddle.x*edgeToMiddle.x + edgeToMiddle.y*edgeToMiddle.y);
    double aMagnitude = sqrt(R.v.a.x*R.v.a.x + R.v.a.y*R.v.a.y);
    double bMagnitude = sqrt(R.v.b.x*R.v.b.x + R.v.b.y*R.v.b.y);
    double aVectorAngle = aScalarProduct / (edgeToMiddleMagnitude*aMagnitude);
    double bVectorAngle = bScalarProduct / (edgeToMiddleMagnitude*bMagnitude);
    if (aVectorAngle > 0 || bVectorAngle > 0){return true;}
    return false;
}

bool existsRegionWithEntryEdge(region s[], line e, int size) {
    int i;
    for (i = 0; i < size; ++i){
        if (hasEntryEdge(s[i], e)){
            return true;
        }
    }
    return false;
}

region findRegionWithEntryEdge(region s[], line e, int size) {
    int i;
    for (i = 0; i < size; ++i){
        if (hasEntryEdge(s[i], e)){
            return s[i];
        }
    }
    line notFound1 = {{-1, 0}, {0, 0}};
    line notFound2 = {{0, 0}, {0, 0}};
    line notFound3 = {{0, 0}, {0, 0}};
    line notFound4 = {{0, 0}, {0, 0}};
    vector notFound5 = {0, 0};
    vector notFound6 = {0, 0};
    region notFound;
    notFound.e.e1 = notFound1;
    notFound.e.e2 = notFound2;
    notFound.e.e3 = notFound3;
    notFound.e.e4 = notFound4;
    notFound.v.a = notFound5;
    notFound.v.b = notFound6;
    return notFound;
};

int numberOfReachableEdges(line I, region s[], int size) {
    line e = findEdgeWithLineSegment(s, size, I);
    if (!existsRegionWithEntryEdge(s, e, size)){
        return 0;
    }
    region R = findRegionWithEntryEdge(s, e, size);
    if (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e1)
        && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e2)
        && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e3)
        && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e4)){
        return 4;
    }
    if ((isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e1) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e2) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e3))
        || (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e1) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e2) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e4))
        || (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e1) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e3) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e4))
        || (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e2) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e3) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e4))){
        return 3;
    }
    if ((isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e1) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e2))
        || (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e1) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e3))
        || (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e1) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e4))
        || (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e2) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e3))
        || (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e2) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e4))
        || (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e3) && isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e4))){
        return 2;
    }
    if (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e1) || isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e2)
        || isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e3) || isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e4)){
        return 1;
    }
    return -1;
}

line reachableEdge(line I, region R){
    if (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e1)){return R.e.e1;}
    if (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e2)){return R.e.e2;}
    if (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e3)){return R.e.e3;}
    if (isImmediatelyReachable(I, R.v.a, R.v.b, R.e.e4)){return R.e.e4;}
    return lineNotFound;
}

bool hasExitEdge(region R, line e) {
    if (!hasEdge(R, e)){return false;}
    point edgeMiddle;
    edgeMiddle.x = (e.pt2.x + e.pt1.x) / 2;
    edgeMiddle.y = (e.pt1.y + e.pt2.y) / 2;
    point regionMiddle;
    double xmax = MAX(max(R.e.e1.pt1.x, R.e.e2.pt1.x, R.e.e3.pt1.x, R.e.e4.pt1.x), max(R.e.e1.pt2.x, R.e.e2.pt2.x, R.e.e3.pt2.x, R.e.e4.pt2.x));
    double xmin = MIN(min(R.e.e1.pt1.x, R.e.e2.pt1.x, R.e.e3.pt1.x, R.e.e4.pt1.x), min(R.e.e1.pt2.x, R.e.e2.pt2.x, R.e.e3.pt2.x, R.e.e4.pt2.x));
    regionMiddle.x = (xmax + xmin) / 2;
    double ymax = MAX(max(R.e.e1.pt1.y, R.e.e2.pt1.y, R.e.e3.pt1.y, R.e.e4.pt1.y), max(R.e.e1.pt2.y, R.e.e2.pt2.y, R.e.e3.pt2.y, R.e.e4.pt2.y));
    double ymin = MIN(min(R.e.e1.pt1.y, R.e.e2.pt1.y, R.e.e3.pt1.y, R.e.e4.pt1.y), min(R.e.e1.pt2.y, R.e.e2.pt2.y, R.e.e3.pt2.y, R.e.e4.pt2.y));
    regionMiddle.y = (ymax + ymin) / 2;
    vector edgeToMiddle;
    edgeToMiddle.x = regionMiddle.x - edgeMiddle.x;
    edgeToMiddle.y = regionMiddle.y - edgeMiddle.y;
    double aScalarProduct = edgeToMiddle.x*R.v.a.x + edgeToMiddle.y*R.v.a.y;
    double bScalarProduct = edgeToMiddle.x*R.v.b.x + edgeToMiddle.y*R.v.b.y;
    double edgeToMiddleMagnitude = sqrt(edgeToMiddle.x*edgeToMiddle.x + edgeToMiddle.y*edgeToMiddle.y);
    double aMagnitude = sqrt(R.v.a.x*R.v.a.x + R.v.a.y*R.v.a.y);
    double bMagnitude = sqrt(R.v.b.x*R.v.b.x + R.v.b.y*R.v.b.y);
    double aVectorAngle = aScalarProduct / (edgeToMiddleMagnitude*aMagnitude);
    double bVectorAngle = bScalarProduct / (edgeToMiddleMagnitude*bMagnitude);
    if (aVectorAngle < 0 || bVectorAngle < 0){return true;}
    return false;
}

bool existsRegionWithExitEdge(region s[], line e, int size) {
    int i;
    for (i = 0; i < size; ++i){
        if (hasExitEdge(s[i], e)){
            return true;
        }
    }
    return false;
}

region findRegionWithExitEdge(region s[], line e, int size) {
    int i;
    for (i = 0; i < size; ++i){
        if (hasExitEdge(s[i], e)){
            return s[i];
        }
    }
    line notFound1 = {{-1, 0}, {0, 0}};
    line notFound2 = {{0, 0}, {0, 0}};
    line notFound3 = {{0, 0}, {0, 0}};
    line notFound4 = {{0, 0}, {0, 0}};
    vector notFound5 = {0, 0};
    vector notFound6 = {0, 0};
    region notFound;
    notFound.e.e1 = notFound1;
    notFound.e.e2 = notFound2;
    notFound.e.e3 = notFound3;
    notFound.e.e4 = notFound4;
    notFound.v.a = notFound5;
    notFound.v.b = notFound6;
    return notFound;
}

line findEdgeInRegionWithSameX(line e, region R, double x) {
    if (R.e.e1.pt1.x == x && R.e.e1.pt2.x == x){return R.e.e1;}
    else if (R.e.e2.pt1.x == x && R.e.e2.pt2.x == x){return R.e.e2;}
    else if (R.e.e3.pt1.x == x && R.e.e3.pt2.x == x){return R.e.e3;}
    else if (R.e.e4.pt1.x == x && R.e.e4.pt2.x == x){return R.e.e4;}
    else {return lineNotFound;}
}

line findEdgeInRegionWithSameY(line e, region R, double y) {
    if (R.e.e1.pt1.y == y && R.e.e1.pt2.y == y){return R.e.e1;}
    else if (R.e.e2.pt1.y == y && R.e.e2.pt2.y == y){return R.e.e2;}
    else if (R.e.e3.pt1.y == y && R.e.e3.pt2.y == y){return R.e.e3;}
    else if (R.e.e4.pt1.y == y && R.e.e4.pt2.y == y){return R.e.e4;}
    else {return lineNotFound;}
}
