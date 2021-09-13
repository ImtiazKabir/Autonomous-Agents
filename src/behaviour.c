#include <math.h>
#include <stdio.h>

#include "vector.h"
#include "vehicle.h"

Vector *Vehicle_Seek(Vehicle *self, Vector *force, Vector *target) {
  Vector_Sub(force, target, self->loc);
  Vector_SetMag(force, force, self->maxSpeed);
  Vector_Sub(force, force, self->vel);
  Vector_Truncate(force, force, self->maxForce);
  return force;
}

Vector *Vehicle_Flee(Vehicle *self, Vector *force, Vector *target) {
  Vehicle_Seek(self, force, target);
  Vector_Negate(force, force);
  return force;
}

float map(float value, float low, float high, float mlow, float mhigh) {
  return low + (value - low) * (mhigh - mlow)/(high - low);
}

Vector *Vehicle_Arrive(Vehicle *self, Vector *force, Vector *target) {
  Vector_Sub(force, target, self->loc);
  const float d = Vector_SqMag(force);
  const float mn = 100 * 100;
  if (d < mn) {
    float m = map(d, 0, mn, 0, self->maxSpeed);
    Vector_SetMag(force, force, m);
  } else {
    Vector_SetMag(force, force, self->maxSpeed);
  }

  Vector_Sub(force, force, self->vel);
  Vector_Truncate(force, force, self->maxForce);
  return force;
}

Vector *Vehicle_Persue(Vehicle *self, Vector *force, Vehicle *target) {
  const float distance = Vector_Dist(self->loc, target->loc);
  if (distance > 0) {
    Vector_Sub(force, target->loc, self->loc);
    const float v = self->maxSpeed;
    const float perp = Vector_PerpProjection(target->vel, force);
    const float parr = Vector_ProjectionV(target->vel, force);

    const float lambda = v > perp? sqrtf(v*v - perp * perp) - parr/distance : 1.0f;
    Vector_Div(force, force, lambda);
    Vector_Add(force, target->vel, force);

    Vector_Sub(force, force, self->vel);
  } else {
    force->x = force->y = 0;
  }
  return force;
}

Vector *Vehicle_Evade(Vehicle *self, Vector *force, Vehicle *target) {
  Vehicle_Persue(self, force, target);
  Vector_Negate(force, force);
  return force;
}
