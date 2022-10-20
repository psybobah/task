
#include <gtest/gtest.h>
#include "task.hpp"
#include <iostream>


TEST(TaskTest, TaskTests) {

    {
        double sine_pi4 = sin(M_PI / 4);
        double cosie_pi4 = cos(M_PI / 4);
        double rad1 = 10000.123;
        double rad2 = 100000.12312312;
        double step = 10.12312312;
        double xc = 1.0, yc = 2.0, zc = 3.0;

        std::cout << sine_pi4 - cosie_pi4 << "\n";

        vector <shared_ptr<GeomEntity>> vec;

        size_t vec_idx = 0;

        // Testing circle
        ASSERT_THROW(vec.emplace_back(std::make_shared<XYCircle>(xc, yc, zc, -1.)), std::invalid_argument);

        ASSERT_NO_THROW(vec.emplace_back(std::make_shared<XYCircle>(xc, yc, zc, rad1)));

        EXPECT_EQ(vec.size(), vec_idx + 1);

        {
            auto [x, y, z] = vec[vec_idx]->getPoint(M_PI / 4);
            EXPECT_LE(fabs(x - cosie_pi4 * rad1 - xc), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(y - sine_pi4 * rad1 - yc), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(z - zc), std::numeric_limits<double>::epsilon());
        }

        {
            auto [x, y, z] = vec[vec_idx]->getDerivative(M_PI / 4);
            EXPECT_LE(fabs(x + sine_pi4 * rad1), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(y - cosie_pi4 * rad1), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(z - 0.), std::numeric_limits<double>::epsilon());
        }

        vec_idx++;

        // Testing ellipse
        ASSERT_THROW(vec.emplace_back(std::make_shared<XYEllipse>(xc, yc, zc, -1., rad2)), std::invalid_argument);
        ASSERT_THROW(vec.emplace_back(std::make_shared<XYEllipse>(xc, yc, zc, rad1, -1.)), std::invalid_argument);

        ASSERT_NO_THROW(vec.emplace_back(std::make_shared<XYEllipse>(xc, yc, zc, rad1, rad2)));

        EXPECT_EQ(vec.size(), vec_idx + 1);

        {
            auto [x, y, z] = vec[vec_idx]->getPoint(M_PI / 4);
            EXPECT_LE(fabs(x - cosie_pi4 * rad1 - xc), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(y - sine_pi4 * rad2 - yc), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(z - zc), std::numeric_limits<double>::epsilon());
        }

        {
            auto [x, y, z] = vec[vec_idx]->getDerivative(M_PI / 4);
            EXPECT_LE(fabs(x + sine_pi4 * rad1), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(y - cosie_pi4 * rad2), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(z - 0.), std::numeric_limits<double>::epsilon());
        }

        vec_idx++;

        // Testing helix
        ASSERT_THROW(vec.emplace_back(std::make_shared<ZHelix>(xc, yc, zc, -1., step)), std::invalid_argument);

        ASSERT_NO_THROW(vec.emplace_back(std::make_shared<ZHelix>(xc, yc, zc, rad1, step)));

        EXPECT_EQ(vec.size(), vec_idx + 1);

        {
            auto [x, y, z] = vec[vec_idx]->getPoint(M_PI / 4);
            EXPECT_LE(fabs(x - cosie_pi4 * rad1 - xc), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(y - sine_pi4 * rad1 - yc), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(z - step / 8. - zc), std::numeric_limits<double>::epsilon());
        }

        {
            auto [x, y, z] = vec[vec_idx]->getDerivative(M_PI / 4);
            EXPECT_LE(fabs(x + sine_pi4 * rad1), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(y - cosie_pi4 * rad1), std::numeric_limits<double>::epsilon() * 2);
            EXPECT_LE(fabs(z - 1. / 2. / M_PI * step), std::numeric_limits<double>::epsilon());
        }
    }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
