#include <stdbool.h>
#include <stdlib.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "findRegionOrEdge.h"
#include "immediateReachability.h"
#include "controllabilityKernel.h"


struct line * succ(line suc[], line edgeList[], int numberOfEdges, line I, region s[], int size){
    int i = 0;
    region R;
    line l;
    for (i = 0; i < numberOfEdges; ++i){
        R = findRegionWithEntryEdge(s, edgeList[i], size);
        l = immediateReachability(I, R.v.a, R.v.b, edgeList[(i+1)%numberOfEdges]);
        suc[i] = l;
        I = l;
    }
    return suc;
}

struct line * pred(line pre[], line edgeList[], int numberOfEdges, line I, region s[], int size){
    int i = 0;
    region R;
    line l;
    for (i = 0; i < numberOfEdges; ++i){
        R = findRegionWithExitEdge(s, edgeList[i], size);
        l = immediateReachabilityReverse(I, R.v.a, R.v.b, edgeList[(numberOfEdges - 1 - i)%numberOfEdges]);
        pre[i] = l;
        I = l;
    }
    return pre;
}

struct line * controllabilityKernel(line kernel[], line edgeList[], int numberOfEdges, line I, region s[], int size){
    int i = 0;
    line * suc = malloc(sizeof(line) * numberOfEdges);
    line * pre = malloc(sizeof(line) * numberOfEdges);
    suc = succ(suc, edgeList, numberOfEdges, I, s, size);
    pre = pred(pre, edgeList, numberOfEdges, I, s, size);
    kernel[0] = collinearIntersection(I, collinearIntersection(suc[numberOfEdges - 1], pre[numberOfEdges - 1]));
    for (i = 1; i < numberOfEdges + 1; ++i){
        kernel[i] = collinearIntersection(suc[i - 1], pre[numberOfEdges - 1 - i]);
    }
    free(suc);
    free(pre);
    return kernel;
}
