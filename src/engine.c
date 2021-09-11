#define STB_RECT_PACK_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTTF_IMPLEMENTATION

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "engine.h"
#include "vector.h"
#include "vehicle.h"


void main_loop(void *v_renderer) {
  SDL_Renderer *renderer = (SDL_Renderer *)v_renderer;

  static Vector *mouse;
  static Vector *force;
  static Vehicle **vehicle_arr = NULL;
  static const int len = 100;
  static SDL_Texture *vehicle_img;

  // setup part
  static bool __run_setup__ = true;
  if (__run_setup__) {
    setup(renderer, &vehicle_arr, len, &vehicle_img, &mouse, &force);
    __run_setup__ = false;
  }

  // handle event
  if (event_handler()) {
    clean_up(vehicle_arr, vehicle_img, mouse, force);
    #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    #else
    __quit_window__ = true;
    return;
    #endif
  }

  // update and draw
  update(vehicle_arr, mouse, force);
  draw(renderer, vehicle_arr, vehicle_img, mouse);
  SDL_Delay(1000 / FPS);
  SDL_RenderPresent(renderer);
}


