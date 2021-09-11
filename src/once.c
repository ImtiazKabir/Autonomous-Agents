#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "engine.h"
#include "vector.h"
#include "vehicle.h"

void setup(
  SDL_Renderer *renderer,
  Vehicle **vehicle,
  SDL_Texture **vehicle_img,
  Vector **mouse,
  Vector **force) {

  // create the vehicle
  *vehicle = Vehicle_Create(55.0f, 25.0f, 2.0f, 1.0f);

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



void clean_up(Vehicle *vehicle, SDL_Texture *vehicle_img, Vector *mouse) {
  Vehicle_Destroy(vehicle);
  SDL_DestroyTexture(vehicle_img);
  Vector_Destroy(mouse);
}
