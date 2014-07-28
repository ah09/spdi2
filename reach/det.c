#include "basicStructures.h"
#include "det.h"


inline double det(vector v, line e) {
    return (v.y*(e.pt1.x - e.pt2.x)) - (v.x*(e.pt1.y - e.pt2.y));
}
