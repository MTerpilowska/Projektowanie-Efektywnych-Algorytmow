#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#define MAX 99999 // Jako niesko�czono�� w algorytmie - aby mo�na by�o por�wna� z warto�ci� �cie�ki czy jest minimalna

using namespace std;

// W�asny graf

class Graph
{
    public:
        int **matrix = nullptr; // graf z warto�ciami dr�g mi�dzy miastami
        bool readFromFile(string file);
        bool putMaxToGraph(); // upewnienie si� �e na przek�tnej grafu s� warto�ci za pomoc� ktorych mo�na j� odr�ni�
        int getN();
        int** getMatrix();
        Graph();
        virtual ~Graph();

    protected:

    private:
        int n = 0; // liczba miast

};

#endif // GRAPH_H
