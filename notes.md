# *Day 1* raytracer
-Genuinely have no clue what i am doing and no experience with 
cpp and task feels daunting.
-Following the guide of raytracing in a weekend
# what i want to accomplish
- Make apple
- Rotate it
- Make a shadow
- Surely this isnt that hard *gulp*
# Starting with a PPM 
- PPM is a portable pixel map 
- 2d array where each element holds 3 values (rgb), those values map to colors essentialy
# what is happening so far
- include iostream means importing input and output
- std means that whatever you are doing is part of the library of c++ not something that you mad e
- cout means character output 
 - >> 

std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
this line is telling the web browser hey the following is gonna be an image thats has rgb values, heres the height and weight, none of the values go above 255

std::cout << ir << ' ' << ig << ' ' << ib << '\n';
-This will print rgb values to the output 
-Printing each pixel like 120 50 90
-We use ' ' because the format expects Number *space* number *space* number 
-then the new line 

auto basically makes what variable it declares whatever is needed
if you auto something and initialize it with a number and then use it like an int it will do so automatically

need to set the normalize the values to be between 0.0 and 1.0 

ir = integer red
ig 
ib 
u get the point lol 

the .99 is a safety buffer as c++ truncates and chops off the decimal
FLOATING POINT ERRORS 

then it writes the number as an integer to the file 

installed magick 

cmake -B build
    -this tells cmake to setup the build system and put it in a folder called Build. only run once or changing CMakeLists
cmake --build build
    - this compiles my code
    - reads main.cpp and runs it through compiler and produces a main.exe
    - run everytime i change code
magick image.ppm image.png
    - makes my image.ppm into an image png 
build\Debug\inOneWeekend.exe > image.ppm

 std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

 progress indicator to see if there are things stalling or how long it takes 

  std::clog << "\rDone.                 \n";

  \r puts the cursor to the beginning of the line

  # vec3 time!
   - going to attempt to do this with a checklist and just googling documentation the old fashion way 
   - the following is checklist 


   ## vec3.h Checklist
- [DONE] Create `vec3.h`
- [DONE] Add `#pragma once`
- [DONE] Declare class skeleton with `double e[3]`
- [DONE] Add constructors (default + parameterized)
- [DONE] Add accessors: `x()`, `y()`, `z()`
- [DONE] Add operators inside class: `-`, `[]`, `+=`, `*=`, `/=`
- [DONE] Add utility inside class: `length()`, `length_squared()`
- [DONE] Add free functions outside class: `<<`, `+`, `-`, `*`, `/`, `dot()`, `cross()`, `unit_vector()`
- [DONE] Add `using point3 = vec3;` alias at bottom
- [DONE] Include in `main.cpp` and test compile

#color h 
made a color header file that handles the pixel color output


#ray
made a ray for ray casting holy

basically a ray for origin
and a ray for direction 

what is the purpose of ray?

the ray purpose is you shoot a ray at something and then it figures out the color of the pixel you hit based on where the how far the ray travels, the material it hits, the angle at which it hits, etc 



## Camera & Viewport Setup (main.cpp)

### What I built and why

**ray_color()** — takes a ray and returns a color. Gets the unit direction of the ray, extracts the y component and remaps it from (-1,1) to (0,1), then lerps between white and blue. Rays pointing up = more blue, rays pointing down = more white. This gives the sky gradient.

**viewport_u / viewport_v** — vectors that define the viewport rectangle. viewport_u points left to right along the x axis with length = viewport width. viewport_v points top to bottom along the y axis (negative because row 0 is the top of the image).

**pixel_delta_u / pixel_delta_v** — viewport_u and viewport_v divided by the number of pixels. Represents how far apart adjacent pixels are in 3D world units.

**viewport_upper_left** — the 3D coordinate of the top-left corner of the viewport. Start at camera_center, move back along z by focal_length, then left half the viewport width and up half the viewport height.

**pixel00_loc** — center of the top-left pixel. viewport_upper_left + half a pixel right + half a pixel down.

**pixel_center** — for each pixel (i,j), the 3D position of that pixel. pixel00_loc + i steps right + j steps down.

**ray_direction** — vector from camera_center to pixel_center. Tells the ray which way to travel.

**ray r** — the actual ray object. Starts at camera_center, travels in ray_direction. One ray per pixel.

- [DONE] Add `aspect_ratio = 16.0 / 9.0`
- [DONE] Change `image_width` to 400
- [DONE] Calculate `image_height` from aspect ratio, clamp to at least 1
- [DONE] Add `focal_length = 1.0`
- [DONE] Add `viewport_height = 2.0`
- [DONE] Add `viewport_width`
- [DONE] Add `camera_center = point3(0,0,0)`
- [DONE] Add `viewport_u` and `viewport_v` vectors
- [DONE] Add `pixel_delta_u` and `pixel_delta_v`
- [DONE] Calculate `viewport_upper_left` and `pixel00_loc`
- [DONE] Add `ray_color()` function
- [DONE] Update render loop to cast rays and call `ray_color()`
- [DONE] Test compile and run

## Chapter 5: Adding a Sphere

### What this chapter is about
We're adding the first actual object to the scene — a sphere. The key question is: does a ray hit the sphere? This is solved with math (quadratic equation). If the ray hits, color it red. If not, show the sky gradient.

The math: a point P is on a sphere if the distance from P to the center equals the radius. We substitute the ray equation P(t) = origin + t*direction into the sphere equation and solve for t using the quadratic formula. If t has real solutions, the ray hits the sphere.

### Checklist
- [DONE] Write `hit_sphere()` function that returns true/false if a ray hits a sphere
- [DONE] Update `ray_color()` to call `hit_sphere()` and return red if hit
- [DONE] Test compile and run — should see a red circle on the gradient background

## Chapter 6: Surface Normals and Multiple Objects

### What this chapter is about
Shading with normals, abstracting hittable objects, supporting multiple objects in a scene, and setting up shared infrastructure.

**Surface normals** — a vector perpendicular to the surface at the hit point. Used to shade the sphere by mapping (x,y,z) components to (r,g,b) colors. All normals are unit length.

**hittable abstraction** — instead of a hardcoded sphere function, we made an abstract `hittable` class with a virtual `hit()` method. `sphere` inherits from it. This lets us treat any object the same way.

**hit_record** — a struct that bundles everything about a hit: position `p`, `normal`, parameter `t`, and `front_face`. Avoids recomputing things.

**front_face** — tracks whether the ray hit the outside or inside of a surface. `set_face_normal()` sets this and flips the normal to always point against the ray.

**Simplified sphere math** — replaced `b = -2*dot(...)` with `h = dot(...)`. Factors cancel in the quadratic formula giving a cleaner expression. Also tries both roots so inside-sphere hits work.

**hittable_list** — a list of hittable objects that itself implements `hittable`. Loops through all objects and tracks the closest hit.

**rtweekend.h** — central utility header with `infinity`, `pi`, `shared_ptr`/`make_shared` usings, and common includes.

**shared_ptr / make_shared** — smart pointers that manage memory automatically. Used to add objects: `world.add(make_shared<sphere>(...))`.

### Checklist
- [DONE] Create `hittable.h` with `hit_record` and abstract `hittable` class
- [DONE] Add `front_face` and `set_face_normal()` to `hit_record`
- [DONE] Create `sphere.h` inheriting from `hittable`
- [DONE] Simplify sphere math to use `h` instead of `b`
- [DONE] Try both roots (near and far) in sphere hit function
- [DONE] Call `set_face_normal()` in sphere hit function
- [DONE] Create `hittable_list.h`
- [DONE] Create `rtweekend.h`
- [DONE] Update `main.cpp` to use `hittable_list world` and pass it to `ray_color()`
- [DONE] Add ground plane sphere at `(0,-100.5,-1)` radius 100
- [DONE] Test compile and run — sphere sitting on a ground plane

## Chapter 7: Moving the Camera into its Own Class

### What this chapter is about
Pure refactor — no visual change. All the viewport/pixel-grid setup and the render loop got pulled out of `main()` and into a new `camera` class (`camera.h`). `main()` now just builds the `world`, configures a `camera` object's public settings (`aspect_ratio`, `image_width`), and calls `cam.render(world)`.

**initialize()** — private method, does all the viewport math (focal length, viewport size, `pixel_delta_u/v`, `pixel00_loc`) that used to be loose code in `main()`. Called automatically at the start of `render()`.

**Lesson learned: ordering matters.** `cam.render(world)` reads `world` at the moment it's called — if you call it *before* `world.add(...)`, you render an empty world. The `world.add(...)` calls must come before `cam.render(world)` in `main()`.

### Checklist
- [DONE] Create `camera.h` with `camera` class (public `aspect_ratio`, `image_width`; private `initialize()`, `render()`, `ray_color()`)
- [DONE] Move viewport setup into `initialize()`, render loop into `render()`
- [DONE] Update `main.cpp`: build `world`, create `camera cam`, set `cam.aspect_ratio`/`cam.image_width`, call `cam.render(world)` *after* adding objects to `world`
- [DONE] Test compile and run — identical image to chapter 6

## Chapter 8: Antialiasing

### What this chapter is about
Fixing the jagged "stair-step" edges caused by **point sampling** — one ray through the exact center of each pixel can only return one of two outcomes (hit/miss) for a pixel straddling an edge. The fix is **Monte Carlo sampling**: shoot many randomly-jittered rays per pixel and average the resulting colors, so an edge pixel that's e.g. 70% sphere / 30% sky ends up roughly 70/30 blended instead of a hard binary choice.

### Key concepts and lessons learned

**random_double()** — uses `std::mt19937` (the actual pseudo-random *engine*, produces raw random-looking integers) plus `std::uniform_real_distribution<double>` (a *shaper*, maps the engine's output into `[0,1)`). Both declared `static` inside the function so they persist across calls — without `static`, the generator would be recreated from its default initial state every call and always return the same first value. `static` isn't about saving memory here, it's about preserving the generator's evolving internal state across calls.

**interval::clamp(x)** — clamps `x` into `[min, max]`. Used in `write_color()` via `static const interval intensity(0.000, 0.999)`. Important gotcha: `clamp()` must be applied to the **raw `[0,1]` color component** (e.g. `pixel_color.x()`), *not* a value already pre-scaled to `[0,255]`. If you scale to 0-255 first and then clamp against `[0, 0.999]`, every value > 0.999 clamps down to the same number — producing an all-black or all-white image regardless of the real scene colors.

**sample_square()** — returns a random `vec3` offset in `[-0.5, 0.5) x [-0.5, 0.5)`, representing a random point within one pixel's square area. Equivalent ways to write it: `random_double() - 0.5` or `random_double(-0.5, 0.5)`.

**get_ray(i, j)** — builds a `ray` toward a randomly-jittered point within pixel `(i,j)`, by adding the offset to `i`/`j` *before* multiplying by `pixel_delta_u`/`pixel_delta_v`: `pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v)`.
- **Operator precedence lesson**: `*` binds tighter than `+`. Writing `i + offset.x() * pixel_delta_u` actually evaluates as `i + (offset.x() * pixel_delta_u)` — an `int + vec3`, which is a type error. Needed explicit parens: `(i + offset.x()) * pixel_delta_u`.
- **Type/units lesson**: `pixel00_loc` is a world-space point, `pixel_delta_u`/`v` are world-space step vectors, but `i`, `j`, `offset.x()`, `offset.y()` are just plain numbers (pixel indices). Multiplying a number by a step vector converts "how many pixel-steps" into "how far in world space" — only then can it be added to `pixel00_loc`.

**render() sampling loop** — for each pixel: `color pixel_color(0,0,0)`, then loop `samples_per_pixel` times accumulating `pixel_color += ray_color(get_ray(i,j), world)`, then `write_color(std::cout, pixel_color * pixel_samples_scale)` where `pixel_samples_scale = 1.0 / samples_per_pixel`.

**`(0,0,0)` vs `color(0,0,0)`** — `(0,0,0)` is the comma operator and evaluates to just `0` (an `int`), not a 3-argument constructor call. Needed `color(0,0,0)` (or `color pixel_color(0,0,0);` direct-init) to actually call `vec3(double,double,double)`.

**Header include-order bug** — adding `#include "interval.h"` to `color.h` broke compilation with `'infinity': undeclared identifier` inside `interval.h`. Root cause: `rtweekend.h` included `color.h` (which now drags in `interval.h`) *before* it defined `const double infinity = ...`. Because of `#pragma once`, `interval.h`'s contents only get pasted once — the first time it's reached — so that first pasting needs everything it depends on (`infinity`) to already be defined. Fix: move `const double infinity = ...;` to the top of `rtweekend.h`, before any local `#include`s.

### Checklist
- [DONE] Add `random_double()` (no-arg and `min`/`max` overloads) to `rtweekend.h` using `<random>`
- [DONE] Add `interval::clamp()` to `interval.h`
- [DONE] Update `write_color()` in `color.h` to clamp raw `[0,1]` components via `intensity` interval before scaling to a byte
- [DONE] Fix header include-order bug (`infinity` needed before `interval.h`'s first inclusion)
- [DONE] Add `samples_per_pixel` (public) and `pixel_samples_scale` (private) to `camera`
- [DONE] Add `sample_square()` helper — random offset in unit square
- [DONE] Add `get_ray(i, j)` — jittered ray per sample
- [DONE] Restructure `render()`'s inner loop to accumulate + average `samples_per_pixel` rays per pixel
- [DONE] Set `cam.samples_per_pixel = 100` in `main.cpp`
- [DONE] Test compile and run — same scene, antialiased edges
