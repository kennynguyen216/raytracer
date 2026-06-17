#pragma once 
#include "interval.h"
#include <iostream>
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color){

    double r = double(pixel_color.x());
    double g = double(pixel_color.y());
    double b = double(pixel_color.z());
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

}