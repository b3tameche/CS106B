/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include <algorithm>
#include "random.h"
#include "foreach.h"

using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world, double costFn(Loc from, Loc to, Grid<double>& world), double heuristic(Loc from, Loc to, Grid<double>& world)) {
	Vector<Loc> reversePath;
	TrailblazerPQueue<Loc> candidates;
	Map<Loc, LocInfo> LocInfos; // stores locations as a key and its info as value

	for (int i = 0; i < world.numRows(); i++) { // make all locations gray
		for (int j = 0; j < world.numCols(); j++) {
			LocInfos[makeLoc(i ,j)].color = GRAY;
		}
	}

	LocInfos[start].color = YELLOW;
	colorCell(world, start, YELLOW);

	LocInfos[start].distance = 0;
	candidates.enqueue(start, heuristic(start, end, world));

	/* ამის მერე ყველაფერი ფსევდო კოდის მიხედვით მიწერია და აღარ დავუწერ კომენტარებს */
	while (!candidates.isEmpty()) {
		Loc curr = candidates.dequeueMin();
		LocInfos[curr].color = GREEN;
		colorCell(world, curr, GREEN);

		if (curr == end) {
			while (curr != start) {
				reversePath += curr;
				curr = LocInfos[curr].parent;
			}
			reversePath += start;
			reverse(reversePath.begin(), reversePath.end());
			return reversePath;
		}

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				Loc adj = makeLoc(curr.row + i, curr.col + j);
				if (adj == curr || !world.inBounds(adj.row, adj.col)) continue;

				if (LocInfos[adj].color == GRAY) {
					LocInfos[adj].color = YELLOW;
					LocInfos[adj].distance = LocInfos[curr].distance + costFn(curr,adj,world);
					LocInfos[adj].parent = curr;
					candidates.enqueue(adj, LocInfos[curr].distance + costFn(curr,adj,world) + heuristic(adj,end,world));
					colorCell(world, adj, YELLOW);
				} else if ((LocInfos[adj].color == YELLOW) && (LocInfos[adj].distance > costFn(curr, adj, world) + LocInfos[curr].distance)) {
					LocInfos[adj].distance=LocInfos[curr].distance + costFn(curr,adj,world);
					LocInfos[adj].parent = curr;
					candidates.decreaseKey(adj, LocInfos[curr].distance + costFn(curr, adj, world) + heuristic(adj, end,world));
				}
			}
		}
	}
}

Loc getRoot(Loc loc, Grid<Loc>& links){ // find root of a cluster
	if(links[loc.row][loc.col] == loc) return loc;
	return getRoot(links[loc.row][loc.col], links);
}

Set<Edge> createMaze(int numRows, int numCols) {

	TrailblazerPQueue<Edge> pq;
	Grid<Loc> links(numRows, numCols);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
			links[i][j] = makeLoc(i, j); // store for further purposes (to determine cluster root)

			Loc right = makeLoc(i, j + 1);
			Loc down = makeLoc(i + 1, j);

			if(links.inBounds(i, j + 1)) pq.enqueue(makeEdge(makeLoc(i, j), right), randomReal(0, 1)); // make right edge
			if(links.inBounds(i + 1, j)) pq.enqueue(makeEdge(makeLoc(i, j), down), randomReal(0, 1)); // make down edge
        }
    }

	int clusterCount = numRows * numCols; // initial value

	Set<Edge> result;

	while(!pq.isEmpty()){
		Edge edge = pq.dequeueMin();

		Loc startOrigin = getRoot(edge.start, links); // start node
		Loc endOrigin = getRoot(edge.end, links); // end node

		if(startOrigin != endOrigin){ // if they're not in the same cluster
			links[endOrigin.row][endOrigin.col] = startOrigin;
			clusterCount -= 1;
			result += edge;
		}
	}

	return result;
}
