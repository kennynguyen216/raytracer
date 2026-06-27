#include <iostream>
#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
/*
//The following method is not needed anymore because of sphere.h
//double hit_sphere(const point3& center, double radius, const ray& r) {
    //vector from ray origin to sphere center
   // vec3 origin_center = center - r.origin();
    //how fast is the ray moving (squared length of ray direction)
    //double a = r.direction().length_squared();
    // how much ray direction aligns with vector towarad sphere center
    // is the ray heading to or away from sphere
    //double b = dot(r.direction(), origin_center) * -2.0;
    // is the origin inside or outisde the sphere. negative inside positive outside
    //double c = dot(origin_center, origin_center) - radius * radius; 
//    double discriminant = b*b-(4*a*c);    
  //  if ((discriminant) >= 0) {
    //    double t = (-b - std::sqrt(discriminant)) / (2*a);
      //  return t;
    //} else { return -1.0;}

//}
//color ray_color(const ray& r, const hittable& world) {
    //vec3 lol = unit_vector(r.direction());
    // this is commented out because we made sphere.h btw
    //auto blend = .5* (lol.y() +1.0);
    //auto white = color(1,1,1);
    //auto blue = color(.5,.7,1.0);
    //double t = hit_sphere(point3(0,0,-1), .5, r);
    //if(t > 0.0) {
        //point3 hit_point = r.at(t);
        //point3 normal = unit_vector(hit_point - vec3(0,0,-1));
      //  return 0.5 * (normal + vec3(1,1,1));}
    //    else {return (1-blend) * white + blend * blue;}


    //construct a sphere the center point is 0,0,-1
    //the radius is arbitrary can be any size
    //it just will be bigger lol 

    //chapter 6 makes me edit this out because im using world now
    //sphere circle(point3(0,0,-1), 0.5);

    //declare hit record
    //hit_record rec;

    //if (circle.hit(r, 0, 1e9, rec)) {
      //  
    //} else 
    //if(world.hit(r, interval(0, infinity), rec)) {
      //  return 0.5 * (rec.normal + vec3(1,1,1));
    //} else {return (1-blend) * white + blend * blue;}
//}
    // ---- everything below this point has been migrated to camera.h ----
    // im also moving the int main to below all this commented out code lol
    // // setting the image dimensions
    // int image_width = 400;
    // auto aspect_ratio = 16.0 / 9.0;
    // int image_height = int(image_width / aspect_ratio);
    // image_height = std::max(1, image_height);
    // auto focal_length =  1.0;
    // auto viewport_height = 2.0;
    // auto viewport_width = viewport_height * (double(image_width)/image_height);
    // point3 camera_center = point3(0,0,0);
    // //viewport u and v are vectors that lie across the x and y axis
    // //telling us that its left and right and how long we are
    // //or up and down and how long we are
    // vec3 viewport_u = vec3(viewport_width, 0 , 0);
    // vec3 viewport_v = vec3(0, -viewport_height, 0); // this is negative because the top row is just 0
    // // pixel delta tells us how far a pixel is from the next pixel
    // //either left and right or up and down
    // vec3 pixel_delta_u = viewport_u / image_width;
    // vec3 pixel_delta_v = viewport_v / image_height;
    // // Vu points left to right and Vv points top to down
    // // camera starts in the middle of the viewpoint
    // // so to get to the upper left you need to travel from right to left
    // // you need to travel from down to up
    // // you only need to travel *5 the full distance since you are starting
    // //from the middle
    // point3 viewport_upper_left = camera_center -(viewport_u * .5) -(viewport_v * .5) - vec3(0,0, focal_length);
    // point3 pixel00_loc = viewport_upper_left + (pixel_delta_v*.5) + (pixel_delta_u*.5);
    // // render
    // std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    //
    // for(int j = 0; j < image_height; j++) {
    //     std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    //     for(int i = 0; i < image_width; i++) {
    //         auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    //         auto ray_direction = pixel_center - camera_center;
    //         ray r = ray(camera_center, ray_direction);
    //         write_color(std::cout, ray_color(r, world));
    //     }
    // }
    // std::clog << "\rDone.                 \n";
*/

int main() {

    hittable_list world;
    camera cam; 
    cam.vfov = 25;
    cam.lookfrom = point3(7,3,5);
    cam.lookat = point3(0,0.5,0);
    cam.vup = vec3(0,1,0);
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 500;
    cam.defocus_angle = 0.6;
    cam.focus_dist = (cam.lookfrom - cam.lookat).length();

    // material/sphere construction cheat sheet moved to notes.md ("Quick Reference: Materials & Spheres")

    // auto material_ground = make_shared<lambertian>(color(0.25, 0.15, .08));
    // auto material_sphere = make_shared<metal>(color(0.9, 0.05, 0.15), 0.2);
    // auto material_left = make_shared<metal>(color(0.0, 0.9, 1.0), 0.05); // neon cyan, sharp mirror
    // auto material_right = make_shared<lambertian>(color(0.02, 0.02, 0.03)); // near-black matte
    // auto material_sphere = make_shared<metal>(color(0.761, 0.322, 0.882), 0.0); // medium orchid (dimmer)
    // auto material_left = make_shared<metal>(color(0.431, 0.796, 0.961), 0.0); // light sky blue (dimmer)
    // auto material_right = make_shared<metal>(color(0.345, 0.416, 0.886), 0.0); // royal blue (dimmer)
    /*
    Previous hand-built cyberpunk test scene:

    auto material_ground = make_shared<lambertian>(color(0.01, 0.01, 0.015));
    auto material_sphere = make_shared<metal>(color(0.88, 0.42, 0.98), 0.05);
    auto material_left = make_shared<dielectric>(1.5);
    auto material_bubble = make_shared<dielectric>(1.0 / 1.5);
    auto material_right = make_shared<metal>(color(0.45, 0.52, 0.98), 0.3);
    world.add(make_shared<sphere>(point3(0,0,-1), .5, material_sphere));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100, material_ground));
    world.add(make_shared<sphere>(point3(-1,0,-1), 0.5, material_left));
    world.add(make_shared<sphere>(point3(-1,0,-1), 0.4, material_bubble));
    world.add(make_shared<sphere>(point3(1,0,-1), 0.5, material_right));
    */

    auto ground_material = make_shared<lambertian>(color(0.008, 0.008, 0.012));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -8; a < 8; a++) {
        for (int b = -8; b < 8; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(0, 0.2, 0)).length() > 1.1 &&
                (center - point3(4, 0.2, 0)).length() > 1.1 &&
                (center - point3(-4, 0.2, 0)).length() > 1.1) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.60) {
                    auto albedo = color(
                        random_double(0.01, 0.08),
                        random_double(0.005, 0.04),
                        random_double(0.03, 0.16)
                    );
                    sphere_material = make_shared<lambertian>(albedo);
                } else if (choose_mat < 0.90) {
                    color albedo;
                    auto neon_pick = random_double();
                    if (neon_pick < 0.25) {
                        albedo = color(0.55, 0.95, 1.0);
                    } else if (neon_pick < 0.50) {
                        albedo = color(0.95, 0.35, 1.0);
                    } else if (neon_pick < 0.75) {
                        albedo = color(0.35, 0.45, 1.0);
                    } else {
                        albedo = color(0.75, 0.55, 0.95);
                    }
                    auto fuzz = random_double(0.0, 0.35);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                } else {
                    sphere_material = make_shared<dielectric>(1.5);
                }

                world.add(make_shared<sphere>(center, 0.2, sphere_material));
            }
        }
    }

    auto material_left = make_shared<dielectric>(1.5);
    auto material_bubble = make_shared<dielectric>(1.0 / 1.5);
    auto material_center = make_shared<metal>(color(0.88, 0.42, 0.98), 0.04);
    auto material_right = make_shared<metal>(color(0.45, 0.88, 1.0), 0.18);

    world.add(make_shared<sphere>(point3(-4,1,0), 1.0, material_left));
    world.add(make_shared<sphere>(point3(-4,1,0), 0.85, material_bubble));
    world.add(make_shared<sphere>(point3(0,1,0), 1.0, material_center));
    world.add(make_shared<sphere>(point3(4,1,0), 1.0, material_right));

    cam.render(world);
}
