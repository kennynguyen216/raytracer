#pragma once
#include <cmath>
#include <iostream>

class vec3 {
    public:
        double e[3];
        // constructing vectors
        vec3(){
            e[0] = 0;
            e[1] = 0;
            e[2] = 0; 
        }
        vec3(double e0, double e1, double e2) {
            e[0] = e0;
            e[1] = e1;
            e[2] = e2;
        }
        // accessors
        double x() const {

            return e[0];
        }
        
        double y() const {

            return e[1];

        }

        double z() const {

            return e[2];

        }
        
        vec3 operator-() const {
            return vec3(-e[0], -e[1], -e[2]);
        }
        // getter method
        double operator[](int i) const {

            return e[i];

        }
        // setter method
        double& operator[](int i) {

            return e[i];
        }

        vec3& operator+=(const vec3& i) {

            e[0] += i[0];
            e[1] += i[1]; 
            e[2] += i[2];

            return *this;
        }

        vec3& operator*=(double i) {

            e[0] *= i;
            e[1] *= i;
            e[2] *= i;

            return *this;
        }

        vec3& operator/=(double i) {

            e[0] /= i;
            e[1] /= i;
            e[2] /= i;

            return *this;
        }

        double length_squared() const {

            return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
        }

        double length() const {

            return std::sqrt(length_squared());
        }

        bool near_zero() const {
            auto s = 1e-8;
            return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
        }
};

using point3 = vec3;
// print statement for the 3 values in a vector
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {

    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];

}

inline vec3 operator+(const vec3& u, const vec3& v) {

    vec3 f(u.e[0] + v.e[0],
    u.e[1] + v.e[1],
    u.e[2] + v.e[2]);

    return f;
}

inline vec3 operator-(const vec3& u, const vec3& v) {

    vec3 f(u.e[0] - v.e[0],
    u.e[1] - v.e[1],
    u.e[2] - v.e[2]);

    return f;
}

inline vec3 operator*(const vec3& u, const vec3& v) {

    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);

}

inline vec3 operator*(const vec3& v, double t){

    return vec3(v.e[0] * t, v.e[1] * t, v.e[2] *t);
}
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(const vec3& v, double t) {

    return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);

}

inline double dot(const vec3& u, const vec3& v) {

    return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];

}

inline vec3 cross(const vec3& u, const vec3& v) {

    return vec3(u.e[1]*v.e[2] - u.e[2]*v.e[1], 
                u.e[2]*v.e[0] - u.e[0]*v.e[2], 
                u.e[0]*v.e[1] - u.e[1]*v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {

    return v / v.length();
}

inline vec3 random_vec3() {

    return  vec3(random_double(), random_double(),random_double()); 

}

inline vec3 random_vec3(double min, double max) {

    return vec3(random_double(min, max),random_double(min,max),random_double(min,max));
}

inline vec3 random_unit_vector(){
    
    while(true) {
        vec3 random_point = random_vec3(-1,1);
        double point_squared = random_point.length_squared();
        if((point_squared <=1) && (point_squared > 1e-160)) {
            return random_point / random_point.length();
        }
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {

    vec3 random_vector = random_unit_vector();
    if (dot(random_vector, normal) > 0) {
        return random_vector;
    }
    else {
        return random_vector.operator-();
    }

}

inline vec3 reflect(const vec3& incoming, const vec3& normal) {

    return incoming - 2*dot(incoming, normal) * normal;


}
