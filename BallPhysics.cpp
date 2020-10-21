#include "BallPhysics.hpp"

BallPhysics::BallPhysics()
{
}

BallPhysics::~BallPhysics()
{
}

void BallPhysics::add_ball(float &radius, float &mass, unsigned int &color, Eigen::Vector3f &position, Eigen::Vector3f &velocity, Eigen::Vector3f &acceleration, float &coefficientOfRestitution)
{
    if(ballCount < maxBallCount)
    {
        Ball newBall(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
        this->balls.push_back(newBall);
        this->ballCount++;
    }
    else
    {
        update_ball(ballReplaceIndex, radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
        if(ballReplaceIndex < maxBallCount)
            ballReplaceIndex++;
        else
            ballReplaceIndex = 0;
    }
}

void BallPhysics::update_ball(unsigned int &index, float &radius, float &mass, unsigned int &color, Eigen::Vector3f &position, Eigen::Vector3f &velocity, Eigen::Vector3f &acceleration, float &coefficientOfRestitution)
{
    this->balls[index].radius = radius;
    this->balls[index].mass = mass;
    this->balls[index].color = color;
    this->balls[index].position = position;
    this->balls[index].velocity = velocity;
    this->balls[index].acceleration = acceleration;
    this->balls[index].coefficientOfRestitution = coefficientOfRestitution;
}


void BallPhysics::update(float deltaTime)
{
    for(int ballIndex{0}; ballIndex < ballCount; ballIndex++)
    {
        Ball &ball = balls[ballIndex];
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
                ball.velocity[index] = ball.velocity[index] + ball.acceleration[index]*deltaTime;
                ball.position[index] = ball.position[index] + ball.velocity[index]*deltaTime + 0.5*ball.acceleration[index]*pow(deltaTime, 2);
            }
        }
        for(int ballCollisionIndex{0}; ballCollisionIndex < ballCount; ballCollisionIndex++)
        {
            if(ballCollisionIndex == ballIndex)
                continue;
            else
            {
                Ball &ballCollisionCandidate = balls[ballCollisionIndex];
                Eigen::Vector3f positionDifference = ball.position - ballCollisionCandidate.position;
                float offsetFromBall = positionDifference.norm();
                if(offsetFromBall < (ball.radius + ballCollisionCandidate.radius))
                {
                    ballCollisionCandidate.position = ball.position - positionDifference/offsetFromBall*(ball.radius + ballCollisionCandidate.radius);
                    Eigen::Vector3f velocityDifference = ball.velocity - ballCollisionCandidate.velocity;
                    float totalMass = ball.mass + ballCollisionCandidate.mass;
                    ball.velocity = ball.coefficientOfRestitution*(ball.velocity - 2*ballCollisionCandidate.mass/totalMass*velocityDifference.dot(positionDifference)/pow(positionDifference.norm(),2)*positionDifference);
                    ballCollisionCandidate.velocity = ballCollisionCandidate.coefficientOfRestitution*(ballCollisionCandidate.velocity - 2*ball.mass/totalMass*(-velocityDifference).dot(-positionDifference)/pow(positionDifference.norm(),2)*(-positionDifference));
                }
            }
        }
    }
}
