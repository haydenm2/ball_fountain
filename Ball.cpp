#include "Ball.hpp"

Ball::Ball()
{
}

Ball::Ball(double radiusInit, double massInit, unsigned int colorInit, Eigen::Vector3d positionInit, Eigen::Vector3d velocityInit, Eigen::Vector3d accelerationInit, double coefficientOfRestitutionInit) :
    radius{radiusInit},
    mass{massInit},
    color{colorInit},
    position{positionInit},
    velocity{velocityInit},
    acceleration{accelerationInit},
    coefficientOfRestitution{coefficientOfRestitutionInit}
{
}

Ball::~Ball()
{
}
