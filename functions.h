
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "showworld.h"
#include "functions.h"

typedef enum {
    ldown=1, down=2, rdown=3,
    left=4, pass=5, right=6,
    lup=7, up=8, rup=9
} BOARD;


void movement( 
   AGENT **agent_grid,
   unsigned int *agent_list,
   unsigned int max_id, 
   unsigned int turns);

void free_agent_grid(unsigned int WORLD_X, AGENT** agent_grid);
AGENT **create_agent_grid ( unsigned int X,
							unsigned int Y, 
							AGENT **agent_grid);

#endif