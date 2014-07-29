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
    printf("enter size of SPDI\n");
    int size;
    scanf("%d", &(size));
    region * SPDI = malloc(sizeof(region) * size);
    int i = 0;
    for (i = 0; i < size; ++i) {
        printf("enter R%d.e.e1.pt1.x, R%d.e.e1.pt1.y, R%d.e.e1.pt2.x, R%d.e.e1.pt2.y, R%d.e.e2.pt1.x, R%d.e.e2.pt1.y, R%d.e.e2.pt2.x, R%d.e.e2.pt2.y, R%d.e.e3.pt1.x, R%d.e.e3.pt1.y, R%d.e.e3.pt2.x, R%d.e.e3.pt2.y, R%d.e.e4.pt1.x, R%d.e.e4.pt1.y, R%d.e.e4.pt2.x, R%d.e.e4.pt2.y\n", i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1);
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &(SPDI[i].e.e1.pt1.x), &(SPDI[i].e.e1.pt1.y), &(SPDI[i].e.e1.pt2.x), &(SPDI[i].e.e1.pt2.y), &(SPDI[i].e.e2.pt1.x), &(SPDI[i].e.e2.pt1.y), &(SPDI[i].e.e2.pt2.x), &(SPDI[i].e.e2.pt2.y), &(SPDI[i].e.e3.pt1.x), &(SPDI[i].e.e3.pt1.y), &(SPDI[i].e.e3.pt2.x), &(SPDI[i].e.e3.pt2.y), &(SPDI[i].e.e4.pt1.x), &(SPDI[i].e.e4.pt1.y), &(SPDI[i].e.e4.pt2.x), &(SPDI[i].e.e4.pt2.y));
        printf("enter R%d.v.a.x, R%d.v.a.y, R%d.v.b.x, R%d.v.b.y\n", i+1, i+1, i+1 ,i+1);
        scanf("%lf %lf %lf %lf", &(SPDI[i].v.a.x), &(SPDI[i].v.a.y), &(SPDI[i].v.b.x), &(SPDI[i].v.b.y));
    }
    //region R1;
    //region R2;
    //region R3;
    //region R4;
    //region R5;
    //region R6;
    /*printf("enter R1.e.e1.pt1.x, R1.e.e1.pt1.y, R1.e.e1.pt2.x, R1.e.e1.pt2.y, R1.e.e2.pt1.x, R1.e.e2.pt1.y, R1.e.e2.pt2.x, R1.e.e2.pt2.y, R1.e.e3.pt1.x, R1.e.e3.pt1.y, R1.e.e3.pt2.x, R1.e.e3.pt2.y, R1.e.e4.pt1.x, R1.e.e4.pt1.y, R1.e.e4.pt2.x, R1.e.e4.pt2.y\n");
    scanf("%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", &(R1.e.e1.pt1.x), &(R1.e.e1.pt1.y), &(R1.e.e1.pt2.x), &(R1.e.e1.pt2.y), &(R1.e.e2.pt1.x), &(R1.e.e2.pt1.y), &(R1.e.e2.pt2.x), &(R1.e.e2.pt2.y), &(R1.e.e3.pt1.x), &(R1.e.e3.pt1.y), &(R1.e.e3.pt2.x), &(R1.e.e3.pt2.y), &(R1.e.e4.pt1.x), &(R1.e.e4.pt1.y), &(R1.e.e4.pt2.x), &(R1.e.e4.pt2.y));*/
    //regionEdges re1 = { {{1, 1}, {2, 1}}, {{1, 1}, {1, 2}}, {{1, 2}, {2, 2}}, {{2, 1}, {2, 2}} };
    /*printf("enter R1.v.a.x, R1.v.a.y, R1.v.b.x, R1.v.b.y\n");
    scanf("%lf, %lf, %lf, %lf\n", &(R1.v.a.x), &(R1.v.a.y), &(R1.v.b.x), &(R1.v.b.y));*/
    //regionVectors rv1 = { {1, -1}, {1, -1} };
    /*printf("enter R2.e.e1.pt1.x, R2.e.e1.pt1.y, R2.e.e1.pt2.x, R2.e.e1.pt2.y, R2.e.e2.pt1.x, R2.e.e2.pt1.y, R2.e.e2.pt2.x, R2.e.e2.pt2.y, R2.e.e3.pt1.x, R2.e.e3.pt1.y, R2.e.e3.pt2.x, R2.e.e3.pt2.y, R2.e.e4.pt1.x, R2.e.e4.pt1.y, R2.e.e4.pt2.x, R2.e.e4.pt2.y\n");
    scanf("%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf", &(R2.e.e1.pt1.x), &(R2.e.e1.pt1.y), &(R2.e.e1.pt2.x), &(R2.e.e1.pt2.y), &(R2.e.e2.pt1.x), &(R2.e.e2.pt1.y), &(R2.e.e2.pt2.x), &(R2.e.e2.pt2.y), &(R2.e.e3.pt1.x), &(R2.e.e3.pt1.y), &(R2.e.e3.pt2.x), &(R2.e.e3.pt2.y), &(R2.e.e4.pt1.x), &(R2.e.e4.pt1.y), &(R2.e.e4.pt2.x), &(R2.e.e4.pt2.y));*/
    //regionEdges re2 = { {{2,1},{3,1}}, {{2,1},{2,2}}, {{2,2},{3,2}}, {{3,1},{3,2}} };
    /*printf("enter R2.v.a.x, R2.v.a.y, R2.v.b.x, R2.v.b.y\n");
    scanf("%lf, %lf, %lf, %lf", &(R2.v.a.x), &(R2.v.a.y), &(R2.v.b.x), &(R2.v.b.y));*/
    //regionVectors rv2 = { {1, 1}, {1, 1} };
    /*printf("enter R3.e.e1.pt1.x, R3.e.e1.pt1.y, R3.e.e1.pt2.x, R3.e.e1.pt2.y, R3.e.e2.pt1.x, R3.e.e2.pt1.y, R3.e.e2.pt2.x, R3.e.e2.pt2.y, R3.e.e3.pt1.x, R3.e.e3.pt1.y, R3.e.e3.pt2.x, R3.e.e3.pt2.y, R3.e.e4.pt1.x, R3.e.e4.pt1.y, R3.e.e4.pt2.x, R3.e.e4.pt2.y\n");
    scanf("%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf", &(R3.e.e1.pt1.x), &(R3.e.e1.pt1.y), &(R3.e.e1.pt2.x), &(R3.e.e1.pt2.y), &(R3.e.e2.pt1.x), &(R3.e.e2.pt1.y), &(R3.e.e2.pt2.x), &(R3.e.e2.pt2.y), &(R3.e.e3.pt1.x), &(R3.e.e3.pt1.y), &(R3.e.e3.pt2.x), &(R3.e.e3.pt2.y), &(R3.e.e4.pt1.x), &(R3.e.e4.pt1.y), &(R3.e.e4.pt2.x), &(R3.e.e4.pt2.y));*/
    //regionEdges re3 = { {{1,2},{2,2}}, {{1,2},{1,3}}, {{1,3},{2,3}}, {{2,2},{2,3}} };
    /*printf("enter R3.v.a.x, R3.v.a.y, R3.v.b.x, R3.v.b.y\n");
    scanf("%lf, %lf, %lf, %lf", &(R3.v.a.x), &(R3.v.a.y), &(R3.v.b.x), &(R3.v.b.y));*/
    //regionVectors rv3 = { {-1, -1}, {-1, -1} };
    /*printf("enter R4.e.e1.pt1.x, R4.e.e1.pt1.y, R4.e.e1.pt2.x, R4.e.e1.pt2.y, R4.e.e2.pt1.x, R4.e.e2.pt1.y, R4.e.e2.pt2.x, R4.e.e2.pt2.y, R4.e.e3.pt1.x, R4.e.e3.pt1.y, R4.e.e3.pt2.x, R4.e.e3.pt2.y, R4.e.e4.pt1.x, R4.e.e4.pt1.y, R4.e.e4.pt2.x, R4.e.e4.pt2.y\n");
    scanf("%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf", &(R4.e.e1.pt1.x), &(R4.e.e1.pt1.y), &(R4.e.e1.pt2.x), &(R4.e.e1.pt2.y), &(R4.e.e2.pt1.x), &(R4.e.e2.pt1.y), &(R4.e.e2.pt2.x), &(R4.e.e2.pt2.y), &(R4.e.e3.pt1.x), &(R4.e.e3.pt1.y), &(R4.e.e3.pt2.x), &(R4.e.e3.pt2.y), &(R4.e.e4.pt1.x), &(R4.e.e4.pt1.y), &(R4.e.e4.pt2.x), &(R4.e.e4.pt2.y));*/
    //regionEdges re4 = { {{2,2},{3,2}}, {{2,2},{2,3}}, {{2,3},{3,3}}, {{3,2},{3,3}} };
    /*printf("enter R4.v.a.x, R4.v.a.y, R4.v.b.x, R4.v.b.y\n");
    scanf("%lf, %lf, %lf, %lf", &(R4.v.a.x), &(R4.v.a.y), &(R4.v.b.x), &(R4.v.b.y));*/
    //regionVectors rv4 = { {-1, 1}, {0, 1} };
    /*printf("enter R5.e.e1.pt1.x, R5.e.e1.pt1.y, R5.e.e1.pt2.x, R5.e.e1.pt2.y, R5.e.e2.pt1.x, R5.e.e2.pt1.y, R5.e.e2.pt2.x, R5.e.e2.pt2.y, R5.e.e3.pt1.x, R5.e.e3.pt1.y, R5.e.e3.pt2.x, R5.e.e3.pt2.y, R5.e.e4.pt1.x, R5.e.e4.pt1.y, R5.e.e4.pt2.x, R5.e.e4.pt2.y\n");
    scanf("%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf", &(R5.e.e1.pt1.x), &(R5.e.e1.pt1.y), &(R5.e.e1.pt2.x), &(R5.e.e1.pt2.y), &(R5.e.e2.pt1.x), &(R5.e.e2.pt1.y), &(R5.e.e2.pt2.x), &(R5.e.e2.pt2.y), &(R5.e.e3.pt1.x), &(R5.e.e3.pt1.y), &(R5.e.e3.pt2.x), &(R5.e.e3.pt2.y), &(R5.e.e4.pt1.x), &(R5.e.e4.pt1.y), &(R5.e.e4.pt2.x), &(R5.e.e4.pt2.y));*/
    //regionEdges re5 = { {{1,3},{2,3}}, {{1,3},{1,4}}, {{1,4},{2,4}}, {{2,3},{2,4}} };
    /*printf("enter R5.v.a.x, R5.v.a.y, R5.v.b.x, R5.v.b.y\n");
    scanf("%lf, %lf, %lf, %lf", &(R5.v.a.x), &(R5.v.a.y), &(R5.v.b.x), &(R5.v.b.y));*/
    //regionVectors rv5 = { {-1, 0}, {-1, 0} };
    /*printf("enter R6.e.e1.pt1.x, R6.e.e1.pt1.y, R6.e.e1.pt2.x, R6.e.e1.pt2.y, R6.e.e2.pt1.x, R6.e.e2.pt1.y, R6.e.e2.pt2.x, R6.e.e2.pt2.y, R6.e.e3.pt1.x, R6.e.e3.pt1.y, R6.e.e3.pt2.x, R6.e.e3.pt2.y, R6.e.e4.pt1.x, R6.e.e4.pt1.y, R6.e.e4.pt2.x, R6.e.e4.pt2.y\n");
    scanf("%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf", &(R6.e.e1.pt1.x), &(R6.e.e1.pt1.y), &(R6.e.e1.pt2.x), &(R6.e.e1.pt2.y), &(R6.e.e2.pt1.x), &(R6.e.e2.pt1.y), &(R6.e.e2.pt2.x), &(R6.e.e2.pt2.y), &(R6.e.e3.pt1.x), &(R6.e.e3.pt1.y), &(R6.e.e3.pt2.x), &(R6.e.e3.pt2.y), &(R6.e.e4.pt1.x), &(R6.e.e4.pt1.y), &(R6.e.e4.pt2.x), &(R6.e.e4.pt2.y));*/
    //regionEdges re6 = { {{2,3},{3,3}}, {{2,3},{2,4}}, {{2,4},{3,4}}, {{3,3},{3,4}} };
    /*printf("enter R6.v.a.x, R6.v.a.y, R6.v.b.x, R6.v.b.y\n");
    scanf("%lf, %lf, %lf, %lf", &(R6.v.a.x), &(R6.v.a.y), &(R6.v.b.x), &(R6.v.b.y));*/
    //regionVectors rv6 = { {-1, 1}, {-1, 1}};
    //R1.e = re1;
    //R1.v = rv1;
    //R2.e = re2;
    //R2.v = rv2;
    //R3.e = re3;
    //R3.v = rv3;
    //R4.e = re4;
    //R4.v = rv4;
    //R5.e = re5;
    //R5.v = rv5;
    //R6.e = re6;
    //R6.v = rv6;
    //region SPDI[6] = {R1, R2, R3, R4, R5, R6};
    line initial;
    printf("enter initial.pt1.x, initial.pt1.y, initial.pt2.x, initial.pt2.y\n");
    scanf("%lf %lf %lf %lf", &(initial.pt1.x), &(initial.pt1.y), &(initial.pt2.x), &(initial.pt2.y));
    //line initial = { {2, 1.25}, {2, 1.75} };
    line target;
    printf("enter target.pt1.x, target.pt1.y, target.pt2.x, target.pt2.y\n");
    scanf("%lf %lf %lf %lf", &(target.pt1.x), &(target.pt1.y), &(target.pt2.x), &(target.pt2.y));
    //line target = { {1, 3}, {1, 4} };
    sort(&initial.pt1.x, &initial.pt1.y, &initial.pt2.x, &initial.pt2.y);
    sort(&target.pt1.x, &target.pt1.y, &target.pt2.x, &target.pt2.y);
    //line e1 = { {2, 1}, {2, 2} };
    //line e2 = { {2, 2}, {3, 2} };
    //line e3 = { {2, 2}, {2, 3} };
    //line e4 = { {1, 2}, {2, 2} };
    //line edgeList[4] = {e1, e2, e3, e4};
    //int size = sizeof(SPDI) / sizeof(SPDI[0]);
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
    free(SPDI);
    return 0;
}
