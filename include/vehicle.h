#ifndef B2FF7708_CECE_4780_A9BA_F6FC35A095D8
#define B2FF7708_CECE_4780_A9BA_F6FC35A095D8

#include <SDL2/SDL.h>
#include "vector.h"

typedef struct {
  Vector *loc;
  Vector *vel;
  Vector *acc;
  float maxSpeed;
  float maxForce;
} Vehicle;

Vehicle *Vehicle_Create(float x, float y, float vx, float vy);
void Vehicle_Destroy(Vehicle *self);

void Vehicle_Render(Vehicle *self, SDL_Renderer *renderer, SDL_Texture *vehicle_img);
void Vehicle_Update(Vehicle *self);
void Vehicle_ApplyForce(Vehicle *self, Vector *force);

Vector *Vehicle_Seek(Vehicle *self, Vector *force, Vector *target);
Vector *Vehicle_Flee(Vehicle *self, Vector *force, Vector *target);

#endif /* B2FF7708_CECE_4780_A9BA_F6FC35A095D8 */
