#include <SDL2/SDL.h>
#include "engine.h"

#include "vector.h"
#include "vehicle.h"

void draw(SDL_Renderer *renderer, Vehicle *vehicle, SDL_Texture *vehicle_img) {
  if (SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255) == -1)
    __PRINT_ERROR__("Setting the background color with SDL_SetRenderDrawColor");
  if (SDL_RenderClear(renderer) == -1)
    __PRINT_ERROR__("Clearing the window for background with SDL_RenderClear");


  Vehicle_Render(vehicle, renderer, vehicle_img);
}


void update(Vehicle *vehicle, Vector *mouse, Vector *force) {
  int mx, my;
  SDL_GetMouseState(&mx, &my);
  mouse->x = (float) mx;
  mouse->y = (float) my;

  Vehicle_ApplyForce(vehicle, Vehicle_Seek(vehicle, force, mouse));
  // Vehicle_Flee(vehicle, vehicle->acc, mouse);
  Vehicle_Update(vehicle);
}
