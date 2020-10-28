#include "BallPhysics.hpp"


BallPhysics::BallPhysics(float boxBoundSizeInput, float fluidDensityInput, float gravityInput): boxBoundSize{boxBoundSizeInput}, fluidDensity{fluidDensityInput}, gravity{gravityInput}
{
}

void BallPhysics::add_ball(float &radius, float &mass, unsigned int &color, Eigen::Vector3f &position, Eigen::Vector3f &velocity, float &coefficientOfRestitution)
{
    float velocityMagnitude{velocity.norm()};
    Eigen::Vector3f dragForce{Eigen::Vector3f{0.0, 0.0, 0.0}};
    if(velocityMagnitude > 0)
        dragForce = -(0.5*fluidDensity*pow(velocityMagnitude, 2)*dragCoefficient*(M_PI*pow(radius, 2)))/mass*velocity/velocityMagnitude;

    Eigen::Vector3f acceleration{Eigen::Vector3f{0.0, 0.0, gravity} + dragForce};
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

void BallPhysics::update(float deltaTime)
{
    for(int ballIndex{0}; ballIndex < ballCount; ballIndex++)
    {
        Ball &ball = balls[ballIndex];
        float velocityMagnitude = ball.velocity.norm();
        Eigen::Vector3f dragForce = Eigen::Vector3f{0.0, 0.0, 0.0};;
        if(velocityMagnitude > 0)
            dragForce = -(0.5*fluidDensity*pow(velocityMagnitude, 2)*dragCoefficient*(M_PI*pow(ball.radius, 2)))/ball.mass*ball.velocity/velocityMagnitude;
        ball.acceleration = Eigen::Vector3f{0.0, 0.0, gravity} + dragForce;
        ball.velocity = ball.velocity + ball.acceleration*deltaTime;
        ball.position = ball.position + ball.velocity*deltaTime + 0.5*ball.acceleration*pow(deltaTime, 2);
        update_box_collisions(ball);
        update_ball_collisions(ball, ballIndex);
    }
}

void BallPhysics::update_ball(unsigned int &index, float &radius, float &mass, unsigned int &color, Eigen::Vector3f &position, Eigen::Vector3f &velocity, Eigen::Vector3f &acceleration, float &coefficientOfRestitution)
{
    if(this->ballCount >= index)
    {
        this->balls[index].radius = radius;
        this->balls[index].mass = mass;
        this->balls[index].color = color;
        this->balls[index].position = position;
        this->balls[index].velocity = velocity;
        this->balls[index].acceleration = acceleration;
        this->balls[index].coefficientOfRestitution = coefficientOfRestitution;
    }
}

void BallPhysics::remove_ball()
{
    if(this->ballCount > 0)
    {
        balls.pop_back();
        ballCount--;
    }
}

void BallPhysics::clear_balls()
{
    balls.clear();
    ballCount = 0;
}

void BallPhysics::update_box_collisions(Ball &ball)
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
    }
}

void BallPhysics::update_ball_collisions(Ball &ball, int &ballIndex)
{
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

Ball* BallPhysics::get_ball_ptr(int index)
{
    return &balls[index];
}

float BallPhysics::get_gravity()
{
   return this->gravity;
}

unsigned int BallPhysics::get_ball_count()
{
    return this->ballCount;
}

unsigned int BallPhysics::get_max_ball_count()
{
    return this->maxBallCount;
}

float BallPhysics::get_box_size()
{
    return this->boxBoundSize;
}

float BallPhysics::get_drag_coefficient()
{
    return this->dragCoefficient;
}

float BallPhysics::get_fluid_density()
{
    return this->fluidDensity;
}

void BallPhysics::set_gravity(float newGravity)
{
    this->gravity = newGravity;
}

void BallPhysics::set_box_size(float newSize)
{
    this->boxBoundSize = newSize;
}

void BallPhysics::set_drag_coefficient(float newCoefficient)
{
    this->dragCoefficient = newCoefficient;
}

void BallPhysics::set_fluid_density(float newDensity)
{
    this->fluidDensity = newDensity;
}

