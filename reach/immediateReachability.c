#include <stdbool.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "det.h"
#include "intervalRange.h"
#include "immediateReachability.h"
#include "minmax.h"


bool isImmediatelyReachable(line I, vector a, vector b, line e) {
    double da = det(a, e);
    double db = det(b, e);
    if (da == 0 && db == 0){return false;}
    line ir = intervalRange(I, a, b, e);
    if ((a.x > 0 && b.x > 0 && MAX(ir.pt1.x, ir.pt2.x) <= MIN(I.pt1.x, I.pt2.x))
        || (a.x < 0 && b.x < 0 && MIN(ir.pt1.x, ir.pt2.x) >= MAX(I.pt1.x, I.pt2.x))
        || (a.y > 0 && b.y > 0 && MAX(ir.pt1.y, ir.pt2.y) <= MIN(I.pt1.y, I.pt2.y))
        || (a.y < 0 && b.y < 0 && MIN(ir.pt1.y, ir.pt2.y) >= MAX(I.pt1.y, I.pt2.y))) {
        return false;
    }
    if (isCollinear(I, e) || ir.pt1.x > e.pt2.x || ir.pt2.x < e.pt1.x
        || (ir.pt1.x == ir.pt2.x && (ir.pt1.y > e.pt2.y || ir.pt2.y < e.pt1.y))) {
        return false;
    }
    else{
        line r = collinearIntersection(ir, e);
        if (r.pt1.x == r.pt2.x && r.pt1.y == r.pt2.y){
            return false;
        }
        else{
            return true;
        }
    }
}

line immediateReachability(line I, vector a, vector b, line e) {
    if (isImmediatelyReachable(I, a, b, e)) {
        line ir = intervalRange(I, a, b, e);
        line r = collinearIntersection(ir, e);
        return r;
    }
    else {
        return lineNotFound;
    }
}

line immediateReachabilityReverse(line I, vector a, vector b, line e) {
    a.x = -a.x;
    a.y = -a.y;
    b.x = -b.x;
    b.y = -b.y;
    if (isImmediatelyReachable(I, a, b, e)) {
        line ir = intervalRange(I, a, b, e);
        line r = collinearIntersection(ir, e);
        return r;
    }
    else {
        return lineNotFound;
    }
}
