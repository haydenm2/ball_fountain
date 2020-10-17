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

void BallPhysics::update(double deltaTime)
{
    for(Ball &ball : balls)
    {
        for(int index{0}; index < 3; index++)
        {
            if(index == 2 && ball.position[index] < ball.radius)
            {
                ball.velocity[index] = ball.coefficientOfRestitution*fabs(ball.velocity[index]);
                ball.position[index] = ball.radius;
            }
            else if(index != 2 && fabs(ball.position[index]) > boxBoundSize-ball.radius)
            {
                ball.velocity[index] = -ball.coefficientOfRestitution*ball.velocity[index];
                ball.position[index] = copysign(boxBoundSize-ball.radius, ball.position[index]);
            }
            else
            {
                ball.velocity[index] = ball.velocity[index]+ball.acceleration[index]*deltaTime;
                ball.position[index] = ball.position[index]+ball.velocity[index]*deltaTime+0.5*ball.acceleration[index]*pow(deltaTime, 2);
            }
        }
    }
}
