#include <stdio.h>
#include <stdlib.h>

#include "./xx_grid.h"

int main ( int argc, char** argv ) {

  xx_grid* i_grid = xx_create_grid ( 640, 480, 10, 20 );
  
  xx_add_to_grid ( i_grid, 0, 10, 10 );
  xx_add_to_grid ( i_grid, 0, 10, 10 );
  xx_add_to_grid ( i_grid, 0, 10, 10 );
  xx_add_to_grid ( i_grid, 0, 10, 10 );
  xx_add_to_grid ( i_grid, 0, 10, 10 );
  xx_add_to_grid ( i_grid, 0, 10, 10 );
  xx_add_to_grid ( i_grid, 0, 10, 10 );
  xx_add_to_grid ( i_grid, 0, 10, 10 );
  xx_add_to_grid ( i_grid, 0, 10, 10 );


  xx_add_to_grid ( i_grid, 1, 10, 10 );
  xx_add_to_grid ( i_grid, 1, 10, 10 );
  xx_add_to_grid ( i_grid, 1, 11, 10 );
  xx_add_to_grid ( i_grid, 1, 10, 10 );
  xx_add_to_grid ( i_grid, 1, 10, 10 );
  xx_add_to_grid ( i_grid, 1, 10, 10 );
  xx_add_to_grid ( i_grid, 1, 10, 10 );
  xx_add_to_grid ( i_grid, 1, 10, 10 );
  xx_add_to_grid ( i_grid, 1, 10, 10 );
  xx_add_to_grid ( i_grid, 1, 10, 10 );

  xx_print_grid_info ( i_grid );

  xx_free_grid ( i_grid );
  return 0;
}
