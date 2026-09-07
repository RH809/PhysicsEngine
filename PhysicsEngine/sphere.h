#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

#define NUM_STACKS (20)
#define NUM_SLICES (20)
#define DEFAULT_RADIUS (0.5f)

class Sphere : public Object {
private:
	float radius;
public:
	Sphere(float _x, float _y, float _z, glm::quat _r, float _m, float _s);
};
#endif