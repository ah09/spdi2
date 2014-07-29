#include <stdbool.h>
#include "basicStructures.h"
#include "compare.h"
#include "collinearIntersection.h"
#include "cycle.h"
#include "escape.h"
#include "findRegionOrEdge.h"
#include "immediateReachability.h"
#include "reach.h"

line reach(region s[], int size, line edgeSequence[], line intervalSequence[], int i, line e){
    //printf("i is %d\n", i);
    edgeSequence[i] = findEdgeWithLineSegment(s, size, intervalSequence[i]);
    //printf("intervalSequence[%d] is (%f, %f) to (%f, %f)\n", i, intervalSequence[i].pt1.x, intervalSequence[i].pt1.y, intervalSequence[i].pt2.x, intervalSequence[i].pt2.y);
    //int count = 0;
    //for (count = 0; count <= i; ++count){
    //    printf("number of edges is %d, edge[%d] is (%f, %f) to (%f, %f)\n", i+1, count, edgeSequence[count].pt1.x, edgeSequence[count].pt1.y, edgeSequence[count].pt2.x, edgeSequence[count].pt2.y);
    //    printf("number of intervals is %d, interval[%d] is (%f, %f) to (%f, %f)\n", i+1, count, intervalSequence[count].pt1.x, intervalSequence[count].pt1.y, intervalSequence[count].pt2.x, intervalSequence[count].pt2.y);
    //}
    /*if(i > 0 && sameLineAs(edgeSequence[i], e)) {
       printf("found it\n");
       return true;
    }*/
    if (patternDetection(edgeSequence, i+1)){
        int sizeOfCycle = cycleNumber(edgeSequence, i+1);
        //printf("cycle is %d\n", sizeOfCycle);
        //printf("edges are:\n");
        //for (count = 3*sizeOfCycle-1; count >= 0; --count){
        //    printf("(%f, %f) to (%f, %f)\n", edgeSequence[i-count].pt1.x, edgeSequence[i-count].pt1.y, edgeSequence[i-count].pt2.x, edgeSequence[i-count].pt2.y);
        //}
        //printf("intervals are:\n");
        //for (count = 3*sizeOfCycle-1; count >= 0; --count){
        //    printf("(%f, %f) to (%f, %f)\n", intervalSequence[i-count].pt1.x, intervalSequence[i-count].pt1.y, intervalSequence[i-count].pt2.x, intervalSequence[i-count].pt2.y);
        //}
        int start = i-3*sizeOfCycle+1;
        int finish = start + sizeOfCycle - 1;
        //printf("start is %d\n", start);
        //printf("finish is %d\n", finish);
        for (i = start; i <= finish; ++i){
            region R = findRegionWithExitEdge(s, edgeSequence[i], size);
            //printf("edgeSequence[%d] is (%f, %f) to (%f, %f)\n", i, edgeSequence[i].pt1.x, edgeSequence[i].pt1.y, edgeSequence[i].pt2.x, edgeSequence[i].pt2.y);
            //printf("intervalSequence[%d] is (%f, %f) to (%f, %f)\n", i, intervalSequence[i].pt1.x, intervalSequence[i].pt1.y, intervalSequence[i].pt2.x, intervalSequence[i].pt2.y);
            if (!isLimitWithinEdge(edgeSequence[i], intervalSequence[i], edgeSequence, start, sizeOfCycle, s, size)) {
                line sameY1 = findEdgeInRegionWithSameY(edgeSequence[i], R, edgeSequence[i].pt1.y);
                line sameY2 = findEdgeInRegionWithSameY(edgeSequence[i], R, edgeSequence[i].pt2.y);
                line sameX1 = findEdgeInRegionWithSameX(edgeSequence[i], R, edgeSequence[i].pt1.x);
                line sameX2 = findEdgeInRegionWithSameX(edgeSequence[i], R, edgeSequence[i].pt2.x);
                if (edgeSequence[i].pt1.x == edgeSequence[i].pt2.x
                    && existsRegionWithEntryEdge(s, sameY1, size)
                    && existsRegionWithEntryEdge(s, sameY2, size)
                    && !sameLineAs(sameY1, e) && !sameLineAs(sameY2, e)) {
                    break; // escape
                }
                else if (edgeSequence[i].pt1.y == edgeSequence[i].pt2.y
                    && existsRegionWithEntryEdge(s, sameX1, size)
                    && existsRegionWithEntryEdge(s, sameX2, size)
                    && !sameLineAs(sameX1, e) && !sameLineAs(sameX2, e)) {
                    break; // escape
                }
            }
        }
        return lineNotFound; // stuck in loop
    }
    if (existsRegionWithEntryEdge(s, edgeSequence[i], size)){
        region R = findRegionWithEntryEdge(s, edgeSequence[i], size);
        //printf("intervalSequence[%d] is (%f, %f) to (%f, %f)\n", i, intervalSequence[i].pt1.x, intervalSequence[i].pt1.y, intervalSequence[i].pt2.x, intervalSequence[i].pt2.y);
        //printf("e is (%f, %f) to (%f, %f)\n", e.pt1.x, e.pt1.y, e.pt2.x, e.pt2.y);
        if (hasEdge(R, e) && isImmediatelyReachable(intervalSequence[i], R.v.a, R.v.b, e)){/*printf("found it\n");*///return true;}
            line l = immediateReachability(intervalSequence[i], R.v.a, R.v.b, e);
            return l;
        }
        if (isImmediatelyReachable(intervalSequence[i], R.v.a, R.v.b, R.e.e1)){
            intervalSequence[i+1] = immediateReachability(intervalSequence[i], R.v.a, R.v.b, R.e.e1);
            //for (count = 0; count <= i; ++count){
            //    printf("intervalSequence[%d] is (%f, %f) to (%f, %f)\n", count, intervalSequence[count].pt1.x, intervalSequence[count].pt1.y, intervalSequence[count].pt2.x, intervalSequence[count].pt2.y);
            //}
            line l = reach(s, size, edgeSequence, intervalSequence, i+1, e);
            //if(reach(s, size, edgeSequence, intervalSequence, i+1, e)){return true;}
            if (l.pt1.x != -1){return l;}
        }
        if (isImmediatelyReachable(intervalSequence[i], R.v.a, R.v.b, R.e.e2)){
            intervalSequence[i+1] = immediateReachability(intervalSequence[i], R.v.a, R.v.b, R.e.e2);
            //for (count = 0; count <= i; ++count){
            //    printf("intervalSequence[%d] is (%f, %f) to (%f, %f)\n", count, intervalSequence[count].pt1.x, intervalSequence[count].pt1.y, intervalSequence[count].pt2.x, intervalSequence[count].pt2.y);
            //}
            line l = reach(s, size, edgeSequence, intervalSequence, i+1, e);
            //if(reach(s, size, edgeSequence, intervalSequence, i+1, e)){return true;}
            if (l.pt1.x != -1){return l;}
        }
        if (isImmediatelyReachable(intervalSequence[i], R.v.a, R.v.b, R.e.e3)){
            intervalSequence[i+1] = immediateReachability(intervalSequence[i], R.v.a, R.v.b, R.e.e3);
            //for (count = 0; count <= i; ++count){
            //    printf("intervalSequence[%d] is (%f, %f) to (%f, %f)\n", count, intervalSequence[count].pt1.x, intervalSequence[count].pt1.y, intervalSequence[count].pt2.x, intervalSequence[count].pt2.y);
            //}
            line l = reach(s, size, edgeSequence, intervalSequence, i+1, e);
            //if(reach(s, size, edgeSequence, intervalSequence, i+1, e)){return true;}
            if (l.pt1.x != -1){return l;}
        }
        if (isImmediatelyReachable(intervalSequence[i], R.v.a, R.v.b, R.e.e4)){
            intervalSequence[i+1] = immediateReachability(intervalSequence[i], R.v.a, R.v.b, R.e.e4);
            //for (count = 0; count <= i; ++count){
            //    printf("intervalSequence[%d] is (%f, %f) to (%f, %f)\n", count, intervalSequence[count].pt1.x, intervalSequence[count].pt1.y, intervalSequence[count].pt2.x, intervalSequence[count].pt2.y);
            //}
            line l = reach(s, size, edgeSequence, intervalSequence, i+1, e);
            //if(reach(s, size, edgeSequence, intervalSequence, i+1, e)){return true;}
            if (l.pt1.x != -1){return l;}
        }
    }
    return lineNotFound;
}
