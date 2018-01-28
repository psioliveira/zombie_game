#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "functions.h"
#include "showworld.h"




unsigned int movement(
    AGENT **agent_grid,
    unsigned short *agents_list,
    unsigned short max_id, 
    unsigned int WORLD_X, unsigned int WORLD_Y) 
{
	
	unsigned int x=0, y=0, a=0;
    unsigned int rand_id = 0;
    unsigned int turn=0;

    //auxiliar flags
    unsigned int flag =0, c_id=0;

    
  
    /* 1,2,3,4,5,6,7,8,9 are the aceptable 
    keys for the agents */
 
    int key;
    
     
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
                agents_list[a] = max_id+5;
                break;
            }
        }

    } while (flag!=1);

    if(agent_grid[y][x].playable )
    {   
        printf("ID %.2x   ", rand_id);
        printf("walk: ");
        key= getchar(); 
        int trash= getchar(); 
    }
    else if (!(agent_grid[y][x].playable)) 
    {
        printf( "NPC!!!   ");
        printf("ID %.2x   ", rand_id);
        printf("walk: ");
            
        key= getchar();
    int trash= getchar();
        // a_int();
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
        case up: //left mov 
        {printf("up");
            //if the entrance aren't in the first line
            if ((x > 0) && (agent_grid[y][x-1]).type == None) 
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[y][x-1]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[y][x-1] = hold_pos;
                agent_grid[y][x] = hold_pos2;  
                turn++;
                break;
            }

             //if the entrance are in the first line
            else if((x == 0) && (agent_grid[WORLD_X-1][y]).type == None)
            {
                AGENT hold_pos = agent_grid[x][y]; //hold actual local value
                AGENT hold_pos2 = agent_grid[WORLD_X-1][y]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[WORLD_X-1][y] = hold_pos;
                agent_grid[x][y] = hold_pos2;  
            	turn++;
                break;
            }

				/****************
				* infect humans *
				****************/
            //if the entrance aren't in the first column
            else if ((x > 0) && (agent_grid[x][y]).type == Zombie 
                    	&& (agent_grid[x-1][y]).type == Human) 
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[x-1][y].type = Zombie;
                agent_grid[x-1][y].playable = 0x0;
                turn++;
                break;
                }

            //if the entrance are in the first column
            else if ((x == 0) && (agent_grid[x][y]).type == Zombie 
            			 && (agent_grid[WORLD_X-1][y]).type == Human)
            {
                /*Swich the value of Human to Zombie*/
               agent_grid[y][WORLD_X-1].type = Zombie;
                agent_grid[y][WORLD_X-1].playable = 0x0;
                turn++;
                break;
            }

            else 
            {
               printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
            }
            
            x=0; y=0;

            break;
        }


        case right: //right mov
        {printf("right");

        	//if the entrance are in the first line
            if ((y < WORLD_Y-1) && (agent_grid[y+1][x]).type == None) 
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[y+1][x]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[y][x] = hold_pos2;
                agent_grid[y+1][x] = hold_pos;  
                turn++;
                break;       
            }


            //if the entrance are in the last line
            else if((y == WORLD_Y-1 ) && (agent_grid[0][x]).type == None)
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[0][x]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[0][x] = hold_pos;
                agent_grid[y][x] = hold_pos2;  
                turn++;
                break;       
            }
				
			/****************
			* infect humans *
			****************/

            //if the entrance aren't in the first column
            else if ((x < WORLD_X-1) && (agent_grid[y][x]).type == Zombie 
            					&& (agent_grid[y+1][x]).type == Human) 
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[y+1][x].type = Zombie;
                agent_grid[y+1][x].playable = 0x0;
                turn++;
                break;       
            }

            //if the entrance are in the last line
            else if ((y == WORLD_Y-1 ) && (agent_grid[y][x]).type == Zombie 
            					  && (agent_grid[0][x]).type == Human)
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[0][x].type = Zombie;
                agent_grid[0][x].playable = 0x0;
                turn++;
                break;
                        
            }
            else
            {
               printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
            }
            
            x=0; y=0;
            break;
        }

        case down: //down mov
        {printf("down");

            //if the entrance aren't in the last line
            if (x < WORLD_X-1 && agent_grid[y][x+1].type == None) 
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[y][x+1]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[y][x+1] = hold_pos;
                agent_grid[y][x] = hold_pos2;
                turn++;
                break;
                        
            }
                     //if the entrance are in the last column
            else if((x == WORLD_X-1 ) && (agent_grid[y][0]).type == None)
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[y][0]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[y][0] = hold_pos;
                agent_grid[y][x] = hold_pos2; 
                turn++;
                break;
                        
            }
				
                   			/****************
                   			* infect humans *
                   			****************/
            //if the entrance aren't in the first column
            else if ((x > WORLD_X-1) && (agent_grid[y][x]).type == Zombie 
            					&& (agent_grid[y][x+1]).type == Human) 
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[y][x+1].type = Zombie;
                agent_grid[y][x+1].playable = 0x0;
                turn++;
                break;
                        
            }

            //if the entrance are in the first column
            else if ((x == WORLD_X-1 ) && (agent_grid[y][x]).type == Zombie 
            					  && (agent_grid[y][0]).type == Human)
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[y][0].type = Zombie;
                agent_grid[y][0].playable = 0x0;
                turn++;
                break;
                       
            }
            else
            {
               printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
            }
            
            x=0; y=0;
            break;
        }

        case left: //left mov
        {  printf("left"); 

            //if the entrance aren't in the first column
            if (y > 0 && (agent_grid[y-1][x]).type == None) 
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[y-1][x]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[y-1][x] = hold_pos;
                agent_grid[y][x] = hold_pos2; 
                turn++;
                break;
                      
            }


            //if the entrance are in the first column
            else if((y == 0 ) && (agent_grid[WORLD_Y-1][x]).type == None)
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[WORLD_Y-1][x]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[WORLD_Y-1][x] = hold_pos;
                agent_grid[y][x] = hold_pos2;  
                turn++;
                break;      
            }
                
           			  	   /****************
                            * infect humans *
                   			*****************/
            //if the entrance aren't in the first column
            else if ((y > 0 )&& (agent_grid[y][x]).type == Zombie 
     	  			&& (agent_grid[y-1][x]).type == Human) 
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[y-1][x].type = Zombie;
                agent_grid[y-1][x].playable = 0x0;
                turn++;
                break;       
            }

            //if the entrance are in the first column
            else if ((y == 0 ) && (agent_grid[y][x]).type == Zombie 
            			  && (agent_grid[WORLD_Y-1][x]).type == Human)
            {
            /*Swich the value of Human to Zombie*/
                agent_grid[y+1][x].type = Zombie;
                agent_grid[y+1][x].playable = 0x0;
                turn++;
                break;        
            }
            else
            {
                printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
            }
            
            x=0; y=0;
            break;
        }

        case rup: //right up mov
        {printf("rup");

    	   //if the entrance aren't in the last line and first column
            if ((x < WORLD_X-1) && (y > 0) &&
    	      (agent_grid[x+1][y-1]).type == None) 
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[y-1][x+1]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[x][y] = hold_pos2;
                agent_grid[x+1][y-1] = hold_pos; 
                turn++;
                break;       
            }


             //if the entrance are in the last column 
            else if  (y == 0)
            {
                if((x == WORLD_X-1 ) && (agent_grid[0][WORLD_Y-1].type == None) )
                {
                    AGENT hold_pos = agent_grid[x][y]; //hold actual local value
                    AGENT hold_pos2 = agent_grid[0][WORLD_Y-1]; //hold blank value
    
                    /*Swich values between actual and blank values*/
                    agent_grid[0][WORLD_Y-1] = hold_pos;
                    agent_grid[x][y] = hold_pos2;  
                    turn++;
                    break;        
                }

                 if((x != WORLD_X-1 ) && (agent_grid[0][y-1].type == None) )
                {
                    AGENT hold_pos = agent_grid[x][y]; //hold actual local value
                    AGENT hold_pos2 = agent_grid[0][y-1]; //hold blank value
    
                    /*Swich values between actual and blank values*/
                    agent_grid[0][y-1] = hold_pos;
                    agent_grid[x][y] = hold_pos2;  
                    turn++;
                    break;        
                }


			}	
                				/****************
                				* infect humans *
                				****************/
            //if the entrance aren't in thelast line and first column
            if ((x < WORLD_X-1) && (y > 0) 
            		&& (agent_grid[x][y]).type == Zombie 
            		&& (agent_grid[x+1][y-1]).type == Human) 
            {
                /*Swich the value of Human to Zombie*/
               agent_grid[x+1][y-1].type = Zombie;
                agent_grid[x+1][y-1].playable = 0x0;
                turn++;
                break;       
            }

            //if the entrance are in the last column 
            else if ( x == WORLD_X-1 ) 
            {
                if((y ==  0) 
                && ( agent_grid[x][y].type == Zombie ) 
                && ( agent_grid[0][WORLD_Y-1].type == Human) )
                {
                    /*Swich the value of Human to Zombie*/
                    agent_grid[0][WORLD_Y-1].type = Zombie;
                    agent_grid[0][WORLD_Y-1].playable = 0x0;
                    turn++;
                    break;   
                }

                if((y !=  0) 
                && ( agent_grid[x][y].type == Zombie ) 
                && ( agent_grid[0][y-1].type == Human) )
                {
                    /*Swich the value of Human to Zombie*/
                    agent_grid[0][y-1].type = Zombie;
                    agent_grid[0][y-1].playable = 0x0;
                    turn++;
                    break;   
                }


            }
            else
            {
                printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
            }
            
            x=0; y=0;
    	   break;
            }

        case rdown: //right down mov
        {printf("rdown");
            //if the entrance aren't in the last line and last column
            if ( ( y < WORLD_Y-1 && x < WORLD_X-1 ) &&
            	(agent_grid[y+1][x+1].type == None ) ) 
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[y+1][x+1]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[y][x] = hold_pos2;
                agent_grid[y+1][x+1] = hold_pos;  
                turn++;
                break;        
            }


             //if the entrance are in the last column 
            else if ( x == WORLD_X-1 )
            {

                if( (y != WORLD_Y-1) && (agent_grid[y+1][0].type == None ) )
                {
                    AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                    AGENT hold_pos2 = agent_grid[y+1][0]; //hold blank value

                    /*Swich values between actual and blank value*/
                    agent_grid[y+1][0] = hold_pos;
                    agent_grid[y][x] = hold_pos2;  

                   }

                else if (y == WORLD_Y-1 && agent_grid[0][0].type == None )
                { 
                    AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                    AGENT hold_pos2 = agent_grid[01][0]; //hold blank value

                    /*Swich values between actual and blank value*/
                    agent_grid[0][0] = hold_pos;
                    agent_grid[y][x] = hold_pos2;  
                }

                turn++;
                break;           
            }
				

			/****************
    	    * infect humans *
            ****************/
            //if the entrance aren't in the last line and last column
            else if ((y < WORLD_Y-1 && x < WORLD_X-1) 
            	&& (agent_grid[y][x].type == Zombie )
            	&& (agent_grid[y+1][x+1].type == Human ) )
            {
                 /*Swich the value of Human to Zombie*/
                agent_grid[y+1][x+1].type = Zombie;
                agent_grid[y+1][x+1].playable = 0x0;
                turn++;
                break;       
            }

            //if the entrance are in the last line and last column 
            else if ( ( y == WORLD_Y-1  || x == WORLD_X-1 ) 
        	    && (agent_grid[y][x].type == Zombie )
            	&& (agent_grid[0][0].type == Human ) )
                {
                /*Swich the value of Human to Zombie*/
                agent_grid[0][0].type = Zombie;
                agent_grid[0][0].playable = 0x0;
                turn++;
                break;       
            }
            else
            {
                printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
            }
            
            x=0; y=0;
            break;
        }

        case lup: // left up mov
        {printf("lup");
            //if the entrance aren't in the first line and first column
            if ( (y >0 && x >0 ) && ( agent_grid[y-1][x-1].type == None ) ) 
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[y-1][x-1]; //hold blank value

                    /*Swich values between actual and blank values*/
                agent_grid[y][x] = hold_pos2;
                agent_grid[y-1][x-1] = hold_pos;  
                turn++;
                break;        
            }


             //if the entrance are in the first column 
            else if ( x == 0 ) 
            {

                if(y!=0 && (agent_grid[y-1][WORLD_X-1].type == None) )
                {

                    AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                    AGENT hold_pos2 = agent_grid[y-1][WORLD_X-1]; //hold blank value

                    /*Swich values between actual and blank values*/
                    agent_grid[y-1][WORLD_X-1] = hold_pos;
                    agent_grid[y][x] = hold_pos2;  
                    turn++;
                    break;  
                } 

                if(y == 0 && (agent_grid[WORLD_Y-1][WORLD_X-1].type == None) )
                {

                    AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                    AGENT hold_pos2 = agent_grid[WORLD_Y-1][WORLD_X-1]; //hold blank value

                    /*Swich values between actual and blank values*/
                    agent_grid[WORLD_Y-1][WORLD_X-1] = hold_pos;
                    agent_grid[y][x] = hold_pos2;  
                    turn++;
                    break;  
                }
            }			
               				/****************
               				* infect humans *
               				****************/
            //if the entrance aren't in the first line and first column
            else if ( ( y < WORLD_Y-1 && x < WORLD_X-1 ) 
                    && ( agent_grid[y][x].type == Zombie )
                	&& ( agent_grid[y+1][x+1].type == Human ) ) 
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[y+1][x+1].type = Zombie;
                agent_grid[y+1][x+1].playable = 0x0;
                turn++;
                break;    
            }

            //if the entrance are in the first line and first column 
            else if ((y == 0 && x == 0) 
            		&& (agent_grid[y][x]).type == Zombie 
            		&& (agent_grid[WORLD_Y-1][WORLD_X-1].type == Human) )
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[WORLD_Y-1][WORLD_X-1].type = Zombie;
                agent_grid[WORLD_Y-1][WORLD_X-1].playable = 0x0;
                turn++;
                break;    
            }

            else if ((y != 0 && x == 0) 
                    && (agent_grid[y][x]).type == Zombie 
                    && (agent_grid[y-1][WORLD_X-1].type == Human) )
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[y-1][WORLD_X-1].type = Zombie;
                agent_grid[y-1][WORLD_X-1].playable = 0x0;
                turn++;
                break;    
            }
            else
            {
                printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
            }
            
            key = 0;
            x=0; y=0;
            break;
        }

        case ldown: //left down mov
        {printf("ldown");
            //if the entrance aren't in the last line and first column
            if ( ( y > 0 && x < WORLD_X-1 ) 
                && ( agent_grid[y-1][x+1].type == None ) )
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[y-1][x+1]; //hold blank value
                    /*Swich values between actual and blank values*/
                agent_grid[y][x] = hold_pos2;
                agent_grid[y-1][x+1] = hold_pos; 
                turn++;
                break;    
            }

             //if the entrance are in the first column and last line 
            else if (( y == WORLD_Y-1 && x==0)&&
            	(agent_grid[y-1][0].type == None) )
            {
                AGENT hold_pos = agent_grid[y][x]; //hold actual local value
                AGENT hold_pos2 = agent_grid[y-1][0]; //hold blank value

                /*Swich values between actual and blank values*/
                agent_grid[y-1][0] = hold_pos;
                agent_grid[y][x] = hold_pos2;  
                turn++;
                break;    
            }
			
               				/****************
               				* infect humans *
               				****************/
            //if the entrance aren't in the first line and last column
            else if ((y > 0) && (x < WORLD_X-1)
            		&& (agent_grid[y][x].type == Zombie )
            		&& (agent_grid[y-1][x+1].type == Human) )
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[y-1][x+1].type = Zombie;
                agent_grid[y-1][x+1].playable = 0x0;
                turn++;
                break;   
            }
            //if the entrance are in the first line and the last column 
            else if ((x == WORLD_X-1)
            	&& (agent_grid[y][x].type == Zombie )
            	&& (agent_grid[y-1][0].type == Human))
            {
                /*Swich the value of Human to Zombie*/
                agent_grid[y-1][0].type = Zombie;
                agent_grid[y-1][0].playable = 0x0;
                turn++;
                break;    
            }
            else
            {
                printf("invalid moviment!\nthe cell what you want to move on is already occuepd.\n\n");
            }
             
            x=0; y=0;
            break;
        }

        case pass: // skip turn
        {
         	printf("\n turn skipped.\n");
        	turn++;
            x=0; y=0;
            break;
        }

        default: // wrong key
        { 
        	printf("this key is invalid!\n\n");
            printf( "key ==> %d \n",key);
        	agents_list[a] = rand_id; //return the agent id into the agents list.
          x=0; y=0;
            break;
        }
    }

    if (turn == max_id){ turn++ ; }
 
 return turn;
}
