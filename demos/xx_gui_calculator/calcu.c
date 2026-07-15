/* 
 * so this will be the gui calculator using my own xx_gui created in SDL2
 * for naming things, I'm not so good, so the program functions are named like xv_function_name
 * */
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

// all the constants that I'm using on this program, could be transported to an external file like a settings file
enum Calc_Info {
  BUTTON_WIDTH = 20,
  BUTTON_HEIGHT = 20,

  BUTTON_COUNT = 18,

  INPUT_WIDTH = 120,
  INPUT_HEIGHT = 20,

  FONT_WIDTH = 20,

  SCREEN_WIDTH = 230,
  SCREEN_HEIGHT = 330,

  MAX_STRING_SIZE = 200,
  MAX_INPUT_SIZE = 20,
  GRID_ITEM_COUNT = 19
};

// header files from xx_gui
#include "../../src/xx_gui/xx_string.h"
#include "../../src/xx_gui/xx_window_manager.h"
#include "../../src/xx_gui/bm_mgr.h"
#include "../../src/xx_gui/xx_grid.h"
#include "../../src/xx_gui/xx_button_text.h"
#include "../../src/xx_gui/xx_label.h"

struct Bundle {

  // for rendering everything
  bm_mgr* font;

  // for window and renderer
  xx_window_manager* window;

  // for storing input information 
  size_t string_size;
  char* input1;
  char* input2;
  char* answer_store;

  // for buttons and button count (button-text)
  size_t btn_count;
  xx_button_text** btns;

  // for input
  xx_label* screen;
  
  // for grid
  xx_grid* grid;

  float result; // to store the result
  float a;
  float b;
  int prev_code; // to store if the previous was add, mul, sub, div
};

// function declarations
// functions to initialize libraries
int xv_init_lib (); // this function initializes SDL and SDl_image
void xv_quit_lib (); // this function will call SDL_Quit () and IMG_Quit

struct Bundle* xv_init_bundle (); // this function will initialize struct Bundle
void xv_free_bundle ( struct Bundle* bun ); // this function will free everything that the xv_init_bundle had allocated

int xv_event_function ( struct Bundle* bun ); // this is the main loop function
int xv_put_to_grid ( struct Bundle* bun ); // this function will put / load to the grid

void xv_transfer_string ( struct Bundle* bun, char* ch_string ); // this function will take the buttons input and string together the input 
                                                // while also 
                                                // -- checking for '+', '-', '*', '/', '=' and working acccordingly
                                                // -- transfer value of input1 to input2, 
                                                // -- also storing the answer only if '=' is pressed
void xv_free_string ( struct Bundle* bun );

// this is the message for the button - so that I don't have to manually update each character
char btn_msg [GRID_ITEM_COUNT][5] = {
  "1\0", "2\0", "3\0", "4\0", "5\0", "6\0", "7\0", "8\0", "9\0", "0\0",
  "+\0", "-\0", "*\0", "/\0", "=\0", "Ans\0", ".\0", "C\0"
};

// function main
/* 
 * init main (int, char**);
 *  -- only calls in other functions
 * */
int main ( int argc, char** argv ) {
  if (!xv_init_lib () ) {
    fprintf (stdout, "Error! xv_init_lib () \n");
    return 0;
  }

  struct Bundle* bun = xv_init_bundle ();
  if ( bun == NULL ) {
    fprintf (stdout, "Error! xv_init_bundle () \n");
    return 0;
  }

  if (!xv_put_to_grid ( bun )) {
    fprintf (stdout, "Error! xv_put_to_grid (bun)\n");
    return 0;
  }

  if (!xv_event_function ( bun )) {
    fprintf (stdout, "Error! xv_event_Function (bun)\n");
    return 0;
  }

  xv_free_bundle (bun);
  xv_quit_lib ();

  return 0;
}


// all the functions definitions
/* 
 * init xv_init_lib ()
 *  -- will initialize sdl and sdl_image 
 *  -- returns 0 on failure and 1 on success
 * */
int xv_init_lib () {
  if ( SDL_Init (SDL_INIT_VIDEO) < 0) {
    fprintf (stderr, "Could not initialize SDL -> %s\n", SDL_GetError ());
    return 0;
  }
  if ( IMG_Init ( IMG_INIT_PNG ) < 0 ) {
    fprintf (stderr, "Could not initialize SDL_image -> %s\n", IMG_GetError ());
    return 0;
  }

  return 1;
}

/* 
 * void xv_quit_lib ()
 *   -- will quit sdl_image and sdl
 * */
void xv_quit_lib () {
  IMG_Quit ();
  SDL_Quit ();
}

/* 
 * struct Bundle* xv_init_bundle ()
 *  -- will create, allocate necessary memory and return the pointer to bundle struct
 * */
struct Bundle* xv_init_bundle () {
  // allocating memory to the bundle manager 
  struct Bundle* bun = (struct Bundle*) calloc (sizeof(struct Bundle), 1);
  if ( bun == NULL ) {
    fprintf (stderr, "Could not allocate memory - struct Bundle* bun\n");
    return NULL;
  }

  // creating window
  bun -> window = xx_create_window_renderer ( SCREEN_WIDTH, SCREEN_HEIGHT, (char*) "Calculator" );
  bun -> result = 0;

  // for font
  bun -> font = bm_create ();
  bm_set_zoom ( bun -> font, 8 );
  bm_load ( bun -> window -> renderer, bun -> font, (char*) "../../src/xx_gui/font1.png" );


  bun -> btn_count = BUTTON_COUNT;
  bun -> btns = (xx_button_text**) calloc (sizeof(xx_button_text*), BUTTON_COUNT);
  if ( bun -> btns == NULL) {
    fprintf (stderr, "Could not allcate memory - bun -> xx_button_text** btns \n");
    return NULL;
  } else {
    for ( int i = 0; i < bun -> btn_count; i++ ) {
      bun -> btns[i] = xx_create_button_text (bun -> font, btn_msg[i]);
      if ( bun -> btns[i] == NULL) {
        fprintf (stderr, "Could not allocate memory to - bun -> btns [%d] \n", i);
      }
    }
  }

  // for input and user_input
  bun -> screen = xx_create_label ( bun -> font, -1, MAX_STRING_SIZE, "\0" );
  if ( bun -> screen == NULL ) {
    fprintf (stderr, "Error! Could not allocate memory - xx_label*\n");
    return NULL;
  }

  // initializing string for input, input2 and answer
  bun -> string_size = MAX_INPUT_SIZE;
  bun -> input1 = (char*) calloc (sizeof(char), bun -> string_size);
  bun -> input2 = (char*) calloc (sizeof(char), bun -> string_size);
  bun -> answer_store = (char*) calloc (sizeof(char), bun -> string_size);;

  // initializing xx_grid
  bun -> grid = xx_create_grid (SCREEN_WIDTH, SCREEN_HEIGHT, 10, GRID_ITEM_COUNT);

  return bun;
}

/* 
 * void xv_free_bundle ( struct Bundle* bun )
 *  -- will free everything of the bundle manager
 * */
void xv_free_bundle ( struct Bundle* bun ) {
  // freeing the xx_input
  if ( bun -> screen != NULL ) {
    xx_free_label ( bun -> screen );
    bun -> screen = NULL;
  }

  // freeing all the buttons
  for ( int i = 0; i < BUTTON_COUNT; i++ ) {
    xx_free_button_text ( bun -> btns[i] );
    bun -> btns [i] = NULL;
  }

  // freeing the main pointer to xx_button_text
  if ( bun -> btns != NULL ) {
    free ( bun -> btns );
    bun -> btns = NULL;
  }

  // freeing bm manager or font
  if ( bun -> font != NULL ) {
    bm_free ( bun -> font );
    bun -> font = NULL;
  }

  // freeing window and renderer
  if ( bun -> window != NULL) {
    xx_destroy_window_renderer ( bun -> window );
    bun -> window = NULL;
  }

  // freeing grid
  if ( bun -> grid != NULL ) {
    xx_free_grid ( bun -> grid );
    bun -> grid = NULL;
  }

  // freeing the strings, input1, input2, answer_store
  if ( bun -> input1 != NULL ) {
    free ( bun -> input1 );
    bun -> input1 = NULL;
  }

  if ( bun -> input2 != NULL ) {
    free ( bun -> input2 );
    bun -> input2 = NULL;
  }

  if ( bun -> answer_store != NULL ) {
    free ( bun -> answer_store );
    bun -> answer_store = NULL;
  }

  // freeing the bundle manager itself
  if ( bun != NULL) {
    free (bun);
    bun = NULL;
  }
}

/* 
 * int xv_event_function ( struct Bundle* bun )
 *  -- will have the main loop
 *  -- will listen to inputs and work on it 
 *  -- will return 1 on success (there is no reason for a failure)
 * */
int xv_event_function ( struct Bundle* bun ) {
  SDL_Event e;
  int quit = 0;

  while (!quit) {
    while (SDL_PollEvent (&e)) {
      if (e.type == SDL_QUIT) {
        quit = 1;
      }
      for ( int i = 0; i < bun -> btn_count; i++ ) {
        // when that certain button is pressed what we will do
        if (xx_button_text_listen ( bun -> btns[i], e ) == 1) {
          // button is pressed
          // call a function 
          xv_transfer_string ( bun, bun -> btns[i] -> btn_text );
        }
      }
    }
    SDL_SetRenderDrawColor ( bun -> window -> renderer, 255, 255, 255, 255 );
    SDL_RenderClear ( bun -> window -> renderer);

    // rendering the buttons and the input
    //xx_render_input ( bun -> window -> renderer, bun -> screen, bun -> font, xx_get_x ( bun -> grid, 0 ), xx_get_y ( bun -> grid, 0 ) );
    xx_render_label ( bun -> window -> renderer, bun -> screen, bun -> font, xx_get_x ( bun -> grid, 0 ), xx_get_y ( bun -> grid, 0 ) );
    for ( int i = 0; i < bun -> btn_count; i++ ) {
      xx_render_button_text ( bun -> window -> renderer, bun -> btns[i], bun -> font, xx_get_x ( bun -> grid, i + 1 ), xx_get_y ( bun -> grid, i + 1 ) );
    }

    SDL_RenderPresent ( bun -> window -> renderer );
  }

  return 1;
}

/* 
 * int xv_put_to_grid ( struct Bundle* bun )
 *  -- will add / record all the items (xx_input and xx_button_text * 16) to the grid 
 *  -- will return 1 on success and 0 on failure
 *  -- will automatically update row based on '4'
 * */
int xv_put_to_grid ( struct Bundle* bun ) {
  xx_add_to_grid ( bun -> grid, 0, xx_get_label_total_width ( bun -> screen ), xx_get_label_total_height ( bun -> screen ) );

  int row = 1;
  int counter = 0;
  // adding the buttons
  for ( int i = 0; i < bun -> btn_count; i++) {

    xx_add_to_grid ( bun -> grid, row, xx_get_button_total_width ( bun -> btns [i] ), xx_get_button_total_height ( bun -> btns[i] ) );
    counter += 1;

    if ( counter > 3 ) {
      row += 1;
      counter = 0;
    }
  }
  return 1;
}

void xv_transfer_string ( struct Bundle* bun, char* ch_string ) {
  // addition
  if ( xx_strcmpi ( ch_string, btn_msg[10] ) == 0 ) {
    bun -> a = strtof ( bun -> input1, NULL );
    bun -> b = strtof ( bun -> input2, NULL );


    bun -> result = bun -> a + bun -> b;
    // copying the result to input2, while clearing input1
    snprintf ( bun -> input2, bun -> string_size, "%.2f", bun -> result );
    // copying the message to the screen buffer to be displayed
    xx_set_label_message ( bun -> screen, bun -> string_size, bun -> input2);
    // cleaning input1
    xv_free_string (bun);
    bun -> prev_code = 11;
  }
  // subtraction
  else if ( xx_strcmpi ( ch_string, btn_msg[11] ) == 0 ) {
    bun -> a = strtof ( bun -> input1, NULL );
    bun -> b = strtof ( bun -> input2, NULL );
    bun -> result = bun -> b - bun -> a;
    snprintf ( bun -> input2, bun -> string_size, "%.2f", bun -> result );
    xx_set_label_message ( bun -> screen, bun -> string_size, bun -> input2 );
    xv_free_string ( bun );
    bun -> prev_code = 12;
  }
  // multiplication
  else if ( xx_strcmpi ( ch_string, btn_msg[12] ) == 0 ) {
    snprintf (bun -> input2, bun -> string_size, "%s", bun -> input1);
    bun -> b = strtof ( bun -> input2, NULL );
    xv_free_string ( bun );
    bun -> prev_code = 13;
  }
  // division
  else if ( xx_strcmpi ( ch_string, btn_msg[13] ) == 0 ) {
    snprintf ( bun -> input2, bun -> string_size, "%s", bun -> input1);
    bun -> b = strtof ( bun -> input2, NULL );
    xv_free_string ( bun );
    bun -> prev_code = 14;
  }
  // equals
  else if ( xx_strcmpi ( ch_string, btn_msg[14] ) == 0 ) {
    // checking the code
    if ( bun -> prev_code == 11 ) {

      bun -> a = strtof ( bun -> input1, NULL );
      bun -> b = strtof ( bun -> input2, NULL );

      bun -> result = bun -> a + bun -> b;
      // copying the result to input2, while clearing input1
      snprintf ( bun -> input2, bun -> string_size, "%.2f", bun -> result );
      // copying the message to the screen buffer to be displayed
      xx_set_label_message ( bun -> screen, bun -> string_size, bun -> input2);
      // cleaning input1
      xv_free_string (bun);
    } else if ( bun -> prev_code == 12 ) {
      bun -> a = strtof ( bun -> input1, NULL );
      bun -> b = strtof ( bun -> input2, NULL );
      bun -> result = bun -> b - bun -> a;
      snprintf ( bun -> input2, bun -> string_size, "%.2f", bun -> result );
      xx_set_label_message ( bun -> screen, bun -> string_size, bun -> input2 );
      xv_free_string ( bun );
    }
    else if ( bun -> prev_code == 13 ) {
      bun -> a = strtof ( bun -> input1, NULL );
      // b = strtof ( bun -> input2, NULL );

      bun -> result = bun -> a * bun -> b;

      snprintf ( bun -> input2, bun -> string_size, "%.2f", bun -> result );
      xx_set_label_message ( bun -> screen, bun -> string_size, bun -> input2 );
      xv_free_string ( bun );
    }
    else if ( bun -> prev_code == 14 ) {

      bun -> a = strtof ( bun -> input1, NULL );
      bun -> b = strtof ( bun -> input2, NULL );
      if ( bun -> a == 0.0f || bun -> a == 0 ) {
        xx_set_label_message ( bun -> screen, bun -> string_size, (char*) "Divider '0'" ) ;
      }
      else {
        bun -> result = bun -> b / bun -> a;

        snprintf ( bun -> input2, bun -> string_size, "%.2f", bun -> result );
        xx_set_label_message ( bun -> screen, bun -> string_size, bun -> input2 );
      }

    }
    snprintf ( bun -> answer_store, bun -> string_size, "%s", bun -> input2  ); // storing answer to the answer button 
  } else if( xx_strcmpi (ch_string, btn_msg[15]) == 0 ) {
    // answer - previous answer
    snprintf ( bun -> input1, bun -> string_size, "%s", bun -> answer_store );
    xx_set_label_message ( bun -> screen, bun -> string_size, bun -> input1 );
  } else if ( xx_strcmpi (ch_string, btn_msg[17]) == 0) {
    // clear
    xv_free_string (bun);
    memset ( bun -> input2, 0, bun -> string_size );
    xx_set_label_message ( bun -> screen, bun -> string_size, bun -> input1 );
    bun -> a = 0.0f;
    bun -> b = 0.0f;
  } else {
    // store the strings to the bun -> input1 and show it
    xx_push_back ( bun -> input1, ch_string[0] );
    xx_set_label_message ( bun -> screen, bun -> string_size, bun -> input1 );
  }
}

void xv_free_string ( struct Bundle* bun ) {
  memset ( bun -> input1, 0, bun -> string_size );
  bun -> result = 0.0f;
}
