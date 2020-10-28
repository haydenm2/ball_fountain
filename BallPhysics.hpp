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
    BallPhysics(float boxBoundSizeInput=30, float fluidDensityInput=0, float gravityInput=-9.81);

    void add_ball(float &radius, float &mass, unsigned int &color, Eigen::Vector3f &position, Eigen::Vector3f &velocity, float &coefficientOfRestitution);
    void update(float deltaTime);
    void update_ball(unsigned int &index, float &radius, float &mass, unsigned int &color, Eigen::Vector3f &position, Eigen::Vector3f &velocity, Eigen::Vector3f &acceleration, float &coefficientOfRestitution);
    void remove_ball();
    void clear_balls();

    Ball* get_ball_ptr(int index);

    float get_gravity();
    unsigned int get_ball_count();
    unsigned int get_max_ball_count();
    float get_box_size();
    float get_drag_coefficient();
    float get_fluid_density();

    void set_gravity(float newGravity);
    void set_box_size(float newSize);
    void set_drag_coefficient(float newCoefficient);
    void set_fluid_density(float newDensity);

protected:
    std::vector<Ball> balls;
    unsigned int ballReplaceIndex{0};
    float gravity{-9.81};
    unsigned int ballCount{0};
    unsigned int maxBallCount{100};
    float boxBoundSize{30};
    float dragCoefficient{0.5};
    float fluidDensity{0};

private:
    void update_box_collisions(Ball &ball);
    void update_ball_collisions(Ball &ball, int &ballIndex);
};

#endif
