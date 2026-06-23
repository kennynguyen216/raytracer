#pragma once 
#include "interval.h"
#include <iostream>
#include "vec3.h"

using color = vec3;

double linear_to_gamma(double linear_component) {
    return sqrt(linear_component);
}

void write_color(std::ostream& out, const color& pixel_color){

    double r = double(pixel_color.x());
    double g = double(pixel_color.y());
    double b = double(pixel_color.z());
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));


    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

}