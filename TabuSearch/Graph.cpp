#include "Graph.h"
#include <fstream>
#include <time.h>


bool Graph::readFromFile(string file)
{
	ifstream fin;
	fin.open(file);

	if(fin.fail() || fin.eof())
	{
		return false;
	}

	if(n)
	{
		for(int i=0;i<n;i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	fin >> n;
	int **temp;
	temp = new int *[n];

	for(int i=0;i<n;i++)
	{
		temp[i] = new int[n];
	}

	for(int i=0;i<n;i++)
	{
		for (int j = 0; j < n; j++)
		{
			fin >> temp[i][j];
		}
	}

	fin.close();
	matrix = temp;
	return true;
}


bool Graph::putMaxToGraph() // upewnienie się że na przekątnej grafu są wartości za pomocą ktorych można ją odróżnić
{
	if(!n)
		return false;
	else
	{
		for(int i=0;i<n;i++)
		{
			matrix[i][i] = MAX;
		}
		return true;
	}
}

int Graph::getN()
{
	return n;
}

int** Graph::getMatrix()
{
	return matrix;
}

Graph::Graph()
{

}

Graph::~Graph()
{

}
