#include <stdbool.h>
#include "basicStructures.h"
#include "compare.h"
#include "cycle.h"


bool patternDetection(line sequence[], int size){
    int i = 0;
    int j = 0;
    for (i = size-2; i >= 0; --i){
        if (sameLineAs(sequence[i], sequence[size-1]) && size >= 3*(size-i-1)){
            line cycle[size-i - 1];
            for (j = 0; j < size-i-1; ++j){
                cycle[j] = sequence[i+j+1];
            }
            for (j = 0; j < size-i- 2; ++j){
                if (!sameLineAs(sequence[2*(i+1)-size+j], cycle[j]) || !sameLineAs(sequence[3*(i+1)-2*size+j], cycle[j]))//(sequence[2*(i+1)-size + j].pt1.x != cycle[j].pt1.x || sequence[2*(i+1)-size + j].pt1.y != cycle[j].pt1.y || sequence[2*(i+1)-size + j].pt2.x != cycle[j].pt2.x || sequence[2*(i+1)-size + j].pt2.y != cycle[j].pt2.y
                    //|| sequence[3*(i+1) - 2*size + j].pt1.x != cycle[j].pt1.x || sequence[3*(i+1) - 2*size + j].pt1.y != cycle[j].pt1.y || sequence[3*(i+1) - 2*size + j].pt2.x != cycle[j].pt2.x || sequence[3*(i+1) - 2*size + j].pt2.y != cycle[j].pt2.y)
                {return false;}
            }
            return true;
        }
    }
    return false;
}

int cycleNumber(line sequence[], int size){
    int i = 0;
    for (i = size-2; i>= 0; --i){
        if (sameLineAs(sequence[i], sequence[size-1]) && size >= 3*(size-i-1)){
            return size-i-1;
        }
    }
    return -1;
}
