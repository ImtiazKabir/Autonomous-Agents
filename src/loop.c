#include <SDL2/SDL.h>
#include <stdio.h>
#include "engine.h"

#include "vector.h"
#include "vehicle.h"
#include "stb/stb_ds.h"

void draw(
  SDL_Renderer *renderer,
  Vehicle **vehicle_arr,
  SDL_Texture *vehicle_img,
  Vector *mouse
) {

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

  for (int i = 0; i < (int) arrlen(vehicle_arr); ++i) {
    Vehicle_Render(vehicle_arr[i], renderer, vehicle_img);
  }
}


void update(Vehicle **vehicle_arr, Vector *mouse, Vector *force) {
  int mx, my;
  SDL_GetMouseState(&mx, &my);
  mouse->x = (float) mx;
  mouse->y = (float) my;

  // for (int i = 0; i < (int) arrlen(vehicle_arr); ++i) {
  //   Vehicle_ApplyForce(vehicle_arr[i], Vehicle_Arrive(vehicle_arr[i], force, mouse));
  //   Vehicle_Update(vehicle_arr[i]);
  // }

  Vehicle_Arrive(vehicle_arr[0], force, mouse);
  Vehicle_ApplyForce(vehicle_arr[0], force);

  Vehicle_Persue(vehicle_arr[1], force, vehicle_arr[0]);
  Vehicle_ApplyForce(vehicle_arr[1], force);

  Vehicle_Update(vehicle_arr[0]);
  Vehicle_Update(vehicle_arr[1]);
}
