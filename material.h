#pragma once
#include "ray.h"
#include "hittable.h"
#include "color.h"
#include <cmath>


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
// Dielectric materials are clear materials like glass or water that can reflect and refract.
class dielectric : public material {
    public:
    double refraction_index;
    dielectric(double refraction_index) : refraction_index(refraction_index) {}
    static double reflectance(double cos_theta, double refraction_ratio) {
        auto r_theta = (1.0 - refraction_ratio) / (1+refraction_ratio);
        r_theta = r_theta * r_theta;

        return r_theta + (1-r_theta) * std::pow(1-cos_theta, 5); 

    }
    bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color(1.0, 1.0, 1.0); // Clear glass does not tint the ray.
        double refraction_ratio;
        // front_face tells us whether the ray is entering the sphere or leaving it.
        if(rec.front_face) {
            // Entering glass: air / glass.
            refraction_ratio = 1.0 / refraction_index;
        }
        else {
            // Leaving glass: glass / air.
            refraction_ratio = refraction_index;
        }
        
        auto unit_direction = unit_vector(r.direction());
        // dot(-unit_direction, rec.normal) asks how straight on did the ray hit the surface
        auto cos_theta = std::fmin(dot(-unit_direction, rec.normal),1.0);
        auto sin_theta = std::sqrt(1.0 - (cos_theta * cos_theta));
        // Snell's law cannot produce a valid refracted ray if sin(theta) would exceed 1.
        // In that case, the ray must reflect.
        bool cannot_refract = (refraction_ratio * sin_theta) > 1.0;
        vec3 direction;
        if(cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
            direction = reflect(unit_direction, rec.normal);
        }
        else {
            direction = refract(unit_direction, rec.normal, refraction_ratio);
        }
        
        scattered = ray(rec.p, direction);

        return true;
    }
};
