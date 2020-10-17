#ifndef BALLPHYSICS_HPP
#define BALLPHYSICS_HPP

#include "Ball.hpp"
#include <vector>
#include <math.h>
#include <iostream>
#include <eigen3/Eigen/Dense>

class BallPhysics
{
public:
    BallPhysics();
    ~BallPhysics();

    void add_ball(double &radius, double &mass, unsigned int &color, Eigen::Vector3d &position, Eigen::Vector3d &velocity, Eigen::Vector3d &acceleration, double &coefficientOfRestitution);
    void update(double deltaTime);

    std::vector<Ball> balls;
    float gravity{-9.81};
    unsigned int ballCount{0};
    double boxBoundSize{30};


private:

};

#endif
