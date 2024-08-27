#ifndef RAY_H
#define RAY_H


#include "vec3.h"

struct Ray {
    vec3 Origin;
    vec3 Direction;

    vec3 at(double t) const {
        return Origin + Direction * t;
    }
};

#endif
