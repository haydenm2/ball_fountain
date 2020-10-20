#include "Ball.hpp"

Ball::Ball()
{
}

Ball::Ball(float radiusInit, float massInit, unsigned int colorInit, Eigen::Vector3f positionInit, Eigen::Vector3f velocityInit, Eigen::Vector3f accelerationInit, float coefficientOfRestitutionInit) :
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
