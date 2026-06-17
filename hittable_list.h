#pragma once
#include "hittable.h"
#include <vector>
#include <memory>

class hittable_list: public hittable {

    public:
    void clear(){
        objects.clear();
    };
    void add(std::shared_ptr<hittable> object){
        objects.push_back(object);
    };
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        bool track_hit = false;
        double closest_hit = ray_t.max;
        for (const auto& object: objects) {
            if (object->hit(r, interval(ray_t.min, closest_hit), rec)) {
                track_hit = true;
                closest_hit = rec.t;
            };
        }
        return track_hit;
    }

    std::vector<std::shared_ptr<hittable>> objects;
    hittable_list() {
    }
    hittable_list(std::shared_ptr<hittable> object) {
        objects.push_back(object);
    }
};