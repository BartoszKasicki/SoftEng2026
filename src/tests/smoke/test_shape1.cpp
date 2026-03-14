#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>
#include "ShapeFactory.h"

TEST(test_shape1, AddFunction)
{
    bool res = true;
    ShapeParam<float> param;
    res = param.set_attrib(ShapeParamIndex::PARAM_RADIUS, 1.f);
    ASSERT_NE(res, false);

    param.type = ShapeType::PT_CIRCLE;

    res = param.validate();
    ASSERT_NE(res, false);

    auto shape =
        std::unique_ptr<IShape<float>>(ShapeFactory<float>::create(param));
    ASSERT_NE(shape, nullptr);

#if 0
    ShapeResult<float> data=shape->compute();
    float area=data.get_attrib(ShapeResultIndex::RESULT_AREA);
    ASSERT_NE(area, 0.f);
#endif

    shape.reset(nullptr);
    ASSERT_EQ(shape.get(), nullptr);
}

TEST(test_torus, Compute)
{
    ShapeParam<double> param;

    param.set_attrib(PARAM_RADIUS, 5.0);
    param.set_attrib(PARAM_RADIUS_2, 2.0);

    Torus<double> torus(param);

    ShapeResult<double> result = torus.compute();

    double volume = result.get_attrib(RESULT_VOLUME);
    double surface = result.get_attrib(RESULT_SURFACE);

    const double PI = M_PI;

    double expected_volume = 2 * PI * PI * 5.0 * 2.0 * 2.0;
    double expected_surface = 4 * PI * PI * 5.0 * 2.0;

    ASSERT_NEAR(volume, expected_volume, 1e-6);
    ASSERT_NEAR(surface, expected_surface, 1e-6);
}

TEST(test_torus, PrintContainsValues)
{
    ShapeParam<double> param;

    param.set_attrib(PARAM_RADIUS, 5.0);
    param.set_attrib(PARAM_RADIUS_2, 2.0);

    Torus<double> torus(param);

    std::string text = torus.print();

    ASSERT_NE(text.find("Torus"), std::string::npos);
    ASSERT_NE(text.find("5"), std::string::npos);
    ASSERT_NE(text.find("2"), std::string::npos);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
