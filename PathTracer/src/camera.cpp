#include "camera.h"

void Camera::onResize(uint32_t x, uint32_t y) {
    m_Width  = x;
    m_Height = y;
}

void Camera::setFov(double fov) {
    m_Fov = fov;
}

vec3& Camera::position() { return m_Position; }
vec3& Camera::lookAt() { return m_LookAt; }
