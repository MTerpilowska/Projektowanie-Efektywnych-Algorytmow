#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "Genetic.h"
#include "Graph.h"

using namespace std;

int main()
{
    srand(time(NULL));

    ifstream fin;
	fin.open("INI.txt");

	if(fin.fail() || fin.eof())
	{
		cout << "Blad odczytu\n";
	}
	else
    {
        int time, N, k;
        float p_c, p_m;
        fin >> time >> N >> k >> p_c >> p_m;
        ofstream fout;
        fout.open ("tsp_test_out_zajecia.csv");
        fout << "TEST DLA N: " << N << ", k: " << k << ", p_c: " << p_c << ", p_m: " << p_m << " i czasu: " << time << "ms;\n";
        string line;
        while(getline(fin, line))
        {
            string path;
            int reps;
            stringstream line_stream(line);
            if (line_stream >> path >> reps)
            {

                Graph graph;

                if(!graph.readFromFile(path))
                {
                    cout << "Blad odczytu\n";
                }

                if(!graph.getN())
                {
                    cout << "Niepoprawny plik\n";
                }
                else
                {
                    fout << path << ";\n";
                    cout << path << "\n";

                    graph.putMaxToGraph();

                    for(int i=0;i<reps;i++)
                    {
                        Genetic ag(graph, N, k, p_c, p_m, time);
                        int result = ag.apply();
                        //cout << result << ", " << ag.foundTime << "\n";
                        fout << result << "; " << ag.foundTime << "\n";
                    }

                }
            }

        }
        fout.close();
    }



    return 0;
}
