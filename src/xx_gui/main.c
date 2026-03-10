#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include "./xx_string.h"
#include "./bm_mgr.h"
#include "./xx_window_manager.h"
#include "./xx_check_box.h"
#include "./xx_radio_button.h"
#include "./xx_grid.h"

void move_to_left ( xx_grid* i_grid ) {
  for (int i = 0; i < i_grid -> unit_n; i++) {
    i_grid -> unit_info [i].x -= 5;
  }
}
void move_to_right ( xx_grid* i_grid ) {
  for (int i = 0; i < i_grid -> unit_n; i++) {
    i_grid -> unit_info [i].x += 5;
  }
}

int main ( int argc, char** argv ) {

  SDL_Init (SDL_INIT_VIDEO);
  IMG_Init ( IMG_INIT_PNG );

  xx_window_manager* window = xx_create_window_renderer ( SCREEN_WIDTH, SCREEN_HEIGHT, (char*) "Testing Check Box" );
  bm_mgr* font = bm_create ();
  bm_set_zoom ( font, -4 );
  bm_load ( window -> renderer, font, (char*) "./font1.png" );

  xx_grid* g = xx_create_grid ( SCREEN_WIDTH, SCREEN_HEIGHT, 10 );

  xx_check_box* chk1 = xx_create_check_box ( font, 5, 30 );
  xx_radio_button* r1 = xx_create_radio_button ( font, 5, 30 );

  xx_add_check_box_element ( chk1, (char*) "Message1" );
  xx_add_check_box_element ( chk1, (char*) "Message -2 ");
  xx_add_check_box_element ( chk1, (char*) "Message Third");

  xx_add_radio_button ( r1, (char*) "Something Off" );
  xx_add_radio_button ( r1, (char*) "Nothing is Here" );
  xx_add_radio_button ( r1, (char*) "Message - 3" );
  xx_add_radio_button ( r1, (char*) "Shit is real" );

  char string_array [2][30] = {"CheckBox Buttons", "Radio Buttons"};
  char string1 [] = "xx_window_manager* window = xx_create_window_renderer ( SCREEN_Width, Screen_Height, (char*) \"This is nothing\" );";

  xx_add_to_grid ( g, 0, bm_get_total_width ( font, string_array[0] ), bm_get_total_height ( font, string_array [0] ));
  xx_add_to_grid ( g, 1, xx_get_check_box_total_width ( chk1 ), xx_get_check_box_total_height ( chk1 ) );
  xx_add_to_grid ( g, 2, bm_get_total_width ( font, string_array[1] ), bm_get_total_height ( font, string_array [1] ));
  xx_add_to_grid ( g, 3, xx_get_radio_button_total_width ( r1 ), xx_get_radio_button_total_height ( r1 ) );

  xx_add_to_grid ( g, 1, bm_get_total_width ( font, string1 ), bm_get_total_height ( font, string1 ) );
  

  SDL_Event e;
  int quit = 0;

  while (!quit) {
    while (SDL_PollEvent (&e)) {
      if (e.type == SDL_QUIT) {
        quit = 1;
      }
      xx_listen_radio_button ( r1, e );
      xx_listen_check_box ( chk1, e );

      if ( e.type == SDL_KEYDOWN ) {
        switch (e.key.keysym.sym) {
          case SDLK_DOWN:
            move_to_left (g);
            break;
          case SDLK_UP:
            move_to_right ( g );
            break;
        }
      }
    }
    SDL_SetRenderDrawColor ( window -> renderer, 255, 255, 255, 255 );
    SDL_RenderClear ( window -> renderer );

    xx_render_check_box ( window -> renderer, chk1, font, xx_get_x ( g, 1 ), xx_get_y ( g, 1 ) );
    xx_render_radio_button ( window -> renderer, r1, font, xx_get_x ( g, 3 ), xx_get_y ( g, 3 ) );
    bm_set_color ( font, 255, 0, 0 );
    bm_render ( window -> renderer, font, string_array[0], xx_get_x ( g, 0 ), xx_get_y ( g, 0 ) );
    bm_render ( window -> renderer, font, string_array[1], xx_get_x ( g, 2 ), xx_get_y ( g, 2 ) );

    bm_set_color ( font, 0, 255, 100 );
    bm_render_advanced ( window -> renderer, font, string1, xx_get_x (g, 4), xx_get_y (g, 4), SCREEN_WIDTH );
    SDL_RenderPresent ( window -> renderer );
  }

  xx_free_radio_button ( r1 );
  xx_free_check_box ( chk1 );
  xx_free_grid ( g );
  bm_free ( font );
  xx_destroy_window_renderer ( window );
  IMG_Quit ();
  SDL_Quit ();

  return 0;
}
