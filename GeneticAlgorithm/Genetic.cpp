#include <iostream>
#include "Genetic.h"

using namespace std;

Genetic::Genetic(Graph graph, int n_N, int n_k, float n_p_c, float n_p_m, int n_time)
{
    N = n_N;
    k = n_k;
    p_c = n_p_c;
    p_m = n_p_m;
    time = n_time;
    foundTime = 0;

    matrix = graph.getMatrix();
    n = graph.getN();
}

int Genetic::apply()
{
    vector<vector<int>> population, nPopulation;
	vector<int> populationFitness;
	vector<int> best_path;
	int best_sum;

	clock_t start;
    start = clock();

    generation_number = 0;
    startPopulation(population);
	best_path = population[0];
	best_sum = sumPath(best_path);
	int p1, p2, psize = n;

	while(!((clock()-start) / CLOCKS_PER_SEC >= time))
	{
        calculateFitness(populationFitness, population);
		nPopulation = tournament(population, populationFitness);

		int populationBestIndex = distance(populationFitness.begin(), min_element(populationFitness.begin(), populationFitness.end()));
		if (populationFitness[populationBestIndex] < best_sum) //-----------------------------------------------------------------------best??
		{
			best_path = population[populationBestIndex];
			best_sum = sumPath(best_path);
			foundTime = (1000 * (clock() - start)) / CLOCKS_PER_SEC;
			// generation = generation_number;
			if(n == 17 && best_sum == 2085) break;
			else if(n == 170 && best_sum < 4132) break;
			else if(n == 323 && best_sum < 1989) break;
		}

		//wymiana pokolen
		clearPopulation(population);
		population = nPopulation;
		clearPopulation(nPopulation);

		orderedCrossover(population);

		for(int i=0;i<N;++i)
        {
            if(rand() % 1000 < 1000 * p_m)
            {
                int index1, index2; //get<0>(indexes), index2 = get<1>(indexes);
                do{
                    index1 = rand() % n;
                    index2 = rand() % n;
                }while(index1 == index2);

                swap(population.at(i)[index1], population.at(i)[index2]);
            }
        }

        generation_number++;

	}

    best_path = fixPath(best_path); //naprawa sciezki
	best_path.push_back(best_path[0]);

	return best_sum;

	//cout << "Jeszcze dziala.";
}

vector<int> Genetic::fixPath(vector<int> path)
{
    while(path[0] != 0)
	{
		path.push_back(path[0]);
        path.erase(path.begin());
	}
	return path;
}

void Genetic::startPopulation(vector<vector<int>>& population)
{
    vector<int> v;
	v.clear();

	for(int i=0;i<n;i++)
    {
        v.push_back(i);
    }
	for(int i=0;i<N;i++)
	{
		random_shuffle(v.begin(), v.end());
		population.push_back(v);
	}
}

void Genetic::clearPopulation(vector<vector<int>>& population)
{
    for(vector<int>& ite : population)
	{
		ite.clear();
	}
	population.clear();
}

void Genetic::calculateFitness(vector<int>& fitness, vector<vector<int>> population)
{
    fitness.clear();
	for(vector<int>& ite : population)
	{
		fitness.push_back(sumPath(ite));
	}
}

vector<vector<int>> Genetic::tournament(vector<vector<int>>& parents, vector<int> fitness)
{
    vector<vector<int>> nextPopulation;
	vector<int> perm;
	int result,index;

	for(int i=0;i<N;++i)
	{
		result = INT32_MAX;
		for(int j=0;j<k;++j)
		{
			index = rand() % N;
			if(fitness[index] < result)
			{
				result = fitness[index];
				perm.clear();
				perm = parents[index];
			}
		}
		nextPopulation.push_back(perm);
	}
	return nextPopulation;
}

/*vector<vector<int>> Genetic::pairTournament(vector<vector<int>>& parents, vector<int> fitness)
{
    vector<vector<int>> nextPopulation;
	int result,index;

	for(int i=0;i<N;++i)
	{
		result = INT32_MAX;
		for(int j=0;j<k;++j)
		{
			tuple<int, int> indexes = getTwoIndexes(N);
			int index_parent1 = get<0>(indexes), index_parent2 = get<1>(indexes);
			if(fitness[index_parent1] < fitness[index_parent2]) nextPopulation.push_back(parents[index_parent1]);
			else nextPopulation.push_back(parents[index_parent2]);
		}
	}
	return nextPopulation;
}*/

int Genetic::sumPath(vector<int> path)
{
    int sum = matrix[path[n-1]][path[0]];

    for(int i=0;i<(n-1);++i)
    {
        sum += matrix[path[i]][path[i+1]];
    }

    return sum;
}

void Genetic::orderedCrossover(vector<vector<int>>& population)
{
    for(int i=0;i<N;++i)
	{
		if(rand()%1000 < 1000*p_c)
		{
			tuple<int, int> indexes = getTwoIndexes(N);
			int index_parent1 = get<0>(indexes), index_parent2 = get<1>(indexes);
			_orderedCrossover(population[index_parent1], population[index_parent2]);
		}
	}
}


tuple<int, int> Genetic::getTwoIndexes(int n)
{
    int index1, index2;
	do
	{
		index1 = rand() % n;
		index2 = rand() % n;
	}while(index1 == index2);      // ----------------------------------------------------------------------------------------------------

	return make_tuple(index1, index2);
}

bool Genetic::isOnPath(vector<int>& path, int p_begin, int p_end, int city)
{
    for(int i=p_begin;i<=p_end;++i)
	{
		if(city == path[i]) return true;
	}
	return false;
}

void Genetic::_orderedCrossover(vector<int>& parent1, vector<int>& parent2)
{
    std::vector<int> tmp1(n), tmp2(n);
	std::vector<int>::iterator ite1, ite2;
	int beginIndex, endIndex;

	do{
		beginIndex = rand() % n;
		endIndex = rand() % n;
	}while((0 >= (endIndex - beginIndex)) || !beginIndex || !(endIndex - (n-1)));

	for(int i = beginIndex; i <= endIndex; i++)
    {
		tmp1[i] = parent1[i];
		tmp2[i] = parent2[i];
	}

	ite1 = tmp1.begin() + endIndex + 1;
	ite2 = parent2.begin() + endIndex + 1;

	while (ite1 != tmp1.begin() + beginIndex)
    {
		if(isOnPath(tmp1, beginIndex, endIndex, *ite2))
		{
			if(ite2 == (parent2.end()-1)) ite2 = parent2.begin();
			else ite2++;
		}
		else
		{
			*ite1 = *ite2;

			if(ite1 == (tmp1.end()-1)) ite1 = tmp1.begin();
			else ite1++;

			if(ite2 == (parent2.end()-1)) ite2 = parent2.begin();
			else ite2++;
		}
	}

	ite1 = tmp2.begin() + endIndex + 1;
	ite2 = parent1.begin() + endIndex + 1;

	while(ite1 != tmp2.begin() + beginIndex)
    {
		if(!(isOnPath(tmp2, beginIndex, endIndex, *ite2)))
		{
			*ite1 = *ite2;

			if(ite1 == (tmp2.end()-1)) ite1 = tmp2.begin();
			else ite1++;

			if(ite2 == (parent1.end()-1)) ite2 = parent1.begin();
			else ite2++;
		}
		else
        {
			if(ite2 == (parent1.end()-1)) ite2 = parent1.begin();
			else ite2++;
		}
	}

	parent1.clear();
	parent2.clear();
	parent1 = tmp1;
	parent2 = tmp2;
}


Genetic::~Genetic()
{
    //dtor
}
