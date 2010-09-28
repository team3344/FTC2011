/*
 *  main.c
 *  Dijkstra
 *
 *  Created by Justin Buchanan on 9/26/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

#include "main.h"


#define kNodeCount 5
#define kUnvisited -1
#define kInfinity 100000



int costs[kNodeCount][kNodeCount] = {
	{0, kInfinity, kInfinity, 3, kInfinity},
	{kInfinity, 1, 2, kInfinity, 4},
	{kInfinity, 1, kInfinity, 1, kInfinity},
	{kInfinity, 1, 2, 3, kInfinity},
	{kInfinity, 1, 2, 1, kInfinity}
};





/*
int costs[kNodeCount][kNodeCount] = {
	{0, 1, kInfinity},
	{1, kInfinity, 2},
	{kInfinity, 2, 0}
};*/


int tentativeCosts[kNodeCount];
int previous[kNodeCount];
int traveled[kNodeCount];


void init()
{
	for ( int i = 0; i < kNodeCount; i++ )
	{
		previous[i] = kUnvisited;
		tentativeCosts[i] = kInfinity;
		traveled[i] = 0;
		costs[i][i] = 0;
	}
}



void print()
{
	printf("\n");
	for ( int i = 0; i < kNodeCount; i++ )
	{
		for ( int j = 0; j < kNodeCount; j++ )
		{
			printf("\t%d,", costs[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}



void evaluate_node(int node)
{
	//printf("\n***evaluating %d***\n", node);
	traveled[node] = 1;
	for ( int i = 0; i < kNodeCount; i++ )
	{
		//printf("\nlooping in evaluate_node i= %d\n", i);
		int totalCost = costs[node][i] + tentativeCosts[node];
		
		if ( totalCost < tentativeCosts[i] )
		{
			//printf("\nshorter path found from %d to %d w/cost %d\n", node, i, totalCost);
			tentativeCosts[i] = totalCost;
			previous[i] = node;
		}
	}
	
	for ( int i = 0; i < kNodeCount; i++ )
	{
		//printf("\nchecking for travel to %d from %d\n", i, node);
		if ( costs[node][i] != kInfinity && traveled[i] == 0 ) evaluate_node(i);
	}
	
}


void shortest_path(int start, int finish)
{
	tentativeCosts[start] = 0;
	evaluate_node(start);
	
	
	
	int path[kNodeCount];
	for ( int i = 0; i < kNodeCount; i++ ) { path[i] = 0; }	//	set 'em all to zero
	
	
	int i = kNodeCount - 1;
	int node = finish;
	while ( node != start )
	{
		node = previous[node];
		path[i] = node;
		
		i--;
	}
	
	printf("\nshortest path from %d to %d = ", start, finish);
	for ( i++; i < kNodeCount; i++ )
	{
		printf("%d-->", path[i]);
	}
	printf("%d", finish);
	
	printf(" with a cost of %d\n", tentativeCosts[finish]);
	
	
	
}









int main_dijkstra()
{
	init();
	print();
	
	
	shortest_path(0, kNodeCount - 1);
	
	
	
	
	
	
	return 0;
}

