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
    BallPhysics(float boxBoundSizeInput=30, float fluidDensityInput=0);
    ~BallPhysics();

    void add_ball(float &radius, float &mass, unsigned int &color, Eigen::Vector3f &position, Eigen::Vector3f &velocity, float &coefficientOfRestitution);
    void update(float deltaTime);
    void remove_ball();

    std::vector<Ball> balls;
    float gravity{-9.81};
    unsigned int ballCount{0};
    unsigned int maxBallCount{20};
    float boxBoundSize{30};
    unsigned int ballReplaceIndex{0};
    float dragCoefficient{0.5};
    float fluidDensity{0};


private:
    void update_ball(unsigned int &index, float &radius, float &mass, unsigned int &color, Eigen::Vector3f &position, Eigen::Vector3f &velocity, Eigen::Vector3f &acceleration, float &coefficientOfRestitution);

};

#endif
