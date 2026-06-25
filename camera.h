#pragma once 
#include "hittable.h"
#include "vec3.h"
#include "material.h"

class camera {
    public:
        double aspect_ratio = 1.0;
        int image_width = 100;
        int samples_per_pixel = 10;
        int max_depth = 90;
        double vfov = 90;
        point3 lookfrom = point3(0,0,0);
        point3 lookat = point3(0,0,-1);
        vec3 vup = vec3(0,1,0);
        
        void render(const hittable& world) {
            initialize();
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
            for(int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for(int i = 0; i < image_width; i++) {
                    //auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    //auto ray_direction = pixel_center - center;
                    //ray r = ray(center, ray_direction);
                    color pixel_color = color(0,0,0);
                    for(int k = 0; k < samples_per_pixel; k++) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, world, max_depth);
                    }
                    write_color(std::cout, pixel_color * pixel_samples_scale);
                }
            }
            std::clog << "\rDone.                 \n";
        }

    private:
        int image_height;
        point3 center;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;
        vec3 u; 
        vec3 v; 
        vec3 w;
        double pixel_samples_scale;
// this initializes all the stuff in main.cpp just cleaning up code 
        void initialize() {
            center = lookfrom;
            image_height = int(image_width / aspect_ratio);
            image_height = std::max(1, image_height);
            auto focal_length = 1.0;
            auto theta = degrees_to_radians(vfov);
            auto h = std::tan(theta/2);
            auto viewport_height = 2 * h * focal_length;
            auto viewport_width = viewport_height * (double(image_width)/image_height);
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w,u);
            auto viewport_u = viewport_width * u;
            auto viewport_v = viewport_height * -v;
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;
            auto viewport_upper_left  = center - (viewport_u * .5) - (viewport_v * .5) - (focal_length * w);
            pixel00_loc = viewport_upper_left + (pixel_delta_v*.5) + (pixel_delta_u*.5);
            pixel_samples_scale = 1.0 / samples_per_pixel;
        }
        color ray_color(const ray& r, const hittable& world, int depth) const {
            if (depth <= 0)
            {
                return color(0,0,0);
            }

            vec3 lol = unit_vector(r.direction());
            auto blend = .5 * (lol.y() + 1.0);
            // auto white = color(1,1,1);
            // auto blue = color(.5,.7,1.0);
            // auto white = color(0.878, 0.851, 0.965); // lavender horizon glow (dimmer)
            // auto blue = color(0.165, 0.137, 0.337); // midnight blue night sky (dimmer)
            auto white = color(0.92, 0.9, 0.98); // lavender horizon glow, brighter
            auto blue = color(0.28, 0.22, 0.48); // midnight blue night sky, brighter

            hit_record rec;
            if (world.hit(r, interval(0.001, infinity), rec)) {
                color attenuation;
                ray scattered;
                if(rec.mat->scatter(r, rec, attenuation, scattered)) {
                    return attenuation * ray_color(scattered, world, depth-1);
                }
                return color(0,0,0);
            } else { 
                return (1-blend) * white + blend * blue; // sets the sky color 
            }
        }
        vec3 sample_square() const {
            auto x = random_double(-0.5, 0.5);
            auto y = random_double(-0.5, 0.5);
            auto z = 0;
            return vec3(x,y,z);
        }
        ray get_ray(int i, int j) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
            auto ray_direction = pixel_sample - center;
            ray r  = ray(center, ray_direction);
            return r;
        }
};