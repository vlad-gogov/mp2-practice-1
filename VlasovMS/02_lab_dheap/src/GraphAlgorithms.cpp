#include "GraphAlgorithms.h"

TGraph GraphAlgorithms::kruskalAlgorithm(const TGraph& graph)
{
    return graph.findMinimumSpanningTree();
}

TPathData GraphAlgorithms::dijkstraAlgorithm(const TGraph& graph, TVertexId startVertex)
{
    return graph.findShortestPaths(startVertex);
}
