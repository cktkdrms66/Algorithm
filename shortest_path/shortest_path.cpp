#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

int find_min(int** graph, int* start_to_node, int* visit, int size)
{
	int i, j,min, min_index;
	
	min = numeric_limits<int>::max();
	for ( i = 0; i < size; i++ )
	{
		if ( start_to_node[i] < min && visit[i] == 0 )
		{
			
			min_index = i;
			min = start_to_node[i];
		}
	}
	return min_index;
}

int main()
{
	string input;
	int node_num, edge_num, i, node1, node2, cost, j;
	int sum;


	while ( getline(cin, input) )
	{
		int** graph;
		sum = 0;
		string str_node;
		string str_edge;
		
		//error checking
		if ( input.size() == 0 )
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


		//graph init
		graph = new int*[node_num];
		
		for ( i = 0; i < node_num; i++ )
		{
			graph[i] = new int[node_num];
			for ( j = 0; j < node_num; j++ )
			{
				if ( i == j ) graph[i][j] = 0;
				else graph[i][j] = numeric_limits<int>::max();
			}
		}

		//input
		for ( i = 0; i < edge_num; i++ )
		{
			int tmp;
			cin >> node1 >> node2 >> cost;
			if(node1 > node2)
			{
				tmp = node1;
				node1 = node2;
				node2 = tmp;
			}
			if ( cost < graph[node1 - 1][node2 - 1] )
			{
				graph[node1 - 1][node2 - 1] = cost;
			}
			
		}

		//start and visit init
		int* start_to_node = new int[node_num];
		int* visit = new int[node_num];
		for ( i = 0; i < node_num; i++ )
		{
			if ( i == 0 )
			{
				start_to_node[i] = 0;
			}
			else start_to_node[i] = numeric_limits<int>::max();
			visit[i] = 0;
			
		}


		//dj start
		int node;
		for ( i = 0; i < node_num; i++ )
		{
			node = find_min(graph, start_to_node, visit, node_num);
			for ( j = 0; j < node_num; j++ )
			{
				int path;
				if ( graph[0][node] == numeric_limits<int>::max() || graph[node][j] == numeric_limits<int>::max() )
					path = numeric_limits<int>::max();
				else path = start_to_node[node] + graph[node][j];
				if ( path < start_to_node[j] )
				{
					start_to_node[j] = path;
				}
					
			}
			visit[node] = 1;

		}

		cout << start_to_node[node_num - 1] << endl;
		getchar();
		input = "";

	}


	return 0;
}

