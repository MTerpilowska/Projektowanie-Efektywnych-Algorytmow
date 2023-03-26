#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <windows.h>

#include "BB.h"

using namespace std;

//--------------------------------- POMIAR CZASU -------------------------
long long int read_QPC()
{
LARGE_INTEGER count;
DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
QueryPerformanceCounter(&count);
SetThreadAffinityMask(GetCurrentThread(), oldmask);
return((long long int)count.QuadPart);
}
//-------------------------------------------------------------------------



int main()
{
    // do pomiaru czasu:
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,1000000);

    ifstream fin;
	fin.open("INI.txt");

	if(fin.fail() || fin.eof())
	{
		cout << "Blad odczytu\n";
	}
	else
    {
        ofstream fout;
        fout.open ("tsp_test_out.csv");
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

                    graph.putMaxToGraph();

                    // Branch and Bound: depth search
                    BB bbTest(graph);
                    bbTest.apply();

                    fout << path << "; " << bbTest.toString() << ";";

                    for(int i=0;i<reps;i++)
                    {
                        start = read_QPC();
                        // Branch and Bound: depth search
                        BB bb(graph);
                        bb.apply();
                        elapsed = read_QPC() - start;
                        fout << (1000.0 * elapsed) / frequency << endl << ";";
                    }

                }
            }

        }
        fout.close();
    }

    return 0;
}

