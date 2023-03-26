#ifndef BB_H
#define BB_H

#include "Graph.h"
#include "MyStack.h"
#define MAX 9999 // Jako nieskoñczonoœæ w algorytmie - aby mo¿na by³o porównaæ z wartoœci¹ œcie¿ki czy jest minimalna

// Branch and Bound: depth search

struct Node // wêze³ - miasto
{
	int lowerrBound; //dolna granica wartoœci œcie¿ki
	int vertex; //numer miasta
};

class BB
{
    public:
        BB(Graph graph);
        virtual ~BB();
        string toString();
        void apply();
        void recursion(Node node);
        int calcLowerBound(Node node, int next);

    protected:

    private:
        int **matrix;
        int n;
        int upperBound; //górna granica wartoœci œcie¿ki
        int lowerBound; //dolna granica wartoœci œcie¿ki
        bool *visited; //odwiedzone miasta
        int *edges; // wartoœci minimalne krawêdzi w danym wierszu grafu - indeks to wierzcho³ek z którego wychodzi krawêdŸ
        MyStack path;
        MyStack tempPath;
};

#endif // BB_H

