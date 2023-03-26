#ifndef GENETIC_H
#define GENETIC_H

#include "Graph.h"
#include<vector>
#include <random>
#include <ctime>
#include <time.h>
#include <algorithm>
#include <tuple>

using namespace std;

class Genetic
{
    private:
        int n; // liczba miast
        int** matrix = nullptr; // graf miast
        int generation_number;

        void startPopulation(vector<vector<int>>& population);
        vector<int> fixPath(vector<int> path);
        void clearPopulation(vector<vector<int>>& population);
        void calculateFitness(vector<int>& fitness, vector<vector<int>> population);
        vector<vector<int>> tournament(vector<vector<int>>& parents, vector<int> fitness);
        //vector<vector<int>> pairTournament(vector<vector<int>>& parents, vector<int> fitness);
        int sumPath(vector<int> path);
        void orderedCrossover(vector<vector<int>>& population);
        tuple<int, int> getTwoIndexes(int n);
        void _orderedCrossover(vector<int>& parent1, vector<int>& parent2);
        bool isOnPath(vector<int>& path, int p_begin, int p_end, int city);


    public:
        float p_c; // prawdopodobieñstwo krzy¿owania
        float p_m; // prawdopodobieñstwo mutacji
        int N; // wielkoœæ populacji
        int k; // liczba osobników wybrana w selekcji turniejowej
        int time; // czas dzia³ania
        int foundTime; // w milisekundach

        int apply();
        Genetic(Graph graph, int n_N, int n_k, float n_p_c, float n_p_m, int n_time);
        virtual ~Genetic();

};

#endif // GENETIC_H
