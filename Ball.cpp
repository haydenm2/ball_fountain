#include "Ball.hpp"

Ball::Ball()
{
}

Ball::Ball(double radiusInit, double massInit, unsigned int colorInit, std::array<double, 3> positionInit, std::array<double, 3> velocityInit, std::array<double, 3> accelerationInit, double coefficientOfRestitutionInit) :
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
