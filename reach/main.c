#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "basicStructures.h"
#include "controllabilityKernel.h"
#include "escape.h"
#include "findXorY.h"
#include "findRegionOrEdge.h"
#include "sort.h"
#include "reach.h"

int main()
{
    region R1;
    region R2;
    region R3;
    region R4;
    region R5;
    region R6;
    regionEdges re1 = { {{1, 1}, {2, 1}}, {{1, 1}, {1, 2}}, {{1, 2}, {2, 2}}, {{2, 1}, {2, 2}} };
    regionVectors rv1 = { {1, -1}, {1, -1} };
    regionEdges re2 = { {{2,1},{3,1}}, {{2,1},{2,2}}, {{2,2},{3,2}}, {{3,1},{3,2}} };
    regionVectors rv2 = { {1, 1}, {1, 1} };
    regionEdges re3 = { {{1,2},{2,2}}, {{1,2},{1,3}}, {{1,3},{2,3}}, {{2,2},{2,3}} };
    regionVectors rv3 = { {-1, -1}, {-1, -1} };
    regionEdges re4 = { {{2,2},{3,2}}, {{2,2},{2,3}}, {{2,3},{3,3}}, {{3,2},{3,3}} };
    regionVectors rv4 = { {-1, 1}, {0, 1} };
    regionEdges re5 = { {{1,3},{2,3}}, {{1,3},{1,4}}, {{1,4},{2,4}}, {{2,3},{2,4}} };
    regionVectors rv5 = { {-1, 0}, {-1, 0} };
    regionEdges re6 = { {{2,3},{3,3}}, {{2,3},{2,4}}, {{2,4},{3,4}}, {{3,3},{3,4}} };
    regionVectors rv6 = { {-1, 1}, {-1, 1}};
    R1.e = re1;
    R1.v = rv1;
    R2.e = re2;
    R2.v = rv2;
    R3.e = re3;
    R3.v = rv3;
    R4.e = re4;
    R4.v = rv4;
    R5.e = re5;
    R5.v = rv5;
    R6.e = re6;
    R6.v = rv6;
    region SPDI[6] = {R1, R2, R3, R4, R5, R6};
    line initial = { {2, 1.25}, {2, 1.75} };
    line target = { {1, 3}, {1, 4} };
    sort(&initial.pt1.x, &initial.pt1.y, &initial.pt2.x, &initial.pt2.y);
    sort(&target.pt1.x, &target.pt1.y, &target.pt2.x, &target.pt2.y);
    //line e1 = { {2, 1}, {2, 2} };
    //line e2 = { {2, 2}, {3, 2} };
    //line e3 = { {2, 2}, {2, 3} };
    //line e4 = { {1, 2}, {2, 2} };
    //line edgeList[4] = {e1, e2, e3, e4};
    int size = sizeof(SPDI) / sizeof(SPDI[0]);
    //line * k = malloc(sizeof(line) * 5);
    //k = controllabilityKernel(k, edgeList, 4, initial, SPDI, size);
    //int i = 0;
    //for (i = 0; i < 4; ++i) {
        //printf("k[%d] is (%f, %f) to (%f, %f)\n", i, k[i].pt1.x, k[i].pt1.y, k[i].pt2.x, k[i].pt2.y);
    //}
    line * edgeSequence = malloc(sizeof(line) * 1000);
    line * intervalSequence = malloc(sizeof(line) * 1000);
    intervalSequence[0] = initial;
    line l = reach(SPDI, size, edgeSequence, intervalSequence, 0, target);
    if (l.pt1.x != -1) {
        printf("yes, the edge (%f, %f) to (%f, %f)\nis reachable at (%f, %f) to (%f, %f)\nwhen starting from (%f, %f) to (%f, %f)\n",
        target.pt1.x, target.pt1.y, target.pt2.x, target.pt2.y, l.pt1.x, l.pt1.y, l.pt2.x, l.pt2.y, initial.pt1.x, initial.pt1.y, initial.pt2.x, initial.pt2.y);
    }
    else {
        printf("no, the edge (%f, %f) to (%f, %f) is not reachable when starting from (%f, %f) to (%f, %f)\n",
        target.pt1.x, target.pt1.y, target.pt2.x, target.pt2.y, initial.pt1.x, initial.pt1.y, initial.pt2.x, initial.pt2.y);
    }
    //free(k);
    return 0;
}
