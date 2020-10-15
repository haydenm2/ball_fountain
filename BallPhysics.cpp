#include "BallPhysics.hpp"

BallPhysics::BallPhysics()
{
}

BallPhysics::~BallPhysics()
{
}

void BallPhysics::add_ball(double &radius, double &mass, unsigned int &color, std::array<double, 3> &position, std::array<double, 3> &velocity, std::array<double, 3> &acceleration, double &coefficientOfRestitution)
{
    Ball newBall(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    this->balls.push_back(newBall);
}
