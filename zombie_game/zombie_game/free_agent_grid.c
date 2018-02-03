#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


void free_agent_grid(unsigned int X, AGENT **agent_grid){


	for (unsigned int i=0; i<X; i++)
	{
		free(agent_grid[i]);
	}
	free(agent_grid);
}

AGENT **create_agent_grid(unsigned int X ,unsigned int  Y, AGENT** agent_grid) 
{
/* A bi-dimensional array of agents, representing agents in a grid. */
 	agent_grid = malloc (Y * sizeof (AGENT *));

	for (unsigned int i = 0; i < X; ++i)
	{
      	agent_grid[i] = calloc (X , sizeof (AGENT));
 	}
 	
 	return(agent_grid);
 }	
