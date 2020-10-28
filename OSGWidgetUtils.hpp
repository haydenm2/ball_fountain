#ifndef OSG_WIDGET_UTILS_HPP
#define OSG_WIDGET_UTILS_HPP

#include <osg/Vec4>

#include <random>

namespace osgwidgetutils
{
    osg::Vec4 hue_to_osg_rgba_decimal(int hue);
    float get_small_random_float();
}
#endif
