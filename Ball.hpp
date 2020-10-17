#ifndef BALL_HPP
#define BALL_HPP

#include <osg/Vec4>
#include <eigen3/Eigen/Dense>


class Ball
{
public:
    Ball();
    Ball(double radius, double mass, unsigned int color, Eigen::Vector3d position, Eigen::Vector3d velocity, Eigen::Vector3d acceleration, double coefficientOfRestitution);
    ~Ball();
    double radius{1};
    double mass{1};
    unsigned int color{0};
    Eigen::Vector3d position{0.0, 0.0, 0.0};
    Eigen::Vector3d velocity{0.0, 0.0, 0.0};
    Eigen::Vector3d acceleration{0.0, 0.0, 0.0};
    double coefficientOfRestitution{0.0};
private:

};

#endif
