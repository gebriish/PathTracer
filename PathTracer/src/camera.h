#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include <memory>

class Camera {
public:
    
    void onResize(uint32_t x, uint32_t y);
    void setFov(double fov);

    inline double getFov() const { return m_Fov; }

    inline uint32_t getWidth() const { return m_Width; }
    inline uint32_t getHeight() const { return m_Height; }

    vec3& position();
    vec3& lookAt();

private:
    double m_Fov = 60.0;
    vec3 m_Position{0.0,0.0,2.0};
    vec3 m_LookAt{0.0,0.0,0.0};
    uint32_t m_Width = 256, m_Height = 256;
};

#endif
