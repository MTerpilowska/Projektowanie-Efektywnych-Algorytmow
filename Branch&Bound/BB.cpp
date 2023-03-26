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

	// obliczanie dolnej granicy wartoœci œcie¿ki
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

	// czy to ju¿ ostatni wierzcho³ek
	if(nodes.empty())
	{
	    // jeœli wartoœæ œcie¿ki dalej mieœci siê w przedziale
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
		    // usuwamy wierzcho³ek z kolejki do sprawdzenia
			tempNode = nodes.top();
			nodes.pop();
			// jeœli docieraj¹c do tego wierzcho³ka jesteœmy na minimalnej dotychczas œcie¿ce, to idziemy wg³¹b rekurencj¹
			if(tempNode.lowerrBound < upperBound)
			{
				recursion(tempNode);
			}
			else
				break; // jeœli wartoœæ dolnego ograniczenia wierzcho³ka jest wy¿sza ni¿ ogólne górne ograniczenie to porzucamy to rozwi¹zanie
		}
	}
	tempPath.pop();
	visited[node.vertex] = false;
}

int BB::calcLowerBound(Node node, int next)
{
	return node.lowerrBound - edges[node.vertex] + matrix[node.vertex][next]; // dolne oszacowanie nastêpnika wierzcho³ka to (dolne oszacowanie wierzcho³ka - minimalna wartoœæ œcie¿ki z danego wierzcho³a + wartoœæ œcie¿ki od wierzcho³ka do jego nastêpnika)
}

bool operator > (const Node &arg1, const Node &arg2)
{
	if (arg1.lowerrBound > arg2.lowerrBound)
		return true;
	else
		return false;
}

