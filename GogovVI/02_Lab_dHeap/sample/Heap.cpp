#include <iostream>
#include "../include/THeap.h"
#include "time.h"

int main()
{
	srand((unsigned int)time(0));
	int size = 5 + rand() % 10;
	float* elements = new float[size];
	std::cout << "Elements: ";
	for (int i = 0; i < size; i++)
	{
		elements[i] = 1 + rand() / (RAND_MAX / (100 - 1));
		std::cout << elements[i] << "|";
	}
	THeap<float> heapElements;
	std::cout << std::endl;
	try
	{
		heapElements = THeap<float>(elements, size);
		std::cout << "Heap: ";
		heapElements.Output();
		std::cout << "Heap sort: ";
		heapElements.sort();
		heapElements.Output();
	}
	catch (const char* message)
	{
		std::cout << message;
	}
}