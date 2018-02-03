
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "showworld.h"
#include "functions.h"


typedef enum {
    ldown=49, down=50, rdown=51,
    left=52, pass=53, right=54,
    lup=55, up=56, rup=57
} BOARD;


unsigned int movement( 
   AGENT **agent_grid,
   unsigned short *agent_list,
   unsigned short max_id,
   unsigned short round,
    unsigned int WORLD_X, unsigned int WORLD_Y);
 
int a_int ( unsigned int key);

void free_agent_grid(unsigned int X, AGENT** agent_grid);

AGENT **create_agent_grid ( unsigned int X,
		 					unsigned int Y, 
							AGENT **agent_grid);




#endif
