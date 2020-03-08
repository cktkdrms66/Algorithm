#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class Edge
{
public:
	int node[2];
	int cost;
	Edge(int node1, int node2, int cost)
	{
		this->node[0] = node1;
		this->node[1] = node2;
		this->cost = cost;
	}
	bool operator <(Edge &edge)
	{
		return this->cost < edge.cost;
	}

};


int get_parent(int* parent, int node)
{
	if ( parent[node] == node ) return node;
	else get_parent(parent, parent[node]);
};

void parent_merge(int* parent, int node1, int node2)
{
	int i, j;
	i = get_parent(parent, node1);
	j = get_parent(parent, node2);

	if ( i < j )
	{
		parent[j] = i;
	}
	else
	{
		parent[i] = j;
	}
};

int check_cycle(int* parent, int i, int j)
{
	if ( get_parent(parent, i) == get_parent(parent, j) )
	{
		return 1;
	}

	return 0;
};


int main()
{
	string input;
	int node_num, edge_num, i, node1, node2, cost, j;
	int sum;


	while ( getline(cin, input) )
	{

		vector<Edge> v;
		sum = 0;
		string str_node;
		string str_edge;
		if ( input.size() == 0)
		{
			break;
		}
		if ( input[0] == ' ' || input[input.size() - 1] == ' ' ) break;

		for ( i = 0; i < input.size(); i++ )
		{

			if ( input[i] == ' ' ) break;
			str_node += input[i];
		}

		int error = 0;
		for ( j = i + 1; j < input.size(); j++ )
		{
			if ( input[j] == ' ' ) error = 1;
			str_edge += input[j];
		}
		if ( error == 1 )break;
		node_num = atoi(str_node.c_str());
		edge_num = atoi(str_edge.c_str());
		

		for ( i = 0; i < edge_num; i++ )
		{
			cin >> node1 >> node2 >> cost;
			for ( j = 0; j < v.size(); j++ )
			{
				if ( v[j].node[0] == node1)
				{
					if ( v[j].node[1] == node2 )
					{
						if ( cost < v[j].cost )
						{
							v[j].cost = cost;
						}
					}
				}
				if ( v[j].node[1] == node1 )
				{
					if ( v[j].node[0] == node2 )
					{
						if ( cost < v[j].cost )
						{
							v[j].cost = cost;
						}
					}
				}

			}
			v.push_back(Edge(node1, node2, cost));
		}

		sort(v.begin(), v.end());

		int* parent = new int[node_num +1];
		for ( i = 0; i < node_num + 1; i++ )
		{
			parent[i] = i;
		}
		for ( i = 0; i < edge_num; i++ )
		{
			if ( check_cycle(parent, v[i].node[0], v[i].node[1]) == 0 )
			{
				sum += v[i].cost;
				parent_merge(parent, v[i].node[0], v[i].node[1]);
			}
		}

		cout << sum << endl;
		getchar();
		input = "";

	}


	return 0;
}

