#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include "Graph.h"
#include<vector>

class TabuSearch
{
	private:

		int** matrix = nullptr;
		int n = 0;

		vector<int> chosenPermutation(int n);
		int sumPath(vector<int> path);

	public:

		int apply();
		TabuSearch(Graph graph);
		~TabuSearch();

};

#endif // TABUSEARCH_H
