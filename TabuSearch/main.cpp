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

#include "TabuSearch.h"
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
        ofstream fout;
        fout.open ("tsp_test_out-zajecia-poprawa.csv");
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

                    //fout << "time: " << time;
                    for(int i=0;i<reps;i++)
                    {
                        TabuSearch ts(graph);
                        int best_result = ts.apply();
                        fout << best_result << ";\n";
                    }

                }
            }

        }
        fout.close();
    }



    return 0;
}
