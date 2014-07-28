#include <stdbool.h>
#include "basicStructures.h"
#include "compare.h"


bool samePointAs(point a, point b) {
    if (a.x == b.x && a.y == b.y){
        return true;
    }
    return false;
}

bool sameLineAs(line a, line b) {
    if (a.pt1.x == b.pt1.x && a.pt1.y == b.pt1.y && a.pt2.x == b.pt2.x && a.pt2.y == b.pt2.y) {
        return true;
    }
    return false;
}

bool sameRegionAs(region a, region b) {
    if (a.e.e1.pt1.x == b.e.e1.pt1.x && a.e.e1.pt1.y == b.e.e1.pt1.y
        && a.e.e1.pt2.x == b.e.e1.pt2.x && a.e.e1.pt2.y == b.e.e1.pt2.y
        && a.e.e2.pt1.x == b.e.e2.pt1.x && a.e.e2.pt1.y == b.e.e2.pt1.y
        && a.e.e2.pt2.x == b.e.e2.pt2.x && a.e.e2.pt2.y == b.e.e2.pt2.y
        && a.e.e3.pt1.x == b.e.e3.pt1.x && a.e.e3.pt1.y == b.e.e3.pt1.y
        && a.e.e3.pt2.x == b.e.e3.pt2.x && a.e.e3.pt2.y == b.e.e3.pt2.y
        && a.e.e4.pt1.x == b.e.e4.pt1.x && a.e.e4.pt1.y == b.e.e4.pt1.y
        && a.e.e4.pt2.x == b.e.e4.pt2.x && a.e.e4.pt2.y == b.e.e4.pt2.y) {
        return true;
    }
    return false;
}
