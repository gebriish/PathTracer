#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "utils.h"

class vec3 {
public:
    float e[3];

    vec3() 
        : e{0, 0, 0}
    {}

    vec3(float v)
    : e{v,v,v}
    {}

    vec3(float e0, float e1, float e2) : 
    e{e0, e1, e2}
    {}

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float &operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator-=(const vec3& v) {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }

    vec3& operator*=(float t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator*=(const vec3& v) {
        e[0] *= v.x();
        e[1] *= v.y();
        e[2] *= v.z();
        return *this;
    }

    vec3& operator/=(float t) {
        return *this *= 1/t;
    }

    float length() const {
        return sqrt(length_squared());
    }

    float length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    bool near_zero() const {
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }

        static vec3 random() {
        return vec3(random_float(), random_float(), random_float());
    }

    static vec3 random(float min, float max) {
        return vec3(random_float(min,max), random_float(min,max), random_float(min,max));
    }

};

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(float t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, float t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, float t) {
    return (1/t) * v;
}

inline float dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 normalize(const vec3& v) {
    return v / v.length();
}

inline vec3 reflect(const vec3& r, const vec3& normal) {
    float c = dot(r, normal);
    return r - 2.0 * c * normal;
}

inline vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

inline vec3 random_in_unit_sphere()
{
    while (true)
    {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
}

inline vec3 random_unit_vector()
{
    return normalize(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3 &normal)
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

#endif
