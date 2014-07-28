#ifndef FINDREGIONOREDGE_H_INCLUDED
#define FINDREGIONOREDGE_H_INCLUDED
#include <stdio.h>


/* hasEdgeWithLineSegment determines (sort of) whether a region has an edge
   containing a particular line segment, and if it does it returns the edge */
line hasEdgeWithLineSegment(region, line);

/* findEdgeWithLineSegment determines (sort of) whether an edge
   exists anywhere in an SPDI containing a particular line
   segment and if it does exist it returns the edge */
line findEdgeWithLineSegment(region [], int, line);

/* hasEdge determines whether a particular region has a particular edge */
bool hasEdge(region, line);

/* hasEntryEdge determines whether a particular region has
   a particular edge as an entry edge to the region */
bool hasEntryEdge(region, line);

/* existsRegionWithEntryEdge determines whether a region exists
   which has a particular edge as an entry edge */
bool existsRegionWithEntryEdge(region [], line, int);

/* findRegionWithEntryEdge finds a region which has
   a particular entry edge, if such a region exists */
region findRegionWithEntryEdge(region [], line, int);

/* numberOfReachableEdges finds the number of immediately reachable
   edges of a particular starting interval anywhere in an SPDI */
int numberOfReachableEdges(line, region [], int);

/* reachableEdge is only to be used when the number of reachable edges is one,
   it returns that reachable edge from the starting interval and the region,
   I am unsure whether this is still used */
line reachableEdge(line, region);

/* hasExitEdge determines whether a particular region has
   a particular edge as an exit edge to the region */
bool hasExitEdge(region, line);

/* existsRegionWithExitEdge determines whether a region exists
   which has a particular edge as an exit edge */
bool existsRegionWithExitEdge(region [], line, int);

/* findRegionWithExitEdge finds a region which has
   a particular exit edge, if such a region exists */
region findRegionWithExitEdge(region [], line, int);

line findEdgeInRegionWithSameX(line, region, double);

line findEdgeInRegionWithSameY(line, region, double);


#endif
