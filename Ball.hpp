#ifndef BALL_HPP
#define BALL_HPP

#include <osg/Vec4>
#include <eigen3/Eigen/Dense>


class Ball
{
public:
    Ball();
    Ball(float radius, float mass, unsigned int color, Eigen::Vector3f position, Eigen::Vector3f velocity, Eigen::Vector3f acceleration, float coefficientOfRestitution);
    ~Ball();
    float radius{1};
    float mass{1};
    unsigned int color{0};
    Eigen::Vector3f position{0.0, 0.0, 0.0};
    Eigen::Vector3f velocity{0.0, 0.0, 0.0};
    Eigen::Vector3f acceleration{0.0, 0.0, 0.0};
    float coefficientOfRestitution{0.0};
private:

};

#endif
