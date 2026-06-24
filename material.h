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
