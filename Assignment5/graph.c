#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "graph.h"

/* TODO: implement graph constructor
Instantiate a graph given the number of vertices
There are no edges at instantiation
*/
graph createGraph(int num)
{

    graph g = (graphObj *)malloc(sizeof(graphObj));
    g->n = num;
    g->matrix = (int**)malloc(num*sizeof(int*));
    for (int i = 0; i < g->n; i++)
    {
        g->matrix[i] = (int*)malloc(num*sizeof(int));
        for (int j = 0; j < g->n; j++)
        {
            g->matrix[i][j] = 0;
        }
    }
    return g;
}

/* TODO: implement graph destructor
destruct graph and free allocated memory as appropriate
*/
void destructGraph(graph g)
{

    for (int i = 0; i < g->n; i++)
    {
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g);
}

// TODO: implement addEdge function
void addEdge(graph g, int i, int j)
{
    g->matrix[i][j] = 1;
}

// TODO: implement removeEdge function
void removeEdge(graph g, int i, int j)
{
    g->matrix[i][j] = 0;
}

// TODO: implement hasEdge function
int hasEdge(graph g, int i, int j)
{
    if (g->matrix[i][j] == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// TODO: implement outEdges function
void outEdges(graph g, int i, node **list)
{

    for (int j = 0; j < g->n; j++)
    {
        if (g->matrix[i][j] == 1)
        {
            node* npm = (node*)malloc(sizeof (node));
            npm ->value = j; 
            insertList(list, npm);
        }
    }
}

// TODO: implement inEdges function
// takes in an empty list and adds to it all incoming edges into vertex j
void inEdges(graph g, int j, node **list)
{
     for (int i = 0; i < g->n; i++)
    {
        if (g->matrix[i][j] == 1)
        {
            node* npm = (node*)malloc(sizeof (node));
            npm ->value = i; 
            insertList(list, npm);
        }
    }
}

// TODO: implement getNumVer
int getNumVer(graph g)
{
    return g->n;
}

// TODO: implement printGraph
void printGraph(graph g)
{
    for (int i = 0; i < g->n; i++)
    {
        for (int j = 0; j < g->n; j++)
        {
            if (g->matrix[i][j] == 1)
            {
                printf("(%d, %d) ", i, j);
            }   
        }
    }
    printf("\n");
}
