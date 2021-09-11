#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "vehicle.h"
#include "vector.h"
#include "engine.h"

Vehicle *Vehicle_Create() {
  Vehicle *self = (Vehicle *) malloc(sizeof *self);
  if (!self) {
    fprintf(stderr, "Failed to allocate memory for Vehicle\n");
  }
  float x = rand() * (float) WIDTH / (float) RAND_MAX;
  float y = rand() * (float) HEIGHT / (float) RAND_MAX;
  self->loc = Vector_CreateXY(x, y);

  float vx = rand() * 3.0f / (float) RAND_MAX;
  if (rand() % 2) vx *= -1.0f;
  float vy = rand() * 3.0f / (float) RAND_MAX;
  if (rand() % 2) vy *= -1.0f;
  self->vel = Vector_CreateXY(vx, vy);

  self->acc = Vector_ZERO();

  self->maxSpeed = 3.0f + rand() * 2.0f / (float) RAND_MAX;
  self->maxForce = 0.1f + rand() * 0.05f / (float) RAND_MAX;
  return self;
}

void Vehicle_Destroy(Vehicle *self) {
  Vector_Destroy(self->loc);
  Vector_Destroy(self->vel);
  Vector_Destroy(self->acc);
  free(self);
}

void Vehicle_Render(Vehicle *self, SDL_Renderer *renderer, SDL_Texture *vehicle_img) {
  static SDL_FPoint center;
  static SDL_FRect dstrect = {.w = 55.0f, .h = 25.0f};

  center.x = dstrect.w/2.0f;
  center.y = dstrect.h/2.0f;

  dstrect.x = self->loc->x - center.x;
  dstrect.y = self->loc->y - center.y;

  double angle = Vector_Dir(self->vel) * 180 / M_PI;

  if (SDL_RenderCopyExF(renderer, vehicle_img, NULL, &dstrect, angle, &center, SDL_FLIP_NONE) == -1) {
    __PRINT_ERROR__("Drawing the vehicle with SDL_RenderCopyEx");
  }
}

void Vehicle_Update(Vehicle *self) {
  Vector_Add(self->vel, self->vel, self->acc);
  Vector_Truncate(self->vel, self->vel, self->maxSpeed);

  Vector_Add(self->loc, self->loc, self->vel);
  Vector_Mult(self->acc, self->acc, 0.0f);

  // Make sure the vehicle stays in the window
  if (self->loc->x > (float) WIDTH) self->loc->x = 0.0f;
  else if (self->loc->x < 0.0f) self->loc->x = (float) WIDTH;
  if (self->loc->y > (float) HEIGHT) self->loc->y = 0.0f;
  else if (self->loc->y < 0.0f) self->loc->y = (float) HEIGHT;
}

void Vehicle_ApplyForce(Vehicle *self, Vector *force) {
  Vector_Add(self->acc, self->acc, force);
}


