#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

#include "engine.h"
#include "vector.h"
#include "vehicle.h"

#define STB_DS_IMPLEMENTATION
#include "stb/stb_ds.h"

void setup(
  SDL_Renderer *renderer,
  Vehicle ***vehicle_arr,
  const int len,
  SDL_Texture **vehicle_img,
  Vector **mouse,
  Vector **force
) {

  srand(time(NULL));

  // create the vehicle
  for (int i = 0; i < len; ++i) {
    Vehicle *v = Vehicle_Create();
    arrput(*vehicle_arr, v);
  }

  char *path_to_vehicle_img = __get_path__("assets/vehicle.png");
  SDL_Surface *surface = IMG_Load(path_to_vehicle_img);
  if (!surface) __PRINT_ERROR__("Creating surface for vehicle with IMG_Load");
  *vehicle_img = SDL_CreateTextureFromSurface(renderer, surface);
  if (!*vehicle_img) __PRINT_ERROR__("Creating texture for vehicle with SDL_CreateTextureFromSurface");
  SDL_FreeSurface(surface);
  free(path_to_vehicle_img);

  *mouse = Vector_Create();
  *force = Vector_Create();
}



void clean_up(
  Vehicle **vehicle_arr,
  SDL_Texture *vehicle_img,
  Vector *mouse,
  Vector *force
) {

  for (int i = 0; i < (int) arrlen(vehicle_arr); ++i) {
    Vehicle_Destroy(vehicle_arr[i]);
  }
  arrfree(vehicle_arr);
  SDL_DestroyTexture(vehicle_img);
  Vector_Destroy(mouse);
  Vector_Destroy(force);
}
