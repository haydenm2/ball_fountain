#include "BallPhysics.hpp"


BallPhysics::BallPhysics(float boxBoundSizeInput, float fluidDensityInput, float gravityInput): boxBoundSize{boxBoundSizeInput}, fluidDensity{fluidDensityInput}, gravity{gravityInput}
{
}

void BallPhysics::add_ball()
{
    float velocityMagnitude{newBallVelocity.norm()};
    Eigen::Vector3f dragForce{Eigen::Vector3f{0.0, 0.0, 0.0}};
    if(velocityMagnitude > 0)
        dragForce = -(0.5*fluidDensity*pow(velocityMagnitude, 2)*dragCoefficient*(M_PI*pow(newBallRadius, 2)))/newBallMass*newBallVelocity/velocityMagnitude;

    Eigen::Vector3f newBallAcceleration{Eigen::Vector3f{0.0, 0.0, gravity} + dragForce};
    if(ballCount < maxBallCount)
    {
        Ball newBall(newBallRadius, newBallMass, newBallColor, newBallPosition, newBallVelocity, newBallAcceleration, newBallCoefficientOfRestitution);
        this->balls.push_back(newBall);
        this->ballCount++;
    }
    else
    {
        update_ball(ballReplaceIndex, newBallAcceleration);
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

void BallPhysics::update_ball(unsigned int &index, Eigen::Vector3f &newBallAcceleration)
{
    if(this->ballCount >= index)
    {
        this->balls[index].radius = newBallRadius;
        this->balls[index].mass = newBallMass;
        this->balls[index].color = newBallColor;
        this->balls[index].position = newBallPosition;
        this->balls[index].velocity = newBallVelocity;
        this->balls[index].acceleration = newBallAcceleration;
        this->balls[index].coefficientOfRestitution = newBallCoefficientOfRestitution;
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

float BallPhysics::get_new_ball_radius()
{
    return this->newBallRadius;
}

float BallPhysics::get_new_ball_mass()
{
    return this->newBallMass;
}

unsigned int BallPhysics::get_new_ball_color()
{
    return this->newBallColor;
}

Eigen::Vector3f BallPhysics::get_new_ball_position()
{
    return this->newBallPosition;
}

Eigen::Vector3f BallPhysics::get_new_ball_velocity()
{
    return this->newBallVelocity;
}

float BallPhysics::get_new_ball_coefficient_of_restitution()
{
    return this->newBallCoefficientOfRestitution;
}

void BallPhysics::set_new_ball_parameters(float newRadius, float newMass, unsigned int newColor, Eigen::Vector3f newPosition, Eigen::Vector3f newVelocity, float newCoefficient)
{
    this->newBallRadius = newRadius;
    this->newBallMass = newMass;
    this->newBallColor = newColor;
    this->newBallPosition = newPosition;
    this->newBallVelocity = newVelocity;
    this->newBallCoefficientOfRestitution = newCoefficient;
}

void BallPhysics::set_new_ball_radius(float newRadius)
{
    this->newBallRadius = newRadius;
}

void BallPhysics::set_new_ball_mass(float newMass)
{
    this->newBallMass = newMass;
}

void BallPhysics::set_new_ball_color(unsigned int newColor)
{
    this->newBallColor = newColor;
}

void BallPhysics::set_new_ball_height(float newHeight)
{
    this->newBallPosition[2] = newHeight;
}

void BallPhysics::set_new_ball_velocity(Eigen::Vector3f newVelocity)
{
    this->newBallVelocity = newVelocity;
}

void BallPhysics::set_new_ball_coefficient_of_restitution(float newCoefficient)
{
    this->newBallCoefficientOfRestitution = newCoefficient;
}


