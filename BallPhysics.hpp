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

    void add_ball();
    void update_ball(unsigned int &index, Eigen::Vector3f &newBallAcceleration);
    void update(float deltaTime);
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

    float get_new_ball_radius();
    float get_new_ball_mass();
    unsigned int get_new_ball_color();
    Eigen::Vector3f get_new_ball_position();
    Eigen::Vector3f get_new_ball_velocity();
    float get_new_ball_coefficient_of_restitution();

    void set_new_ball_parameters(float newRadius, float newMass, unsigned int newColor, Eigen::Vector3f newPosition, Eigen::Vector3f newVelocity, float newCoefficient);
    void set_new_ball_radius(float newRadius);
    void set_new_ball_mass(float newMass);
    void set_new_ball_color(unsigned int newColor);
    void set_new_ball_height(float newHeight);
    void set_new_ball_velocity(Eigen::Vector3f newVelocity);
    void set_new_ball_coefficient_of_restitution(float newCoefficient);

protected:
    std::vector<Ball> balls;
    unsigned int ballReplaceIndex{0};
    float gravity{-9.81};
    unsigned int ballCount{0};
    unsigned int maxBallCount{100};
    float boxBoundSize{30};
    float dragCoefficient{0.5};
    float fluidDensity{0};

    float newBallRadius{0.5};
    float newBallMass{5};
    unsigned int newBallColor{0};
    Eigen::Vector3f newBallPosition{0.0, 0.0, 0.0};
    Eigen::Vector3f newBallVelocity{0.0, 0.0, 20.0};
    float newBallCoefficientOfRestitution{0.7};

private:
    void update_box_collisions(Ball &ball);
    void update_ball_collisions(Ball &ball, int &ballIndex);
};

#endif
