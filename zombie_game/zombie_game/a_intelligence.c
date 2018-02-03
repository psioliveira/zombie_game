#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "showworld.h"



int a_int ( unsigned int key){

  key = ((rand() % 9)+1 );
  switch(key)
  {
    case 1:{key= ldown ; break;}
      
    case 2:{key= down ; break;}
      
    case 3:{key= rdown ; break;}
      
    case 4:{key= left ; break;}
      
    case 5:{key= pass ; break;}
      
    case 6:{key= right ; break;}
      
    case 7:{key= lup ; break;}
      
    case 8:{key= up ; break;}
      
    case 9:{key= rup ; break;}
      
    default: break;  
      
  }
 

return key;

}
