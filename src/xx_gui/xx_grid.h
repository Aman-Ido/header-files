/* 
  xx_grid.h
    - this file will have the main grid system (in future)
    
    
    * But for now
      - it will have 2 functions to draw grid on the screen
*/

/* 
 * struct for grid system
 * */
typedef struct {
  int SCREEN_WIDTH; // screen width
  int SCREEN_HEIGHT; // screen height

  int curr_x;
  int curr_y;

  int margin_x;
  int margin_y;

  int curr_row;
  int curr_col;

  int arr_n; // will be 10
  int* arr;

  int ptr_n; // for the pointer SDL_Point
  SDL_Point* ptr; // for storing the x, y of different elements
  /* 
   * 0 -> screen_width, 1 -> screen_height 
   * 2 -> curr_x, 3 -> curr_y 
   * 4 -> margin_x, 5 -> margin_y
   * 6 -> curr_row, 7 -> curr_col
   * 8 -> cursor_x, cursor_y
   * */

} xx_grid;
/* 
  function - declarations
*/
// independent functions - can be called without other libraries just this one
void xx_draw_grid_lines (SDL_Renderer* i_renderer, size_t max_width, size_t max_height, size_t scale); // draws line grid 
void xx_draw_grid_dots (SDL_Renderer* i_renderer, size_t max_width, size_t max_height, size_t scale); // draws dot grid

/* 
 * 
 * */
xx_grid* xx_create_grid ( int SCREEN_WIDTH, int SCREEN_HEIGHT, int n );
void xx_free_grid ( xx_grid* i_grid );
/* 
 * just so you don't forget in the future
 *    -- we will take row, col, those are simple
 *    -- but we will also get the pointer to other xx_ based ui things, and we will get the max width and max height
 *    -- there will be another function as well if you want manual control like (int row, int col, int width, int height);
 * */
int xx_x_grid ( int row, void* ptr ); 
int xx_y_grid ( int col, void* ptr );

/* 
  function - definitions
*/

/* 
  function - void xx_draw_grid_lines (SDL_Renderer*, size_t, size_t, size_t)
      - it will draw lines for grids (in red color);
*/
void xx_draw_grid_lines (SDL_Renderer* i_renderer, size_t max_width, size_t max_height, size_t scale) {
  /*
    temp references
  */
  const int n_x = max_width / scale;
  const int n_y = max_height / scale;
  
  SDL_SetRenderDrawColor (i_renderer, 255, 0, 0, 255);
  
  for (int i = 0; i < n_x; i++) {
    SDL_RenderDrawLine (i_renderer, i * scale, 0, i * scale, max_height);
  }
  
  for (int j = 0; j < n_y; j++) {
    SDL_RenderDrawLine (i_renderer, 0, j * scale, max_width, j * scale);
  }
}


/* 
  function - void xx_draw_grid_dots (SDL_Renderer*, size_t, size_t, size_t);
      - it will draw points on the screen (in red color)
*/
void xx_draw_grid_dots (SDL_Renderer* i_renderer, size_t max_width, size_t max_height, size_t scale) {
  /* 
    temp references
  */
  const int n_x = max_width / scale;
  const int n_y = max_height / scale;
  
  SDL_SetRenderDrawColor (i_renderer, 255, 0, 0, 255);
  
  for (int i = 0; i < n_x; i++) {
    for (int j = 0; j < n_y; j++) {
      SDL_RenderDrawPoint (i_renderer, i * scale, j * scale);
    } 
  }
  
}

/* 
 * function - xx_grid* xx_create_grid ( int SCREEN_WIDTH, int SCREEN_HEIGHT, int n )
 *    -- this function will allocate memory and dthen return that pointer
 * */
xx_grid* xx_create_grid ( int SCREEN_WIDTH, int SCREEN_HEIGHT, int n ) {
  xx_grid* r_grid = (xx_grid*) malloc (sizeof(xx_grid) * 1);
  if ( r_grid == NULL ) {
    printf ("\t Error! Memory Allocation, Failed, xx_grid*\n");
    return NULL;
  }

  r_grid -> arr_n = 10;
  r_grid -> arr = (int*) malloc (sizeof(int) * r_grid -> arr_n);
  if (r_grid -> arr == NULL) {
    printf ("\t Error! Memory allocation, failed, xx_grid* -> int*\n");
    return NULL;
  }

  if ( n < 0 ) {
    r_grid -> ptr_n = 20;
  } else {
    r_grid -> ptr_n = n;
  }

  r_grid -> n = 0;

  r_grid -> ptr = (SDL_Point*) malloc (sizeof(SDL_Point) * r_grid -> ptr_n);
  if ( r_grid -> ptr == NULL ) {
    printf ("\t Error! Memory Allocation, Failed, xx_grid* -> SDL_Point*\n");
    return NULL;
  }

  return r_grid;
}

/* 
 * function - void xx_free_grid ( xx_grid* i_grid );
 *    -- function to remove or destroy everything allocated by the x_grid
 * */
void xx_free_grid ( xx_grid* i_grid ) {
  if ( i_grid != NULL ) {
    free ( i_grid -> arr );
    i_grid -> arr = NULL;

    free ( i_grid -> ptr );
    i_grid -> ptr = NULL;

    free ( i_grid );
    i_grid = NULL;
  }
}

/* 
 * function - int xx_x_grid ( int row, void* ptr )
 *  -- will take in row, then from ptr -> we will take in width and height of that ui element and calculate
 *  -- and return the integer for x coordinate
 *  -- I would have definitely done it in another way, if only I knew I would be making a grid
 * */
int xx_x_grid ( int row, xx_grid* i_grid, void* ptr ) {
  // curr_x
  int r_value = i_grid -> arr[2];

  // calculations
  r_value -> arr[2] = 

  return r_value;
}

