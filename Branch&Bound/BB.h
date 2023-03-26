#ifndef BB_H
#define BB_H

#include "Graph.h"
#include "MyStack.h"
#define MAX 9999 // Jako niesko�czono�� w algorytmie - aby mo�na by�o por�wna� z warto�ci� �cie�ki czy jest minimalna

// Branch and Bound: depth search

struct Node // w�ze� - miasto
{
	int lowerrBound; //dolna granica warto�ci �cie�ki
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
        int upperBound; //g�rna granica warto�ci �cie�ki
        int lowerBound; //dolna granica warto�ci �cie�ki
        bool *visited; //odwiedzone miasta
        int *edges; // warto�ci minimalne kraw�dzi w danym wierszu grafu - indeks to wierzcho�ek z kt�rego wychodzi kraw�d�
        MyStack path;
        MyStack tempPath;
};

#endif // BB_H

