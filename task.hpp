#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <memory>
#include <vector>
#include <cmath>

using std::vector;
using std::shared_ptr;

class GeomEntity {
public:
    virtual std::tuple<double, double, double> getPoint(double t) = 0;

    virtual std::tuple<double, double, double> getDerivative(double t) = 0;
};

class XYCircle : public GeomEntity {
    double radius;
public:
    XYCircle(double x, double y, double z, double _radius) : radius(_radius) {
        if (_radius < 0) {
            throw std::invalid_argument("Radius must be positive");
        }        
    }

    std::tuple<double, double, double> getPoint(double t) {
        return std::make_tuple(radius * cos(t), radius * sin(t), 0.);
    }

    std::tuple<double, double, double> getDerivative(double t) {
        return std::make_tuple(- radius * sin(t), radius * cos(t), 0.);
    }
};

class XYEllipse : public GeomEntity {
    double a, b; // a is the half axis along x and b along y
public:
    XYEllipse(double x, double y, double z, double _a, double _b) : a(_a), b(_b) {
        if (_a < 0 || _b < 0) {
            throw std::invalid_argument("Radii must be positive");
        }        
    }

    std::tuple<double, double, double> getPoint(double t) {
        return std::make_tuple(a * cos(t), b * sin(t), 0.);
    }

    std::tuple<double, double, double> getDerivative(double t) {
        return std::make_tuple(- a * sin(t), b * cos(t), 0.);
    }
};

class ZHelix : public GeomEntity {
    double radius;
    double step;
public:
    ZHelix(double x, double y, double z, double _radius, double _step) : radius(_radius), step(_step) {
        if (_radius < 0) {
            throw std::invalid_argument("Radius must be positive");
        }        
    }

    std::tuple<double, double, double> getPoint(double t) {
        return std::make_tuple(radius * cos(t), radius * sin(t), t / 2. / M_PI * step);
    }

    std::tuple<double, double, double> getDerivative(double t) {
        return std::make_tuple(- radius * sin(t), radius * cos(t), 1. / 2. / M_PI * step);
    }
};

#endif // __TASK_HPP__
