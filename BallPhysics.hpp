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

    void add_ball(float &radius, float &mass, unsigned int &color, Eigen::Vector3f &position, Eigen::Vector3f &velocity, Eigen::Vector3f &acceleration, float &coefficientOfRestitution);
    void update_ball(unsigned int &index, float &radius, float &mass, unsigned int &color, Eigen::Vector3f &position, Eigen::Vector3f &velocity, Eigen::Vector3f &acceleration, float &coefficientOfRestitution);
    void update(float deltaTime);

    std::vector<Ball> balls;
    float gravity{-9.81};
    unsigned int ballCount{0};
    unsigned int maxBallCount{100};
    float boxBoundSize{30};
    unsigned int ballReplaceIndex{0};


private:

};

#endif
