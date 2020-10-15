#ifndef BALLPHYSICS_HPP
#define BALLPHYSICS_HPP

#include "Ball.hpp"
#include <vector>

class BallPhysics
{
public:
    BallPhysics();
    ~BallPhysics();
    void add_ball(double &radius, double &mass, unsigned int &color, std::array<double, 3> &position, std::array<double, 3> &velocity, std::array<double, 3> &acceleration, double &coefficientOfRestitution);
    std::vector<Ball> balls;
private:
    unsigned int ballCount{0};

};

#endif
