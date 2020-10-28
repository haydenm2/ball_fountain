#include "OSGWidgetUtils.hpp"

namespace osgwidgetutils
{

osg::Vec4 hue_to_osg_rgba_decimal(int hue)
{
    float r{0};
    float g{0};
    float b{0};
    float alpha{1};
    float hueSegment{float(hue/60.0)};
    float x{float(1 - fabs(fmod(hueSegment, 2)-1))};
    if(0<=hueSegment && hueSegment<1)
    {
        r = 1;
        g = x;
        b = 0;
    }
    else if(1<=hueSegment && hueSegment<2)
    {
        r = x;
        g = 1;
        b = 0;
    }
    else if(2<=hueSegment && hueSegment<3)
    {
        r = 0;
        g = 1;
        b = x;
    }
    else if(3<=hueSegment && hueSegment<4)
    {
        r = 0;
        g = x;
        b = 1;
    }
    else if(4<=hueSegment && hueSegment<5)
    {
        r = x;
        g = 0;
        b = 1;
    }
    else if(5<=hueSegment && hueSegment<=6)
    {
        r = 1;
        g = 0;
        b = x;
    }
    else
    {
        r = 0;
        g = 0;
        b = 0;
    }

    return osg::Vec4(r, g, b, alpha);
}

float get_small_random_float()
{
    float maxMagnitude{0.01};
    return float(maxMagnitude*(std::rand()%200-100)/100.0);
}

}
