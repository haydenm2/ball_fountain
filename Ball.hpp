#ifndef BALL_HPP
#define BALL_HPP

#include <array>
#include <osg/Vec4>


class Ball
{
public:
    Ball(double radius, double mass, unsigned int color, std::array<double, 3> position, std::array<double, 3> velocity, std::array<double, 3> acceleration, double coefficientOfRestitution);
    ~Ball();
    double radius{1};
    double mass{1};
    unsigned int color{0};
    std::array<double, 3> position{0.0, 0.0, 0.0};
    std::array<double, 3> velocity{0.0, 0.0, 0.0};
    std::array<double, 3> acceleration{0.0, 0.0, 0.0};
    double coefficientOfRestitution{0.0};
private:

};

#endif
