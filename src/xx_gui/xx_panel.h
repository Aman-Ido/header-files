/* 
 * actually I wanted to make xx_grid, where I can make a grid system, but it is kind of becoming a headache. 
 * Thus this will be like the xx_grid, but in beta version where I can try all the things
 * */

typedef struct {
  int ro;
  int co;
} xx_panel_part; //they are row and column
              

typedef struct {
  int SCREEN_WIDTH;
  int SCREEN_HEIGHT;

  int info_n; // default - 2;
  xx_panel_part* info;

  /* 
   * info will have information like available row and column values, along with 
   * */
  int pointer_n; // default - 2;
  SDL_Point* pointer;// this iwll hav ethe information of available x, y, (we will be returning pointer ->x, and pointer -> y);
                     // 0 -> will be the available x, y
                     // 1 -> will be the padding infornation ( default -> 5, each );
  SDL_Rect* data;
  int data_n; // default - 20;
} xx_panel;


/* 
 * function -  declarations
 * */
xx_panel* xx_create_panel ( int SCREEN_WIDTH, int SCREEN_HEIGHT );
void xx_set_default_value_panel ( xx_panel* i_panel );
void xx_free_panel ( xx_panel* i_panel );

int xx_y_panel ( xx_panel* i_panel, int col, int total_height  );
int xx_x_panel ( xx_panel* i_panel, int row, int total_width  );


/* 
 * function - definitions
 *
 * */

/* 
 * function - xx_panel* xx_create_panel ( int SCREEN_WIDTH, int SCREEN_HEIGHT );
 *    -- this will allocate memory and return  the pointer
 * */
xx_panel* xx_create_panel ( int SCREEN_WIDTH, int SCREEN_HEIGHT ) {
  xx_panel* r_panel = (xx_panel*) malloc (sizeof(xx_panel) * 1);
  if ( r_panel == NULL ) {
    printf ("\t Error! Memory Allocation, Failed, xx_panel*\n");
    return NULL;
  }

  r_panel -> info_n = 2;
  r_panel -> pointer_n = 2;
  r_panel -> data_n = 20;

  r_panel -> SCREEN_WIDTH = SCREEN_WIDTH;
  r_panel -> SCREEN_HEIGHT = SCREEN_HEIGHT;

  r_panel -> pointer = ( SDL_Point* ) malloc (sizeof(SDL_Point) * r_panel -> pointer_n);
  if ( r_panel -> pointer == NULL ) {
    printf ("\t Error! Memory Allocation, Failed, xx_panel* -> SDL_Point* pointer\n");
    return NULL;
  }


  r_panel -> info = ( xx_panel_part* ) malloc (sizeof(xx_panel_part) * r_panel -> info_n);
  if ( r_panel -> info == NULL ) {
    printf ("\t Error! Memory Allocation, Failed, xx_panel* -> xx_panel_part* info\n");
    return NULL;
  }

  r_panel -> data = ( SDL_Rect* ) malloc (sizeof(SDL_Rect) * r_panel -> data_n);
  if ( r_panel -> data == NULL ) {
    printf ("\t Error! Memory Allocation, Failed, xx_panel* -> SDL_Rect* data\n");
    return NULL;
  }


  xx_set_default_value_panel ( r_panel );

  return r_panel;
}

/* 
 * function - void xx_set_default_value_panel ();
 *    -- functioon to set the default values to members of the xx_panel
 * */
void xx_set_default_value_panel ( xx_panel* i_panel ) {

  i_panel -> pointer [1].x = 5;
  i_panel -> pointer [1].y = 5;

  i_panel -> pointer [0].x = i_panel -> pointer [1].x + 0;
  i_panel -> pointer [0].y = i_panel -> pointer [1].y + 0;

  i_panel -> info [0].ro = -1;
  i_panel -> info [0].co = -1;
  
}

/* 
 * function - void xx_free_panel ( xx_panel* i_panel );
 *    -- function to free everything of the panel
 * */
void xx_free_panel ( xx_panel* i_panel ) {
  if ( i_panel != NULL ) {
    free ( i_panel -> info );
    i_panel -> info = NULL;

    free ( i_panel -> pointer );
    i_panel -> pointer = NULL;

    free ( i_panel -> data );
    i_panel -> data = NULL;

    free ( i_panel );
    i_panel = NULL;

  }
}

/* 
 * function - int xx_set_px ( xx_panel* i_panel, int row, int total_width ); // sets the pointer and coordination then renders through token system
 *    -- this function will return the coordination of x that is available
 *    -- i will make total width and height fo every obj (like xx_input and everything)
 *    -- then I will calculate the width and height from here
 * */
int xx_x_panel ( xx_panel* i_panel, int row, int total_width ) {

  // if they are not equal (here -1 == 0)
  if ( row > i_panel -> info [0].ro ) {
    i_panel -> info [0].ro = row;
    i_panel -> data [ row ].x = i_panel -> pointer[0].x;
    i_panel -> pointer [0].x = i_panel -> pointer[0].x + total_width + i_panel -> pointer[1].x;
    i_panel -> data [ row ].w = total_width;
    /* printf ("%d, %d, %d, %d, %d \n",
        i_panel -> data [ row ].x,
        i_panel -> info [0].ro,
        i_panel -> pointer[0].x,
        i_panel -> data [ row ].w,
        total_width
        ); */
  }

  return i_panel -> data [ row ].x;
}

/* 
 * function - int xx_y_panel ( xx_panel* i_panel, int col, total_height  );
 *    -- function to return the available coordination of y
 * */
int xx_y_panel ( xx_panel* i_panel, int col, int total_height ) {

  // if they are not equal (here -1 == 0)
  if ( col > i_panel -> info [0].co ) {
    i_panel -> info [0].co = col;
    i_panel -> data [ col ].y = i_panel -> pointer[0].y;
    i_panel -> pointer [0].y = i_panel -> pointer[0].y + total_height + i_panel -> pointer [1].y;
    i_panel -> data [ col ].h = total_height;
  }

  return i_panel -> data [ col ].y;
}

