#pragma once
#include "ray.h"
#include "hittable.h"
#include "color.h"


class material {
    public:
    virtual ~material() = default;
    virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
    public:
    color albedo;

    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto direction = rec.normal + random_unit_vector();
        if (direction.near_zero()) {
            direction = rec.normal;
        }

        scattered = ray(rec.p, direction);
        attenuation = albedo;
        return true;
    }
};

class metal : public material {
    public:
    color albedo;
    double fuzz;

    metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto reflected = reflect(unit_vector(r.direction()), rec.normal);
        reflected = reflected + fuzz * random_unit_vector();
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0 ;
    }
};
// dielectric materials ar elike glass or water where they can reflect and refract
class dielectric : public material {
    public:
    double refraction_index;
    dielectric(double refraction_index) : refraction_index(refraction_index) {}
    bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color(1.0, 1.0, 1.0); // this glass does not tint the way. clear glass does not tint 
        double refraction_ratio;
        // front face asks whether or not the ray hit the outside of the sphere or did it hit
        // or is the ray is inside the sphere hitting the surface from the inside
        if(rec.front_face) {
            //if it hit the outside then it refracts (entering glass so air/glass)
            refraction_ratio = 1.0 / refraction_index;
        }
        else {
            // if it hit from inside the ray is leaving the glass so glass/air
            refraction_ratio = refraction_index;
        }
        
        auto unit_direction = unit_vector(r.direction());
        // dot(-unit_direction, rec.normal) asks how straight on did the ray hit the surface
        auto cos_theta = std::fmin(dot(-unit_direction, rec.normal),1.0);
        auto sin_theta = std::sqrt(1.0 - (cos_theta * cos_theta));
        //this is snells law which says that since sin cannot be greater than 1 then if the
        //sin(theta) is greater than 1 than it cannot refract so it MUST reflect
        bool cannot_refract = (refraction_ratio * sin_theta) > 1.0;
        vec3 direction;
        if(cannot_refract) {
            direction = reflect(unit_direction, rec.normal);
        }
        else {
            direction = refract(unit_direction, rec.normal, refraction_ratio);
        }
        scattered = ray(rec.p, direction);

        return true;
    }
};