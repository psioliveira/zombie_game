#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "functions.h"
#include "showworld.h"




void movement(
    AGENT **agent_grid,
    unsigned int *agents_list,
    unsigned int max_id,
 	unsigned int turns ) {
 
  /** Horizontal world size. */
 unsigned int WORLD_X = 10;

 /** Vertical world size. */
 unsigned int WORLD_Y = 10;

	
	unsigned int x=0, y=0, a=0;
    unsigned int rand_id = 0;
    unsigned int turn=0;

    //auxiliar flags
    unsigned int flag =0, c_id=0;

    /*count how many IDs have already been chosen*/
    unsigned int count = 1;
  
    /* 1,2,3,4,5,6,7,8,9 are the aceptable 
    keys for the agents */
    int key=0;
    
    do { 
        do {
            
            /* generates a random id number to choose 
            the agent who will move */
            rand_id = (rand() % max_id+1);

            //loop to search the ID in agents string.
            for (int a = 0 ; a < max_id ; a++)
            {
             //if the random ID is correct, stop the loop and save ID.   
             	if (agents_list[a] == rand_id) 
                {
                    flag = 1;
                    agents_list[a] = max_id+2;
                    break;
                }
            }

        } while (flag!=1);

        if(agent_grid[y][x].playable == 1)
        {
            printf("walk\n");
            
            key= getchar(); 
            
        }
        else if(agent_grid[y][x].playable == 0)
        {
           // art_int();
        }


        //search the agent in the grid
        for( x=0; x<WORLD_X;x++)
        {
            for( y=0; y<WORLD_Y;y++)
            {
                if(agent_grid[y][x].id == rand_id)
                {
                    c_id=1;
                    break;
                }
            }
    
            if(c_id == 1 )
            {
                c_id=0;
                break;
            }
        }

        switch(key)
        {
            case 4: //left mov 
            {
                    //if the entrance aren't in the first column
                    if ((x > 0) && (agent_grid[y][x-1]).type == None) 
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y][x-1]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y][x-1] = hold_pos;
                        agent_grid[y][x] = hold_pos2;  
                        count++;
                    }

                     //if the entrance are in the first column
                    if((x == 0) && (agent_grid[y][WORLD_X-1]).type == None)
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y][WORLD_X-1]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y][WORLD_X-1] = hold_pos;
                        agent_grid[y][x] = hold_pos2;  
                    	count++;
                    }
				
                   					/****************
                   					* infect humans *
                   					****************/
                   //if the entrance aren't in the first column
                    if ((x > 0) && (agent_grid[y][x]).type == Zombie 
                    			&& (agent_grid[y][x-1]).type == Human) 
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y][x-1].type = Zombie;
                        agent_grid[y][x-1].playable = 0x0;
                        count++;
                    }

                    //if the entrance are in the first column
                    if ((x == 0) && (agent_grid[y][x]).type == Zombie 
                    			 && (agent_grid[y][WORLD_X-1]).type == Human)
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y][WORLD_X-1].type = Zombie;
                        agent_grid[y][WORLD_X-1].playable = 0x0;
                        count++;
                    }

                else{
                   printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
                }
                key = 0;
                x=0; y=0;
                break;
            }


            case 2: //down mov
            {

                	//if the entrance are in the first line
                    if ((y < WORLD_Y-1) && (agent_grid[y+1][x]).type == None) 
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y+1][x]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y][x] = hold_pos2;
                        agent_grid[y+1][x] = hold_pos;  
                        count++;
                       
                    }


                     //if the entrance are in the last line
                    if((x == WORLD_Y-1 ) && (agent_grid[0][x]).type == None)
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[0][x]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[0][x] = hold_pos;
                        agent_grid[y][x] = hold_pos2;  
                        count++;
                       
                    }
				
                   					/****************
                   					* infect humans *
                   					****************/
                   //if the entrance aren't in the first column
                    if ((x < WORLD_X-1) && (agent_grid[y][x]).type == Zombie 
                    					&& (agent_grid[y+1][x]).type == Human) 
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y+1][x].type = Zombie;
                        agent_grid[y+1][x].playable = 0x0;
                        count++;
                       
                    }

                    //if the entrance are in the first column
                    if ((x == WORLD_X-1 ) && (agent_grid[y][x]).type == Zombie 
                    					  && (agent_grid[y+1][x]).type == Human)
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y+1][x].type = Zombie;
                        agent_grid[y+1][x].playable = 0x0;
                        count++;
                        
                    }
                else{
                   printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
                }
                key = 0;
                x=0; y=0;
                break;
            }

            case 6: //right mov
           {

                	//if the entrance aren't in the last column
                	if (x < WORLD_X-1 && agent_grid[y][x+1].type == None) 
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y][x+1]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y][x+1] = hold_pos;
                        agent_grid[y][x] = hold_pos2;
                        count++;
                        
                    }
                     //if the entrance are in the last column
                    if((x == WORLD_X-1 ) && (agent_grid[y][0]).type == None)
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y][0]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y][0] = hold_pos;
                        agent_grid[y][x] = hold_pos2; 
                        count++;
                        
                    }
				
                   					/****************
                   					* infect humans *
                   					****************/
                   //if the entrance aren't in the first column
                    if ((x > WORLD_X-1) && (agent_grid[y][x]).type == Zombie 
                    					&& (agent_grid[y][x+1]).type == Human) 
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y][x+1].type = Zombie;
                        agent_grid[y][x+1].playable = 0x0;
                        count++;
                        
                    }

                    //if the entrance are in the first column
                    if ((x == WORLD_X-1 ) && (agent_grid[y][x]).type == Zombie 
                    					  && (agent_grid[y][0]).type == Human)
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y][0].type = Zombie;
                        agent_grid[y][0].playable = 0x0;
                        count++;
                       
                    }
                else{
                   printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
                }
                key = 0;
                x=0; y=0;
                break;
            }

            case 8: //up mov
            {   

                	//if the entrance aren't in the first column
                    if (y > 0 && (agent_grid[y-1][x]).type == None) 
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y-1][x]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y-1][x] = hold_pos;
                        agent_grid[y][x] = hold_pos2; 
                        count++;
                      
                    }


                     //if the entrance are in the first column
                    if((y == 0 ) && (agent_grid[WORLD_Y-1][x]).type == None)
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[WORLD_Y-1][x]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[WORLD_Y-1][x] = hold_pos;
                        agent_grid[y][x] = hold_pos2;  
                        count++;
                       
                    }
                
                   					/****************
                   					* infect humans *
                   					*****************/
                   //if the entrance aren't in the first column
                    if ((y > 0 ) && (agent_grid[y][x]).type == Zombie 
                    					&& (agent_grid[y-1][x]).type == Human) 
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y-1][x].type = Zombie;
                        agent_grid[y-1][x].playable = 0x0;
                        count++;
                       
                    }

                    //if the entrance are in the first column
                    if ((y == 0 ) && (agent_grid[y][x]).type == Zombie 
                    			  && (agent_grid[WORLD_Y-1][x]).type == Human)
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y+1][x].type = Zombie;
                        agent_grid[y+1][x].playable = 0x0;
                        count++;
                        
                    }
                    else{
                        printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
                    }
                    key = 0;
                    x=0; y=0;
                    break;
            }

            case 1:
            {

                	//if the entrance aren't in the last line and first column
                    if ((y < WORLD_Y-1) && (x > 0) &&
                   		(agent_grid[y+1][x-1]).type == None) 
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y+1][x-1]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y][x] = hold_pos2;
                        agent_grid[y+1][x-1] = hold_pos; 
                        count++;
                       
                    }


                     //if the entrance are in the last line and first column 
                    if  ( ( (y == WORLD_Y-1 ) || (x == 0) ) &&
                    	  (agent_grid[0][WORLD_X-1].type == None) )
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[0][WORLD_X-1]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[0][WORLD_X-1] = hold_pos;
                        agent_grid[y][x] = hold_pos2;  
                        count++;
                        
                    }
				
                   					/****************
                   					* infect humans *
                   					****************/
                   //if the entrance aren't in thelast line and first column
                    if ((y < WORLD_Y-1) && (x > 0) 
                    		&& (agent_grid[y][x]).type == Zombie 
                    		&& (agent_grid[y+1][x-1]).type == Human) 
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y+1][x-1].type = Zombie;
                        agent_grid[y+1][x-1].playable = 0x0;
                        count++;
                        
                    }

                    //if the entrance are in the last line and first column 
                    if ( ( y == WORLD_Y-1  || x ==  0 ) 
                    	&& ( agent_grid[y][x].type == Zombie ) 
                    	&& ( agent_grid[0][WORLD_X-1].type == Human) )
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[0][WORLD_X-1].type = Zombie;
                        agent_grid[0][WORLD_X-1].playable = 0x0;
                        count++;
                        
                    }
                    else{
                        printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
                    }

                    key = 0;
                    x=0; y=0;
                	break;
            }

            case 3:
            {
                	//if the entrance aren't in the last line and last column
                    if ( ( y < WORLD_Y-1 && x < WORLD_X-1 ) &&
                   		(agent_grid[y+1][x+1].type == None ) ) 
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y+1][x+1]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y][x] = hold_pos2;
                        agent_grid[y+1][x+1] = hold_pos;  
                        count++;
                        
                    }


                     //if the entrance are in the last column 
                    if ( x == WORLD_X-1 )
                    {

                        if( y != WORLD_Y-1 && (agent_grid[y+1][0].type == None ) )
                        {
                            AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                            AGENT hold_pos2 = agent_grid[y+1][0]; //hold blank value

                            /*Swich values between actual and blank value*/
                            agent_grid[y+1][0] = hold_pos;
                            agent_grid[y][x] = hold_pos2;  

                        }

                        if (y == WORLD_Y-1 && agent_grid[0][0].type == None )
                        { 
                            AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                            AGENT hold_pos2 = agent_grid[y+1][0]; //hold blank value

                            /*Swich values between actual and blank value*/
                            agent_grid[y+1][0] = hold_pos;
                            agent_grid[y][x] = hold_pos2;  

                        }


                        count++;

                       
                    }
				
                   					/****************
                   					* infect humans *
                   					****************/
                	//if the entrance aren't in the last line and last column
                    if ((y < WORLD_Y-1 && x < WORLD_X-1) 
                    	&& (agent_grid[y][x].type == Zombie )
                    	&& (agent_grid[y+1][x+1].type == Human ) )
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y+1][x+1].type = Zombie;
                        agent_grid[y+1][x+1].playable = 0x0;
                        count++;
                        
                    }

                    //if the entrance are in the last line and last column 
                    if ( ( y == WORLD_Y-1  || x == WORLD_X-1 ) 
                    	&& (agent_grid[y][x].type == Zombie )
                    	&& (agent_grid[0][0].type == Human ) )
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[0][0].type = Zombie;
                        agent_grid[0][0].playable = 0x0;
                        count++;
                        
                    }
                    else{
                        printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
                    }
                    key = 0;
                    x=0; y=0;
                	break;
            }

            case 7:
            {
                	//if the entrance aren't in the first line and first column
                    if ( (y >0 && x >0 ) && ( agent_grid[y-1][x-1].type == None ) ) 
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y-1][x-1]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y][x] = hold_pos2;
                        agent_grid[y-1][x-1] = hold_pos;  
                        count++;
                        
                    }


                     //if the entrance are in the first column 
                    if ( ( x == 0 ) &&
                    	 ( agent_grid[y-1][WORLD_X-1].type == None ) )
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y-1][WORLD_X-1]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y-1][WORLD_X-1] = hold_pos;
                        agent_grid[y][x] = hold_pos2;  
                        count++;
                        
                    }
				
                   					/****************
                   					* infect humans *
                   					****************/
                	//if the entrance aren't in the first line and first column
                    if ( ( y < WORLD_Y-1 && x < WORLD_X-1 ) 
                    		&& ( agent_grid[y][x].type == Zombie )
                    		&& ( agent_grid[y+1][x+1].type == Human ) ) 
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y+1][x+1].type = Zombie;
                        agent_grid[y+1][x+1].playable = 0x0;
                        count++;
                        
                    }

                    //if the entrance are in the first line and first column 
                    if ((y == 0 && x == 0) 
                    		&& (agent_grid[y][x]).type == Zombie 
                    		&& (agent_grid[WORLD_Y-1][WORLD_X-1].type == Human) )
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[WORLD_Y-1][WORLD_X-1].type = Zombie;
                        agent_grid[WORLD_Y-1][WORLD_X-1].playable = 0x0;
                        count++;
                        
                    }
                    else{
                        printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
                    }
                    key = 0;
                    x=0; y=0;
                	break;
            }

            case 9:
            {
                	//if the entrance aren't in the first line and last column
                    if ( ( y > 0 && x < WORLD_X-1 ) 
                        && ( agent_grid[y-1][x+1].type == None ) )
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y-1][x+1]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y][x] = hold_pos2;
                        agent_grid[y-1][x+1] = hold_pos; 
                        count++;
                        
                    }


                     //if the entrance are in the first line and last column 
                    if ( x == WORLD_X-1 &&
                    	(agent_grid[y-1][0].type == None) )
                    {
                        AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                        AGENT hold_pos2 = agent_grid[y-1][0]; //hold blank value

                        /*Swich values between actual and blank values*/
                        agent_grid[y-1][0] = hold_pos;
                        agent_grid[y][x] = hold_pos2;  
                        count++;
                        
                    }
				
                   					/****************
                   					* infect humans *
                   					****************/
                	//if the entrance aren't in the first line and last column
                    if ((y > 0) && (x < WORLD_X-1)
                    		&& (agent_grid[y][x].type == Zombie )
                    		&& (agent_grid[y-1][x+1].type == Human) )
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y-1][x+1].type = Zombie;
                        agent_grid[y-1][x+1].playable = 0x0;
                        count++;
                       
                    }

                    //if the entrance are in the first line and the last column 
                    if ((x == WORLD_X-1)
                    	&& (agent_grid[y][x].type == Zombie )
                    	&& (agent_grid[y-1][0].type == Human))
                    {
                        /*Swich the value of Human to Zombie*/
                        agent_grid[y-1][0].type = Zombie;
                        agent_grid[y-1][0].playable = 0x0;
                        count++;
                        
                    }
                    else{
                        printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
                    }
                    key = 0;
                    x=0; y=0;
                	break;
            }

                case 5:
                {
                	printf("\n turn skipped.\n");
                	count++;
                    x=0; y=0;
                    break;
                }

                default:
                { 
                	printf("this key is invalid!\n\n");
                    printf( "key ==> %d",key);
                	agents_list[a] = rand_id; //return the agent id into the agents list.
                    x=0; y=0;
                    break;
                }
        }
        if (count == max_id){ turn++ ; }

    }while (count < max_id);  
}
