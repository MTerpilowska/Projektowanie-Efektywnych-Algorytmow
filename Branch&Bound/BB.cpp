#include "BB.h"

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

BB::BB(Graph graph)
{
    n = graph.getN();
	matrix = graph.getMatrix();
	upperBound = MAX;
	lowerBound = 0;
	edges = new int[n];
	visited = new bool[n];
	int minimum = MAX;

	// obliczanie dolnej granicy warto�ci �cie�ki
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(matrix[i][j] < minimum)
				minimum = matrix[i][j];
		}
		edges[i] = minimum;
		lowerBound += minimum;
		minimum = MAX;
		visited[i] = false;
	}
}

BB::~BB()
{
    //dtor
}

string BB::toString()
{
	string bandb = to_string(upperBound) + "; " + path.toString() + "0"+ "\n";
	return bandb;
}

void BB::apply()
{
	Node start;
	start.vertex = 0;
	start.lowerrBound = lowerBound;
	recursion(start);
}

void BB::recursion(Node node)
{
	tempPath.push(node.vertex);
	visited[node.vertex] = true;

	// kolejka priorytetowa
	priority_queue <Node, std::vector<Node>, std::greater<Node>> nodes;

    Node tempNode;
	for(int i=0;i<n;i++)
	{
		if(!visited[i])
		{
			tempNode.vertex = i;
			tempNode.lowerrBound = calcLowerBound(node, i);
			nodes.push(tempNode);
		}
	}

	// czy to ju� ostatni wierzcho�ek
	if(nodes.empty())
	{
	    // je�li warto�� �cie�ki dalej mie�ci si� w przedziale
		if(calcLowerBound(node, 0) < upperBound)
		{
			upperBound = calcLowerBound(node, 0);
			tempPath.ccopy(&path);
		}
	}
	else
	{
		while(!nodes.empty())
		{
		    // usuwamy wierzcho�ek z kolejki do sprawdzenia
			tempNode = nodes.top();
			nodes.pop();
			// je�li docieraj�c do tego wierzcho�ka jeste�my na minimalnej dotychczas �cie�ce, to idziemy wg��b rekurencj�
			if(tempNode.lowerrBound < upperBound)
			{
				recursion(tempNode);
			}
			else
				break; // je�li warto�� dolnego ograniczenia wierzcho�ka jest wy�sza ni� og�lne g�rne ograniczenie to porzucamy to rozwi�zanie
		}
	}
	tempPath.pop();
	visited[node.vertex] = false;
}

int BB::calcLowerBound(Node node, int next)
{
	return node.lowerrBound - edges[node.vertex] + matrix[node.vertex][next]; // dolne oszacowanie nast�pnika wierzcho�ka to (dolne oszacowanie wierzcho�ka - minimalna warto�� �cie�ki z danego wierzcho�a + warto�� �cie�ki od wierzcho�ka do jego nast�pnika)
}

bool operator > (const Node &arg1, const Node &arg2)
{
	if (arg1.lowerrBound > arg2.lowerrBound)
		return true;
	else
		return false;
}

