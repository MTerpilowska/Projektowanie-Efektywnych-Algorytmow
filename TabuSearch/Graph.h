#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#define MAX 99999 // Jako nieskończoność w algorytmie - aby można było porównać z wartością ścieżki czy jest minimalna

using namespace std;

// Własny graf

class Graph
{
    public:
        int **matrix = nullptr; // graf z wartościami dróg między miastami
        bool readFromFile(string file);
        bool putMaxToGraph(); // upewnienie się że na przekątnej grafu są wartości za pomocą ktorych można ją odróżnić
        int getN();
        int** getMatrix();
        Graph();
        virtual ~Graph();

    protected:

    private:
        int n = 0; // liczba miast

};

#endif // GRAPH_H
