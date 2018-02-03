/* programa feito por:
Cristina Pietra nº a21701350
Pedro Siqueira nº a21705187
Sara nº a21705494
*/
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 #include "functions.h"
 #include "showworld.h"
 
   /** Horizontal world size. */
  unsigned int WORLD_X = 15;
 
  /** Vertical world size. */
  unsigned int WORLD_Y = 15;
 
 /* This function is an implementation of the definition provided by the
  * ::get_agent_info_at() function pointer. It only works for AGENT and WORLD
  * example structures defined in this file. */
 unsigned int example_get_ag_info(void *world, unsigned int x, unsigned int y);
 
 /**
  * This `main` function is only an example of: a) how to use the API defined in
  * the showworld.h header (mandatory for the project); and, b) how to use the
  * concrete simple implementation of the API (provided in the
  * showworld_simple.c file).
  *
  * @return Always zero.
  * */
 int main() {
 
 
 
 
        /* Number of agents created so far. */
     unsigned short nagents = 0;
     unsigned int turn = 0, max_turn=0, round=0;
     unsigned int a = 0; //aux var
     unsigned int existe_human =0;
 
 
     system("clear");
     system("clear");
     printf("Defina o tamanho do mundo (exemplo: 20 --> mundo 20x20):  ");
     scanf(" %u", &WORLD_X);
     getchar();
     printf("Defina a quantidade de turnos:  ");
     scanf(" %u", &max_turn);
     getchar();
 
     WORLD_Y = WORLD_X;
 
 
     /* An instance of a WORLD structure. */
     WORLD my_world;
 
     /* An instance of a SHOWWORLD world display. */
     SHOWWORLD *sw = NULL;
 
    //Agent grid of the world
     AGENT **agent_grid = NULL;
     agent_grid = create_agent_grid(WORLD_X,WORLD_Y, agent_grid);
 
 
 /**
     * An array of all  possible ID numbers in the main grid. Used for generate the random 
     * order of movement per turn of all agents without repetitions     
     **/ 
     unsigned short *agents_list= NULL;
 
     agents_list = (unsigned short*) calloc (WORLD_X*WORLD_Y,sizeof(unsigned short));
 
 
 
     /* Initialize world display. */
     sw = showworld_new(WORLD_X, WORLD_Y, example_get_ag_info);
 
     /* Initialize random number generator. */
     srand(time(NULL));
 
     /* **************************************************************** */
     /* Cycle through all cells in grid and randomly place agents in it. */
     /* **************************************************************** */
     for (unsigned int i = 0; i < WORLD_Y; ++i) {
         for (unsigned int j = 0; j < WORLD_X; ++j) {
 
             /* Possible agent in grid. By default we assume there is none. */
             AGENT ag = {None, 0, 0};
 
            /* Obtain a probability between 0 and 99. */
            unsigned int probability = (rand() % 100);
 
            /* There is 10% probability of creating an agent. */
            if (probability < 10) {
                
                /* If we got here, an agent will be placed at (i,j). */
 
                /* Randomly define agent type. */
                ag.type = (rand() % 2 == 0) ? Human : Zombie;
 
                /* Give 10% probablity of agent being playable by user. */
                ag.playable = (rand() % 10 == 0);
                 
 
                /* Assign agent ID and then increment number of agents so
                   far. */
                ag.id = nagents;
       
                agents_list[a]= nagents;                a++;
                nagents++;
                /* Assign possible agent to grid at (i,j). */
                agent_grid[i][j] = ag;
             }
 
            
         }
     }
 
     /* ******************************* */
     /* Populate the my_world variable. */
     /* ******************************* */
 
     /* A bidimensional array of agents can be interpreted as a pointer to
        agents. */
     my_world.grid = (AGENT **) agent_grid;
 
     /* World size is defined by constants in this example. */
     my_world.xsize = WORLD_X;
     my_world.ysize = WORLD_Y;
 
     /* ********************************************************************* */
     /* Show world using the simple_show_world() function. This function can  */
     /* be used in the first part of the project.                             */
     /* ********************************************************************* */
     system("clear");
     showworld_update(sw, &(my_world));
 
 do {
     do { 
         round = movement(agent_grid, agents_list, nagents, round, WORLD_X, WORLD_Y);
         showworld_update(sw, &(my_world));
         printf("round :%u ,turn: %u nagents: %u  \n\n",round, turn, nagents);
     } while (round != nagents);
     turn++;
     round=0;
 
     //replace the list of agents ID for the next turn
     a = 0;
     for (unsigned int i = 0; i < WORLD_Y; ++i)
     {
         for (unsigned int j = 0; j < WORLD_X; ++j)
         {
             if (agent_grid[i][j].type == Zombie || agent_grid[i][j].type == Human )
             {   
                 if(agent_grid[i][j].type ==Human)
                 {
                     existe_human =1; //search one human in the grid
                 }
                 agents_list[a]= agent_grid[i][j].id;
                 a ++;    
             }   
         }
     }
     if(existe_human ==0) //if don't exists humans anymore
     {
         printf("Zombies win!!!\n");
         break; //end game, zombies win
     }
     else {existe_human =0;}
 
 } while (turn != max_turn);
 
 
 for (unsigned int i = 0; i < WORLD_Y; ++i)
     {
         for (unsigned int j = 0; j < WORLD_X; ++j)
         {   
             if(agent_grid[i][j].type ==Human)
             {
                 existe_human =1; //search one human in the grid
             }
    
         }   
     }
     if(existe_human ==1) //if exists humans yet
     {
         printf("Humans win!!!\n");
     }
     
     /* Before finishing, ask user to press ENTER. */
     printf("end game!!\n");
     printf("Press ENTER to continue...");
     getchar();
 
     /* Destroy world display. */
     showworld_destroy(sw);
     free_agent_grid(WORLD_X, agent_grid);
     /* Bye. */
     return 0;
 }
 
 /**
  * This function is an implementation of the ::get_agent_info_at() function
  * definition. It only works for ::AGENT and ::WORLD structures defined in this
  * example.
  *
  * It basically receives a pointer to a ::WORLD structure, obtains the AGENT
  * structure in the given coordinates, and returns the agent information in a
  * bit-packed `unsigned int`.
  *
  * @note This is an example which will probably not work in a fully functional
  * game. Students should develop their own implementation of
  * ::get_agent_info_at() and agent/world data structures.
  *
  * @param w Generic pointer to object representing the simulation world.
  * @param x Horizontal coordinate of the simulation world from where to fetch
  * the agent information.
  * @param y Vertical coordinate of the simulation world from where to fetch
  * the agent information.
  * @return An integer containing bit-packed information about an agent, as
  * follows: bits 0-1 (agent type), bit 2 (is agent playable), bits 3-18 (agent
  * ID). Bits 19-31 are available for student-defined agent extensions.
  * */
 unsigned int example_get_ag_info(void *w, unsigned int x, unsigned int y) {
 
     /* The agent information to return. */
     unsigned int ag_info = 0;
 
     /* Convert generic pointer to world to a WORLD object. */
     WORLD *my_world = (WORLD *) w;
 
     /* Check if the given (x,y) coordinates are within bounds of the world. */
     if ((x >= my_world->xsize) || (y >= my_world->ysize)) {
 
         /* If we got here, then the coordinates are off bounds. As such we will
            report that the requested agent is of unknown type. No need to
            specify agent ID or playable status, since the agent is unknown. */
         ag_info = Unknown;
 
     } else {
 
         /* Given coordinates are within bounds, let's get and pack the request
            agent information. */
 
         /* Obtain agent at specified coordinates. */
         AGENT ag = my_world->grid[x][y];
 
         /* Is there an agent at (x,y)? */
         if (ag.type == None) {
 
             /* If there is no agent at the (x,y) coordinates, set agent type to
                None. No need to specify agent ID or playable status, since
                there is no agent here. */
             ag_info = None;
 
         } else {
 
             /* If we get here it's because there is an agent at (x,y). Bit-pack
                all the agent information as specified by the get_agent_info_at
                function pointer definition. */
             ag_info = (ag.id << 3) | (ag.playable << 2) | ag.type;
 
         }
 
     }
 
     /* Return the requested agent information. */
     return ag_info;
 }
