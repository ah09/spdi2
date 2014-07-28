#include <stdio.h>
#include <math.h>


#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* min finds the lowest of four doubles */
inline double min(double a, double b, double c, double d) {
    return MIN(a, MIN(b, MIN(c, d)));
}

/* max finds the highest of four doubles */
inline double max(double a, double b, double c, double d) {
    return MAX(a, MAX(b, MAX(c, d)));
}

/* swap simply swaps the stored values of two doubles */
void swap(double *a, double *b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

/* sort takes the coordinates of two different points and orders them,
   first from left to right and (if one is above another) from bottom to top */
void sort(double *x1, double *x2, double *y1, double *y2) {
    if (*x1 <= *x2 && *y1 <= *y2) return;
    if (*x1 > *x2) {
        swap(x1, x2);
        swap(y1, y2);
    }
    else if (*x1 == *x2) {
        swap(y1, y2);
    }
}

typedef struct point {
    double x;
    double y;
} point;

typedef struct line {
    point pt1;
    point pt2;
} line;

typedef struct endlessline {
    point pt;
    double dx;
    double dy;
} endlessline;

//typedef line regionedges[4];
typedef struct regionedges {
    line e1;
    line e2;
    line e3;
    line e4;
} regionedges;

typedef struct vector {
    double x;
    double y;
} vector;

typedef struct regionvectors {
    vector a;
    vector b;
} regionvectors;

typedef struct region {
    regionedges e;
    regionvectors v;
} region;

/* findX takes a given line and y coordinate and returns the corresponding x coordinate,
   this can only work for non-horizontal lines and should not be called otherwise,
   the basic formula used is x = (C - B*y) / A, where A, B and C are doubles*/
inline double findX(double y, line l) {
    double D = l.pt1.x - l.pt2.x;
    double E = l.pt2.y - l.pt1.y;
    return l.pt1.x - (D / E)*(l.pt1.y + y);
}

/* findY takes a given line and x coordinate and returns the corresponding y coordinate,
   this can only work for non-vertical lines and should not be called otherwise,
   the basic formula used is y = (C - A*x) / B, where A, B and C are doubles*/
 inline double findY(double x, line l) {
    double D = l.pt1.x - l.pt2.x;
    double E = l.pt2.y - l.pt1.y;
    return (E / D)*(l.pt1.x - x) + l.pt1.y;
}

/* det finds the relation between a given vector and a line,
   this is used to help to find a point of intersection,
   if the result is zero then the two are parallel */
inline double det(vector v, line e) {
    return (v.y*(e.pt1.x - e.pt2.x)) - (v.x*(e.pt1.y - e.pt2.y));
}

/* intersection finds a point where a given vector starting
   from a given point intersects with a particular line,
   if there is no intersection then it will return null */
point intersection(point I, vector v, line e) {
    double d = det(v, e);
    double ex = e.pt1.x - e.pt2.x;
    double ey = e.pt2.y - e.pt1.y;
    double Iv = v.y*I.x - v.x*I.y;
    double exy = ey*e.pt1.x + ex*e.pt1.y;
    if (d != 0) {
        double x = (ex*Iv + v.x*exy) / d;
        double y = (v.y*exy - ey*Iv) / d;
        point p = {x, y};
        return p;
    }
    point p = { INFINITY, INFINITY };
    return p;
}

/* intervalRange finds a range on a projected line of infinite length which
   both satisfies the same linear equation as a given line and also is
   reachable to a trajectory from a given line and a pair of given vectors,
   the projected line is not the same as the edge as it is not bounded by
   any end points, rather the edge is a segment of this line */
line intervalRange(line I, vector a, vector b, line e) {
    point i1a = intersection(I.pt1, a, e);
    point i1b = intersection(I.pt1, b, e);
    point i2a = intersection(I.pt2, a, e);
    point i2b = intersection(I.pt2, b, e);
    double xmin = min(i1a.x, i1b.x, i2a.x, i2b.x);
    double ymin = min(i1a.y, i1b.y, i2a.y, i2b.y);
    if (i1a.x == INFINITY) {point i1a = { -INFINITY, -INFINITY }; }
    if (i1b.x == INFINITY) {point i1b = { -INFINITY, -INFINITY }; }
    if (i2a.x == INFINITY) {point i2a = { -INFINITY, -INFINITY }; }
    if (i2b.x == INFINITY) {point i2b = { -INFINITY, -INFINITY }; }
    double xmax = max(i1a.x, i1b.x, i2a.x, i2b.x);
    double ymax = max(i1a.y, i1b.y, i2a.y, i2b.y);
    line l;
    if (xmin < xmax) {
        l.pt1.x = xmin;
        l.pt1.y = findY(xmin, e);
        l.pt2.x = xmax;
        l.pt2.y = findY(xmax, e);
        return l;
    }
    l.pt1.x = findX(ymin, e);
    l.pt1.y = ymin;
    l.pt2.x = findX(ymax, e);
    l.pt2.y = ymax;
    return l;
}

/* range finds the intersection of the line found from
   intervalRange and a given line, it is the final step
   of finding the line of reachability of a given edge */
line range(line I, line e) {
    line l;
    if (I.pt1.x < I.pt2.x) {
        l.pt1.x = MAX(I.pt1.x, e.pt1.x);
        l.pt1.y = findY(l.pt1.x, I);
        l.pt2.x = MIN(I.pt2.x, e.pt2.x);
        l.pt2.y = findY(l.pt2.x, I);
        return l;
    }
    l.pt1.y = MAX(I.pt1.y, e.pt1.y);
    l.pt1.x = findX(l.pt1.y, I);
    l.pt2.y = MIN(I.pt2.y, e.pt2.y);
    l.pt2.x = findX(l.pt2.y, I);
    return l;
}

/* reachability prints the reachable range of a given edge from
   a given starting Interval and a given pair of vectors, in a
   neat way and prints a statement noting if it is unreachable */
void reachability(line I, vector a, vector b, line e) {
    line ir = intervalRange(I, a, b, e);
    if ((I.pt1.x == e.pt1.x && I.pt1.y == e.pt1.y && I.pt2.x == e.pt2.x && I.pt2.y == e.pt2.y) || ir.pt1.x > e.pt2.x || ir.pt2.x < e.pt1.x || (ir.pt1.x == ir.pt2.x && (ir.pt1.y > e.pt2.y || ir.pt2.y < e.pt1.y))) {
        printf("the edge (%f, %f) to (%f, %f) is unreachable\n", e.pt1.x, e.pt1.y, e.pt2.x, e.pt2.y);
    }
    else{
        line r = range(ir, e);
        if (r.pt1.x == r.pt2.x && r.pt1.y == r.pt2.y){
            printf("the edge (%f, %f) to (%f, %f) is unreachable\n", e.pt1.x, e.pt1.y, e.pt2.x, e.pt2.y);
        }
        else{
            printf("the edge from (%f, %f) to (%f, %f) is reachable from (%f, %f) to (%f, %f)\n", e.pt1.x, e.pt1.y, e.pt2.x, e.pt2.y, r.pt1.x, r.pt1.y, r.pt2.x, r.pt2.y);
        }
    }
}

/* reachabilityrange essentially does what the function reachability
   does except it returns a line rather than printing a string, this
   should only be called if such a line exists to be returned */
line reachabilityrange(region r, line I, line e){
    line ir = intervalRange(I, r.v.a, r.v.b, e);
    if ((I.pt1.x != e.pt1.x || I.pt1.y != e.pt1.y || I.pt2.x != e.pt2.x || I.pt2.y != e.pt2.y) && ir.pt1.x <= e.pt2.x && ir.pt2.x >= e.pt1.x && (ir.pt1.x != ir.pt2.x || (ir.pt1.y <= e.pt2.y && ir.pt2.y >= e.pt1.y))) {
        line l = range(ir, e);
        if (l.pt1.x != l.pt2.x || l.pt1.y != l.pt2.y){
            return l;
        }
    }
}

/* distance finds the distance between two points */
double distance(point p1, point p2){
    double d = sqrt(((p1.x - p2.x)*(p1.x - p2.x)) + ((p1.y - p2.y)*(p1.y - p2.y)));
    return d;
}

point lineintersection(point p1, vector v1, point p2, vector v2){
    point p;
    double A1 = v1.y;
    double A2 = v2.y;
    double B1 = -v1.x;
    double B2 = -v2.x;
    double C1 = A1*p1.x + B1*p1.y;
    double C2 = A2*p2.x + B1*p2.y;
    double d = A1*B2 - A2*B1;
    p.x = ((B2*C1 - B1*C2) / d) + MIN(p1.x, p2.x);
    p.y = ((A1*C2 - A2*C1) / d) + MIN(p1.y, p2.y);
    return p;
}

/* tube should return possible trajectories in a region */
void tube(region r, line I, line e){
    line l = reachabilityrange(r, I, e);
    vector anegative = {-r.v.a.x, -r.v.a.y};
    vector bnegative = {-r.v.b.x, -r.v.b.y};
    printf("I.pt1 = (%f, %f), I.pt2 = (%f, %f), e.pt1 = (%f, %f), e.pt2 = (%f, %f)\n", I.pt1.x, I.pt1.y, I.pt2.x, I.pt2.y, e.pt1.x, e.pt1.y, e.pt2.x, e.pt2.y);
    if ((I.pt1.x == e.pt1.x && I.pt1.y == e.pt1.y) || (I.pt2.x == e.pt2.x && I.pt2.y == e.pt2.y)){
        if (r.v.a.x == r.v.b.x && r.v.a.y == r.v.b.y){
            printf("(%f, %f) to (%f, %f)\n", I.pt1.x, I.pt1.y, l.pt1.x, l.pt1.y);
            printf("(%f, %f) to (%f, %f)\n", I.pt2.x, I.pt2.y, l.pt2.x, l.pt2.y);
        }
        else if (I.pt1.x == e.pt1.x && I.pt1.y == e.pt1.y){
            point t1;
            point i1 = lineintersection(I.pt2, r.v.a, e.pt2, bnegative);
            point i2 = lineintersection(I.pt2, r.v.b, e.pt2, anegative);
            if (distance(i1, I.pt1) > distance(i2, I.pt1)) {t1.x = i1.x; t1.y = i1.y;} else {t1.x = i2.x; t1.y = i2.y;}
            printf("(%f, %f) to (%f, %f)\n", I.pt1.x, I.pt1.y, l.pt1.x, l.pt1.y);
            printf("(%f, %f) to (%f, %f) to (%f, %f)\n", I.pt2.x, I.pt2.y, t1.x, t1.y, l.pt2.x, l.pt2.y);
        }
    }
    else if ((I.pt1.x == e.pt2.x && I.pt1.y == e.pt2.y) || (I.pt2.x == e.pt1.x && I.pt2.y == e.pt1.y)){
        if (r.v.a.x == r.v.b.x && r.v.a.y == r.v.b.y){
            printf("(%f, %f) to (%f, %f)5\n", I.pt1.x, I.pt1.y, l.pt1.x, l.pt1.y);
            printf("(%f, %f) to (%f, %f)6\n", I.pt2.x, I.pt2.y, l.pt2.x, l.pt2.y);
        }
        else if (I.pt1.x == e.pt2.x && I.pt1.y == e.pt2.y){
            point t1;
            point i1 = lineintersection(I.pt2, r.v.a, e.pt1, bnegative);
            point i2 = lineintersection(I.pt2, r.v.b, e.pt1, anegative);
            if (distance(i1, I.pt1) > distance(i2, I.pt1)) {t1.x = i1.x; t1.y = i1.y;} else {t1.x = i2.x; t1.y = i2.y;}
            printf("(%f, %f) to (%f, %f)\n", I.pt1.x, I.pt1.y, l.pt1.x, l.pt1.y);
            printf("(%f, %f) to (%f, %f) to (%f, %f)\n", I.pt2.x, I.pt2.y, t1.x, t1.y, l.pt2.x, l.pt2.y);
        }
        else if (I.pt2.x == e.pt1.x && I.pt2.y == e.pt1.y){
            point t1;
            point i1 = lineintersection(I.pt1, r.v.a, e.pt2, r.v.b);
            point i2 = lineintersection(I.pt1, r.v.b, e.pt2, r.v.a);
            printf("point 1 is (%f, %f)\n", i1.x, i1.y);
            printf("point 2 is (%f, %f)\n", i2.x, i2.y);
            if (distance(i1, I.pt2) > distance(i2, I.pt2)) {t1.x = i1.x; t1.y = i1.y;} else {t1.x = i2.x; t1.y = i2.y;}
            printf("(%f, %f) to (%f, %f)\n", I.pt2.x, I.pt2.y, l.pt1.x, l.pt1.y);
            printf("(%f, %f) to (%f, %f) to (%f, %f)\n", I.pt1.x, I.pt1.y, t1.x, t1.y, l.pt2.x, l.pt2.y);
        }
    }
    else {
        line l1;
        l1.pt1 = I.pt1;
        l1.pt2 = e.pt1;
        line l2;
        l2.pt1 = I.pt2;
        l2.pt2 = e.pt2;
        vector lv;
        lv.x = l1.pt1.x - l1.pt2.x;
        lv.y = l1.pt1.y - l1.pt2.y;
        if (det(lv, l2) == 0){
            printf("(%f, %f) to (%f, %f)\n", I.pt1.x, I.pt1.y, l.pt1.x, l.pt1.y);
            printf("(%f, %f) to (%f, %f)\n", I.pt2.x, I.pt2.y, l.pt2.x, l.pt2.y);
        }
        else {
            point p = intersection(l.pt1, lv, l2);
            if (2*p.x == l1.pt1.x + l1.pt2.x || 2*p.y == l1.pt1.y + l1.pt2.y){
                printf("(%f, %f) to (%f, %f)\n", I.pt1.x, I.pt1.y, l.pt2.x, l.pt2.y);
                printf("(%f, %f) to (%f, %f)\n", I.pt2.x, I.pt2.y, l.pt1.x, l.pt1.y);
            }
            else {
                printf("(%f, %f) to (%f, %f)\n", I.pt1.x, I.pt1.y, l.pt1.x, l.pt1.y);
                printf("(%f, %f) to (%f, %f)\n", I.pt2.x, I.pt2.y, l.pt2.x, l.pt2.y);
            }
        }
    }
}

int main()
{
    regionvectors rv = { {2, 1}, {1, 2} };
    regionedges re = { {{1,1},{1,4}}, {{1,4},{4,4}}, {{4,4},{4,1}}, {{4,1},{1,1}} };
    region r;
    r.e = re;
    r.v = rv;
    sort(&r.e.e1.pt1.x, &r.e.e1.pt2.x, &r.e.e1.pt1.y, &r.e.e1.pt2.y);
    sort(&r.e.e2.pt1.x, &r.e.e2.pt2.x, &r.e.e2.pt1.y, &r.e.e2.pt2.y);
    sort(&r.e.e3.pt1.x, &r.e.e3.pt2.x, &r.e.e3.pt1.y, &r.e.e3.pt2.y);
    sort(&r.e.e4.pt1.x, &r.e.e4.pt2.x, &r.e.e4.pt1.y, &r.e.e4.pt2.y);
    reachability(r.e.e1, r.v.a, r.v.b, r.e.e2);
    //reachability(r.e.e1, r.v.a, r.v.b, r.e.e3);
    //reachability(r.e.e1, r.v.a, r.v.b, r.e.e4);
    tube(r, r.e.e1, r.e.e2);
    point p1 = {1, 1};
    point p2 = {4, 4};
    vector v1 = {2, 1};
    vector v2 = {1, 2};
    point test = lineintersection(p1, v1, p2, v2);
    printf("test is (%f, %f)\n", test.x, test.y);
    //tube(r, r.e.e1, r.e.e3);
    return 0;
}
