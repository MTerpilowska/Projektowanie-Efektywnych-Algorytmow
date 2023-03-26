#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#define MAX 99999 // Jako nieskoñczonoœæ w algorytmie - aby mo¿na by³o porównaæ z wartoœci¹ œcie¿ki czy jest minimalna

using namespace std;

// W³asny graf

class Graph
{
    public:
        int **matrix = nullptr; // graf z wartoœciami dróg miêdzy miastami
        bool readFromFile(string file);
        bool putMaxToGraph(); // upewnienie siê ¿e na przek¹tnej grafu s¹ wartoœci za pomoc¹ ktorych mo¿na j¹ odró¿niæ
        int getN();
        int** getMatrix();
        Graph();
        virtual ~Graph();

    protected:

    private:
        int n = 0; // liczba miast

};

#endif // GRAPH_H
