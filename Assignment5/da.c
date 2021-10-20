#include <stdio.h>
#include "List.h"
#include "graph.h"
#include <stdlib.h>

/* TODO: implement the deferred acceptance/Gale-Shapley algorithm
- Note that we want to find the M-optimal set of stable matches
- You can write your own helper functions	
*/

int isMatch(graph g, int i)
{
	for (int j = 0; j < g->n; j++)
	{
		if (hasEdge(g, i, j))
		{
			return 1;
		}
	}
	return 0;
}

int isMatchW(graph g, int w)
{
	for (int j = 0; j < g->n; j++)
	{
		if (hasEdge(g, j, w))
		{
			return 1;
		}
	}
	return 0;
}

int prefers(int w, int m, int other, int size, int **prefW)
{
	for (int i = 0; i < size; i++)
	{
		int current = prefW[w - size][i];
		if (current == m)
		{
			return 1;
		}
		else if (current == other)
		{
			return 0;
		}
	}
	printf("Prefered messed up!\n");
	return -1;
}

int isStable(graph g)
{
	int size = g->n / 2;
	for (int i = 0; i < size; i++)
	{
		if (!isMatch(g, i))
		{
			return 0;
		}
	}
	return 1;
}

int findStableSets(graph g, int **prefW, int **prefM)
{
	//- for every m ∈ M that is not yet matched, propose to w ∈ W that have not yet proposed to
	//-if w is not yet matched (that is there is no (m, w) edge in the graph),
	//add the edge (m, w) in the graph
	//- otherwise, find w's current match (find edge (m', w) in the graph) and see if w prefers m to m'
	//- if w prefers m to m', remove the edge (m', w) and add edge (m, w)
	int size = g->n / 2;
	int choiceNum[size];
	for (int i = 0; i < size; i++)
	{
		choiceNum[i] = 0;
	}
	int m = 0;
	while (!isStable(g))
	{
		// printf("m, %d ",m);
		//printGraph(g);
		if (!isMatch(g, m))
		{
			int w = prefM[m][choiceNum[m]];
			if (!isMatchW(g, w))
			{
				addEdge(g, m, w);
			}
			else
			{
				int other;
				for (other = 0; other < g->n; other++)
				{
					if (g->matrix[other][w])
					{
						break;
					}
				}
				if (prefers(w, m, other, size, prefW))
				{
					removeEdge(g, other, w);
					addEdge(g, m, w);
					choiceNum[other] += 1;
					if (choiceNum[other] >= size)
					{
						return 0;
					}
				}
				else
				{
					choiceNum[m] += 1;
					if (choiceNum[m] >= size)
					{
						return 0;
					}
				}
			}
		}
		m++;
		if (m >= size)
		{
			m -= size;
		}
	}
	return 1;
}

/* TODO: implement the main() function
Here, you would read in the input (from stdin) and execute deferred acceptance algorithm
and print out the set of M-optimal stable matches.
*/
int main(void)
{

	int n;
	fscanf(stdin, "%d", &n);
	graph g = createGraph(n);

	int **prefW = (int **)malloc(n / 2 * sizeof(int *));
	int **prefM = (int **)malloc(n / 2 * sizeof(int *));
	for (int i = 0; i < n / 2; i++)
	{
		prefM[i] = (int *)malloc(n / 2 * sizeof(int));
		for (int j = 0; j < n / 2; j++)
		{
			fscanf(stdin, "%d", &prefM[i][j]);
		}
	}
	for (int i = 0; i < n / 2; i++)
	{
		prefW[i] = (int *)malloc(n / 2 * sizeof(int));
		for (int j = 0; j < n / 2; j++)
		{
			fscanf(stdin, "%d", &prefW[i][j]);
		}
	}

	int returnedVal = findStableSets(g, prefW, prefM);
	if (returnedVal > 0)
	{
		printf("M-Optimal matches are: ");
		printGraph(g);
	}

	destructGraph(g);
	for (int i = 0; i < n / 2; i++)
	{
		free(prefM[i]);
		free(prefW[i]);
	}
	free(prefM);
	free(prefW);

	return 0;
}