/* 
 * this file is compiled using -lSDL2main -lSDL2 -lSDL2_image
 * */
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../xx_string.h"
#include "../xx_window_manager.h"
#include "../xx_panel.h"
#include "../bm_mgr.h"
#include "../xx_button.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main ( int argc, char** argv ) {
  SDL_Init ( SDL_INIT_VIDEO );
  IMG_Init ( IMG_INIT_PNG );

  xx_window_manager* window1 = xx_create_window_renderer ( SCREEN_WIDTH, SCREEN_HEIGHT, (char*) "Window"  );
  bm_mgr* font1 = bm_create ();
  bm_load ( window1 -> renderer, font1, (char*) "./font1.png" );
  xx_panel* pan = xx_create_panel ( SCREEN_WIDTH, SCREEN_HEIGHT );
  bm_set_color ( font1, 0, 0, 0 );

  bm_mgr* font2 = bm_create ();
  bm_load ( window1 -> renderer, font2, (char*) "./font1.png" );
  bm_set_color ( font2, 0, 255, 0);

  bm_render ( window1 -> renderer, font1, (char*) "This is nothing", 0, 0 );
  bm_render ( window1 -> renderer, font2, (char*) "work1", 0, 0 );

  xx_button* btn1 = xx_create_button_text ( font1, (char*) "Submit Query!" );


  SDL_Event e;
  int quit = 0;
  while (!quit) {
    while (SDL_PollEvent (&e)) {
      if (e.type == SDL_QUIT) {
        quit = 1;
      }
      xx_button_listen ( window1 -> renderer, btn1, e );
    }

    SDL_SetRenderDrawColor ( window1 -> renderer, 255, 255, 255, 255 );
    SDL_RenderClear ( window1 -> renderer );

    bm_render ( window1 -> renderer, font1, (char*) "This is nothing",
        xx_x_panel ( pan, 0, bm_get_total_width ( font1 ) ),
        xx_y_panel ( pan, 0, bm_get_total_height ( font1 ) )
        );

    bm_render ( window1 -> renderer, font2, (char*) "work1",
        xx_x_panel ( pan, 1, bm_get_total_width ( font2 ) ),
        xx_y_panel ( pan, 0, bm_get_total_height ( font2 ) )
        );

    xx_render_button_text ( window1 -> renderer, btn1, font1, 
        xx_x_panel ( pan, 0, xx_get_button_total_width ( btn1 ) ),
        xx_y_panel ( pan, 1, xx_get_button_total_height ( btn1 ) )
        );

    xx_render_button_text ( window1 -> renderer, btn1, font1, 
        xx_x_panel ( pan, 1, xx_get_button_total_width ( btn1 ) ),
        xx_y_panel ( pan, 1, xx_get_button_total_height ( btn1 ) )
        );

    xx_render_button_text ( window1 -> renderer, btn1, font1, 
        xx_x_panel ( pan, 2, xx_get_button_total_width ( btn1 ) ),
        xx_y_panel ( pan, 0, xx_get_button_total_height ( btn1 ) )
        );


    SDL_RenderPresent ( window1 -> renderer );
    SDL_Delay ( 16 );
  }

  xx_free_button_text ( btn1 );
  xx_free_panel ( pan );
  bm_free ( font2 );
  bm_free ( font1 );
  xx_destroy_window_renderer ( window1 );

  IMG_Quit ();
  SDL_Quit ();

  return 0;

}
