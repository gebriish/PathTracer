#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

struct Material {
    vec3 base_color{1.0};
    float roughness = 0.5f;
    bool glass = false;
    float refractive_index = 1.33f;
};

#endif