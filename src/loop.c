#include <SDL2/SDL.h>
#include "engine.h"

#include "vector.h"
#include "vehicle.h"

void draw(SDL_Renderer *renderer, Vehicle *vehicle, SDL_Texture *vehicle_img, Vector *mouse) {
  if (SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255) == -1)
    __PRINT_ERROR__("Setting the background color with SDL_SetRenderDrawColor");
  if (SDL_RenderClear(renderer) == -1)
    __PRINT_ERROR__("Clearing the window for background with SDL_RenderClear");


  if (SDL_SetRenderDrawColor(renderer, 200, 0, 200, 255) == -1)
    __PRINT_ERROR__("Setting the mouse color with SDL_SetRenderDrawColor");
  static SDL_FRect mouse_rect = {.w=30, .h = 30};
  mouse_rect.x = mouse->x - mouse_rect.w/2.0f;
  mouse_rect.y = mouse->y - mouse_rect.h/2.0f;
  if (SDL_RenderFillRectF(renderer, &mouse_rect)==-1)
    __PRINT_ERROR__("Drawing the mouse with SDL_RenderFillRectF");

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
