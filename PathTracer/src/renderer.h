#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "scene.h"



class Renderer {
public:
    struct {
        unsigned int Samples = 20;
        unsigned int Depth   = 8;
    } Settings;

public:
    void onRender(Camera& camera, Scene& scene);

private:
    void writeColor(unsigned char* img,const vec3& color, unsigned int pixel_index);

    vec3 getRayColor(const Ray& r, int depth, Scene& scene);
    vec3 sample_square() const ;
};

#endif
