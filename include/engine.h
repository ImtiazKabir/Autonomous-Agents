#ifndef D07D45CE_AA78_4D49_B29A_EBD0B6BCD4AD
#define D07D45CE_AA78_4D49_B29A_EBD0B6BCD4AD

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "internal_stuff.h"

#include "vector.h"
#include "vehicle.h"

#define TITLE_OF_WINDOW "Autonomous Agent"
#define WIDTH (int)800
#define HEIGHT (int)500
#define FPS (uint32_t)60

void main_loop(void *v_renderer);
bool event_handler();

void setup(
  SDL_Renderer *renderer,
  Vehicle **vehicle,
  SDL_Texture **vehicle_img,
  Vector **mouse,
  Vector **force);

void update(Vehicle *vehicle, Vector *mouse, Vector *force);
void draw(SDL_Renderer *renderer, Vehicle *vehicle, SDL_Texture *vehicle_img);
void clean_up(Vehicle *vehicle, SDL_Texture *vehicle_img, Vector *mouse);

#endif /* D07D45CE_AA78_4D49_B29A_EBD0B6BCD4AD */
