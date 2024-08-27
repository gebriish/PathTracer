#ifndef SCENE_H
#define SCENE_H

#include "ray.h"
#include "material.h"

#include <memory>
#include <vector>

struct HitRecord {
    vec3 p;
    vec3 normal;
    double t;
    bool front_face;
    int material_index;

    void set_face_normal(const Ray& r, const vec3& outward_normal) {
        front_face = dot(r.Direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

};

class Hittable {
public:
    virtual ~Hittable() = default;  
    virtual bool hit(const Ray& r, double mint, double maxt, HitRecord& rec) const = 0;    
};

class Sphere: public Hittable {

public:
    Sphere(const vec3& c, double radius, uint32_t material)
    : m_Center(c), m_Radius(radius), m_MaterialIndex(material) {}

    bool hit(const Ray& r, double mint, double maxt, HitRecord& rec) const override{
        vec3 oc = m_Center - r.Origin;
        auto a = r.Direction.length_squared();
        auto h = dot(r.Direction, oc);
        auto c = oc.length_squared() - m_Radius * m_Radius;

        auto discriminant = h*h - a*c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!(mint < root && root < maxt)) {
            root = (h + sqrtd) / a;
            if (!(mint < root && root < maxt))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - m_Center) / m_Radius;
        rec.set_face_normal(r, outward_normal);
        rec.material_index = m_MaterialIndex;

        return true;
    }


private:
    vec3 m_Center;
    double m_Radius;
    uint32_t m_MaterialIndex;
};

class Plane : public Hittable {

public:
    Plane(const vec3& center, const vec3& normal, uint32_t mat_index)
    : center(center), normal(normal), material_index(mat_index) 
    {}

    bool hit(const Ray& r, double mint, double maxt, HitRecord& rec) const override {
        
        auto denominator = dot(r.Direction, normal);

        if(std::fabs(denominator) < 0.00001)
            return false;

        auto numerator = dot(center - r.Origin , normal);
        auto t = numerator/denominator;
        
        if(!((mint < t && t < maxt))) {
            return false;
        }

        rec.t = t;
        rec.p = r.at(t);
        rec.set_face_normal(r, normal);
        rec.material_index = material_index;

        return true;

    }

private:
    vec3 center;
    vec3 normal;
    uint32_t material_index;

};





class Scene : public Hittable {
private:
    std::vector<std::shared_ptr<Hittable>> objects; 
    std::vector<Material> materials;

public:
    Scene() {}
    
    void clear() { objects.clear(); }

    void add(std::shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    void addMaterial(Material mat) {
        materials.push_back(mat);
    }

    bool hit(const Ray& r, double mint, double maxt, HitRecord& rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = maxt;

        for (const auto& object : objects) {
            if (object->hit(r, mint, closest_so_far, temp_rec)) {  // Use '->' to access the hit function
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

    
    Material& getMaterial(int material_index) {
        return materials[material_index];
    }
};

#endif
