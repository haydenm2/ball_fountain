#include "gtest/gtest.h"
#include "OSGWidgetUtils.hpp"
#include "unitTestUtils.hpp"


TEST(OSGUtilsTests, WhenConverting0HueToRGB_ExpectRed)
{
    int inputHue{0};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting60HueToRGB_ExpectRedGreen)
{
    int inputHue{60};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting120HueToRGB_ExpectGreen)
{
    int inputHue{120};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting180HueToRGB_ExpectGreenBlue)
{
    int inputHue{180};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting240HueToRGB_ExpectBlue)
{
    int inputHue{240};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting300HueToRGB_ExpectRedBlue)
{
    int inputHue{300};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(1.0f, 0.0f, 1.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting360HueToRGB_ExpectRed)
{
    int inputHue{360};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConvertingOutOfRangeHueToRGB_ExpectBlack)
{
    int inputHue{600};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenRequestingSmallRandomNumber_ExpectSmallValue)
{
    float randomValue = osgwidgetutils::get_small_random_float();
    EXPECT_NEAR(randomValue, 0.0, 0.01);
}
