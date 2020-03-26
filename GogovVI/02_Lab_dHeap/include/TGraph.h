#ifndef _TGRAPH_H_
#define _TGRAPH_H_
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "../include/Pair.h"
#include "../include/Edge.h"
#include "../include/THeap.h"
#include "../include/TSplitSet.h"

class TGraph
{
	Edge* edges = nullptr;
	int vertexCount = 0, edgesCount = 0;
	bool Connectivity(const bool* adjacencyMatrix) const;
public:
	TGraph();
	TGraph(Edge* edges_, int edgesCount_, int vertexCount_);

	TGraph KruskalAlgorithm();
	void DijkstraAlgorithm(std::vector<std::vector<int>>& path, float*& resultDist, int vertexStart = 0);

	friend std::ostream& operator<< (std::ostream& out, const TGraph& temp);
	friend std::istream& operator>> (std::istream& out, TGraph& temp);
};
#endif // !_TGRAPH_H_