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
  static Vehicle *vehicle;
  static SDL_Texture *vehicle_img;

  // setup part
  static bool __run_setup__ = true;
  if (__run_setup__) {
    setup(renderer, &vehicle, &vehicle_img, &mouse, &force);
    __run_setup__ = false;
  }

  // handle event
  if (event_handler()) {
    clean_up(vehicle, vehicle_img, mouse);
    #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    #else
    __quit_window__ = true;
    return;
    #endif
  }

  // update and draw
  update(vehicle, mouse, force);
  draw(renderer, vehicle, vehicle_img);
  SDL_Delay(1000 / FPS);
  SDL_RenderPresent(renderer);
}


