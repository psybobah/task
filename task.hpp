#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <memory>
#include <vector>
#include <cmath>
#include <iostream>

using std::vector;
using std::shared_ptr;

class GeomEntity {
public:
    virtual std::tuple<double, double, double> getPoint(double t) = 0;

    virtual std::tuple<double, double, double> getDerivative(double t) = 0;

    virtual void print() = 0;
};

class XYCircle : public GeomEntity {
    double x, y, z;
    double radius;
public:
    XYCircle(double _x, double _y, double _z, double _radius) : radius(_radius), x(_x), y(_y), z(_z) {
        if (_radius < 0) {
            throw std::invalid_argument("Radius must be positive");
        }        
    }

    std::tuple<double, double, double> getPoint(double t) {
        return std::make_tuple(x + radius * cos(t), y + radius * sin(t), z);
    }

    std::tuple<double, double, double> getDerivative(double t) {
        return std::make_tuple(- radius * sin(t), radius * cos(t), 0.);
    }

    void print() {
        std::cout << "XYCircle = {" << x << ", "
                                    << y << ", "
                                    << z << ", "
                                    << "radius = " << radius << "}\n";
    }

    double getRadius() const {
        return radius;
    }
};

class XYEllipse : public GeomEntity {
    double x, y, z;
    double a, b; // a is the half axis along x and b along y
public:
    XYEllipse(double _x, double _y, double _z, double _a, double _b) : a(_a), b(_b), x(_x), y(_y), z(_z) {
        if (_a < 0 || _b < 0) {
            throw std::invalid_argument("Radii must be positive");
        }        
    }

    std::tuple<double, double, double> getPoint(double t) {
        return std::make_tuple(x + a * cos(t), y + b * sin(t), z);
    }

    std::tuple<double, double, double> getDerivative(double t) {
        return std::make_tuple(- a * sin(t), b * cos(t), 0.);
    }

    void print() {
        std::cout << "XYEllipse = {" << x << ", "
                                     << y << ", "
                                     << z << ", "
                                     << "a, b = " << a << ", " << b << "}\n";
    }
};

class ZHelix : public GeomEntity {
    double x, y, z;
    double radius;
    double step;
public:
    ZHelix(double _x, double _y, double _z, double _radius, double _step) : radius(_radius), step(_step), x(_x), y(_y), z(_z) {
        if (_radius < 0) {
            throw std::invalid_argument("Radius must be positive");
        }        
    }

    std::tuple<double, double, double> getPoint(double t) {
        return std::make_tuple(x + radius * cos(t), y + radius * sin(t), z + t / 2. / M_PI * step);
    }

    std::tuple<double, double, double> getDerivative(double t) {
        return std::make_tuple(- radius * sin(t), radius * cos(t), 1. / 2. / M_PI * step);
    }

    void print() {
        std::cout << "ZHelix = {" << x << ", "
                                  << y << ", "
                                  << z << ", "
                                  << "radius, step = " << radius << ", " << step << "}\n";
    }
};

#endif // __TASK_HPP__
