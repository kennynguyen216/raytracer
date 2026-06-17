#pragma once
#include <limits>
#include <cmath>
#include <memory>
#include <random>
const double infinity = std::numeric_limits<double>::infinity();
#include "color.h"
#include "ray.h"
#include "vec3.h"

using std::make_shared;
using std::shared_ptr;


#include "interval.h"
const double pi =  3.1415926535897932385;

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min +(max-min) * random_double();
}