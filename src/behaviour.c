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
