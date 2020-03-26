#include <iostream>
#include "../include/TGraph.h"

int main()
{
	TGraph graph1, graph2, result;
	Edge edgeGraph1[11] = {
		Edge(0,1,8),
		Edge(1,5,2),
		Edge(5,0,2),
		Edge(0,4,3),
		Edge(1,4,0),
		Edge(1,3,1),
		Edge(3,4,3),
		Edge(3,2,5),
		Edge(1,2,10),
		Edge(4,2,2),
		Edge(2,5,9)
	};
	try
	{
		graph1 = TGraph(edgeGraph1, 11, 6);
	}
	catch (const char* message)
	{
		std::cout << message;
	}
	std::cout << "Graph: \n" << graph1;
	std::cout << "Kruskal's algorithm:\n";
	try
	{
		result = graph1.KruskalAlgorithm();
		std::cout << result;
	}
	catch (const char* message)
	{
		std::cout << message;
	}
	std::cout << "-------------------------------------------------------------------\n";
	try
	{
		std::cin >> graph1;
		std::cout << "Kruskal's algorithm:\n";
		result = graph1.KruskalAlgorithm();
		std::cout << result;
	}
	catch (const char* message)
	{
		std::cout << message;
	}
	std::cout << "-------------------------------------------------------------------\n";
	Edge edgeGraph2[13] = {
		Edge(0,1,5),
		Edge(0,2,8),
		Edge(0,3,11),
		Edge(1,2,2),
		Edge(1,4,4),
		Edge(2,3,3),
		Edge(2,4,2),
		Edge(3,5,8),
		Edge(4,5,6),
		Edge(4,7,1),
		Edge(5,6,13),
		Edge(5,7,24),
		Edge(6,7,5),
	};
	try
	{
		graph2 = TGraph(edgeGraph2, 13, 8);
	}
	catch (const char* message)
	{
		std::cout << message;
	}
	std::cout << "Graph: \n" << graph2;

	std::vector<std::vector<int>> path;
	std::cout << "Dijkstra's algorithm:\n";
	float* result_dist;
	try
	{
		graph2.DijkstraAlgorithm(path, result_dist);
		for (int i = 0; i < path.size(); i++)
		{
			int current_size = path[i].size();
			for (int j = 0; j < current_size; j++)
			{
				if (j != current_size - 1)
					std::cout << path[i][j] << "-";
				else
					std::cout << path[i][j] << " Distance: " << result_dist[path[i][j]];
			}
			std::cout << std::endl;
		}
		delete[] result_dist;
		path.clear();
	}
	catch (const char* message)
	{
		std::cout << message;
	}
	std::cout << "-------------------------------------------------------------------\n";
	std::cout << "Dijkstra's algorithm:\n";
	try
	{
		std::cin >> graph2;
		std::cout << graph2;
		graph2.DijkstraAlgorithm(path, result_dist);
		for (int i = 0; i < path.size(); i++)
		{
			int current_size = path[i].size();
			for (int j = 0; j < current_size; j++)
			{
				if (j != current_size - 1)
					std::cout << path[i][j] << "-";
				else
					std::cout << path[i][j] << " Distance: " << result_dist[path[i][j]];
			}
			std::cout << std::endl;
		}
		delete[] result_dist;
		path.clear();
	}
	catch (const char* message)
	{
		std::cout << message;
	}
}