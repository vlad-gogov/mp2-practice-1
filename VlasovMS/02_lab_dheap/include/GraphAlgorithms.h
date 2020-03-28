#ifndef _GRAPHALGORITHMS_H_
#define _GRAPHALGORITHMS_H_

#include "TGraph.h"

class GraphAlgorithms
{
public:
    static TGraph kruskalAlgorithm(const TGraph& graph);
    static TPathData dijkstraAlgorithm(const TGraph& graph, TVertexId startVertex = 0);
};

#endif