#include "task.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>

double get_rand_val() {
    return static_cast<double>(std::rand()) / RAND_MAX - 0.5;
}

int main(void) {

    vector <shared_ptr<GeomEntity>> vec;
    size_t num_ent{10};
    std::srand(2);

    for (size_t idx = 0; idx < num_ent; idx++) {
        switch (rand() % 3) {
            case 0: {
                vec.emplace_back(std::make_shared<XYCircle>(get_rand_val(), get_rand_val(), get_rand_val(),
                                                            fabs(get_rand_val())));
                break;
            }
            case 1: {
                vec.emplace_back(std::make_shared<XYEllipse>(get_rand_val(), get_rand_val(), get_rand_val(),
                                                             fabs(get_rand_val()), fabs(get_rand_val())));
                break;
            }
            case 2: {
                vec.emplace_back(std::make_shared<ZHelix>(get_rand_val(), get_rand_val(), get_rand_val(),
                                                          fabs(get_rand_val()), get_rand_val()));
                break;
            }
        }
    }

    std::cout << "Generated vector with " << vec.size() << " elements\n\n";

    // Vector 2 according to task
    vector <shared_ptr<XYCircle>> vec2;

    for (const auto & item : vec) {
        item->print();
        const auto & pt = item->getPoint(M_PI / 4);
        std::cout << "   Point: " << std::get<0>(pt) << ", " << std::get<1>(pt) << ", " << std::get<2>(pt) << "\n";
        const auto & dv = item->getDerivative(M_PI / 4);
        std::cout << "   Derivative: " << std::get<0>(dv) << ", " << std::get<1>(dv) << ", " << std::get<2>(dv) << "\n\n";
        auto cptr = std::dynamic_pointer_cast<XYCircle>(item);
        if (cptr != nullptr) {
            vec2.emplace_back(cptr);
        }
    }

    std::cout << "Sorted list of circles with " << vec2.size() << " elements\n\n";

    std::sort(vec2.begin(), vec2.end(),
              [](const shared_ptr<XYCircle> & a, const shared_ptr<XYCircle> & b)
              {
                 return a->getRadius() < b->getRadius();
              });


    for (const auto & item : vec2) {
        item->print();
        const auto & pt = item->getPoint(M_PI / 4);
        std::cout << "   Point: " << std::get<0>(pt) << ", " << std::get<1>(pt) << ", " << std::get<2>(pt) << "\n";
        const auto & dv = item->getDerivative(M_PI / 4);
        std::cout << "   Derivative: " << std::get<0>(dv) << ", " << std::get<1>(dv) << ", " << std::get<2>(dv) << "\n\n";
    }

    auto add_radius = [](double a, const shared_ptr<XYCircle> & b)
    {
        return a + b->getRadius();
    };

    double sum = std::accumulate(vec2.begin(), vec2.end(), 0., add_radius);

    std::cout << "Sum of radii " << sum << "\n";

    return 0;
}
