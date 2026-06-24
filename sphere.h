#pragma once 
#include "hittable.h"
#include "ray.h"

class sphere: public hittable {
    private:
    point3 center;
    double radius;
    shared_ptr<material> mat;

    public:
    sphere(const point3& center, double radius, shared_ptr<material> mat) : center(center), radius(radius), mat(mat){}
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, interval ray_t, hit_record& rec) const {

    vec3 oc = center - r.origin();

    double a = r.direction().length_squared();
    // how much ray direction aligns with vector towarad sphere center
    // is the ray heading to or away from sphere
    double h = dot(r.direction(), oc);
    // is the origin inside or outisde the sphere. negative inside positive outside
    double c = dot(oc,oc) - radius * radius; 

    double discriminant = h*h-(a*c);
    
    if((discriminant) < 0) {
        return false;
    } else
     {
        double sqrtd = std::sqrt(discriminant);
        double t = (h - sqrtd ) / (a);
        if(ray_t.surrounds(t)) {
            rec.mat = mat;
            rec.t = t;
            rec.p = r.at(t); // rec.p is the position of where you hit the sphere
            //rec.normal = unit_vector(rec.p - center);
            rec.set_face_normal(r, unit_vector(rec.p - center));
            return true;
        } else { 
        double t = (h + sqrtd ) / (a);
        if(ray_t.surrounds(t)) {
            rec.mat = mat;
            rec.t = t;
            rec.p = r.at(t);
            //rec.normal = unit_vector(rec.p-center);
            rec.set_face_normal(r, unit_vector(rec.p - center));
            return true;
        } else {return false;}
    }
    } 
}