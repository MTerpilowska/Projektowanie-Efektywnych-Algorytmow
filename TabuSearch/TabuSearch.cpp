#include <time.h>
#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <iterator>
#include <vector>

#include "TabuSearch.h"
#include "Graph.h"

using namespace std;


TabuSearch::TabuSearch(Graph graph)
{
    matrix = graph.getMatrix();
    n = graph.getN();
}

int TabuSearch::apply()
{
    vector<vector<int>> tabu_matrix;
    vector<int> permutation = chosenPermutation(n);
    vector<int> nextpermutation(permutation);

    int best = INT32_MAX;
    vector<int> best_path;
    int first; //do zamiany miast miejscami
    int second; // do zamiany miast miejscami
    int sum_of_next;

    tabu_matrix.resize(n);

    for(int i=0;i<n;i++)
    {
        tabu_matrix[i].resize(n,0);
    }

    //do pomiaru czasu :
    clock_t start;
    double time;
	double foundTime;
    start = clock();

    for (int s=0;s<(n*n);++s)
    {
        first = 0;
        second = 0;
        sum_of_next = INT32_MAX;

        for(int j=0;j<n;++j)
        {
            for(int k=j+1;k<n;++k)
                {
                    swap(permutation[j], permutation[k]);
                    int temp_sum = sumPath(permutation);

                    if(temp_sum < best)
                    {
                        best = temp_sum;
                        best_path = permutation;

                        foundTime = (1000*(clock() - start)) /CLOCKS_PER_SEC; //czas znalezienia najlepszego rozw
                    }

                    if(temp_sum < sum_of_next)
                    {
                        if(tabu_matrix[k][j] < s)
                        {
                            sum_of_next = temp_sum;
                            nextpermutation = permutation;
                            first = k;
                            second = j;
                        }
                    }
                    else swap(permutation[j], permutation[k]);
                    foundTime = (1000*(clock() - start)) /CLOCKS_PER_SEC;
                    //swap(permutation[j], permutation[k]);
                }
        }
        permutation = nextpermutation;
        tabu_matrix[first][second] += 5000;
    }

    //tabu_matrix.clear();

    /*cout << "tabu:\n";

    for(int i=0;i<n;i++)
    {
        for(int z=0;z<n;z++)
        {
            cout << tabu_matrix[i][z];
        }
        cout << "\n";
    }*/

    best_path.push_back(best_path[0]);
    /*cout << "\nNajlepsza droga: " << best << " [";
    for(int w=0;w<n;w++)
    {
        cout << best_path[w] << " ";
    }*/
    foundTime = (1000*(clock() - start)) /CLOCKS_PER_SEC;
    cout << foundTime << ";\n";


    return best;
}

vector<int> TabuSearch::chosenPermutation(int n)
{
    vector<int> v;
    v.reserve(n);

    //random_device rd;
    //mt19937 g(rd());

    for(int i=0;i<n;i++)
    {
        v.push_back(i);
    }
    random_shuffle(v.begin(), v.end());

    return v;
}

int TabuSearch::sumPath(vector<int> path)
{
    int sum = matrix[path[n-1]][path[0]];

    for(int i=0;i<(n-1);++i)
    {
        sum += matrix[path[i]][path[i+1]];
    }

    return sum;
}

TabuSearch::~TabuSearch()
{
    //dtor
}
