#include "gtest/gtest.h"
#include "BallPhysics.hpp"

void EXPECT_VECTOR3_FLOAT_EQ(Eigen::Vector3f inputVector, Eigen::Vector3f truthVector)
{
    for(float index = 0; index < 3; index++)
    {
        EXPECT_EQ(inputVector[index], truthVector[index]);
    }
}

TEST(BallTests, WhenInstantiatingBall_ExpectCorrectInitialization)
{
    float radiusExpected{1};
    float massExpected{1};
    unsigned int colorExpected{0};
    Eigen::Vector3f positionExpected{0, 0, 0};
    Eigen::Vector3f velocityExpected{0, 0, 0};
    Eigen::Vector3f accelerationExpected{0, 0, 0};
    float coefficientOfRestitutionExpected{0};

    Ball ball;
    EXPECT_EQ(ball.radius, radiusExpected);
    EXPECT_EQ(ball.mass, massExpected);
    EXPECT_EQ(ball.color, colorExpected);
    EXPECT_VECTOR3_FLOAT_EQ(ball.position, positionExpected);
    EXPECT_VECTOR3_FLOAT_EQ(ball.velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(ball.acceleration, accelerationExpected);
    EXPECT_EQ(ball.coefficientOfRestitution, coefficientOfRestitutionExpected);
}

TEST(BallTests, WhenInstantiatingBallWithValues_ExpectCorrectInitialization)
{
    float radius{10};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{1, 2, 3};
    Eigen::Vector3f velocity{4, 5, 6};
    Eigen::Vector3f acceleration{7, 8, 9};
    float coefficientOfRestitution{2};

    Ball ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    EXPECT_EQ(ball.radius, radius);
    EXPECT_EQ(ball.mass, mass);
    EXPECT_EQ(ball.color, color);
    EXPECT_VECTOR3_FLOAT_EQ(ball.position, position);
    EXPECT_VECTOR3_FLOAT_EQ(ball.velocity, velocity);
    EXPECT_VECTOR3_FLOAT_EQ(ball.acceleration, acceleration);
    EXPECT_EQ(ball.coefficientOfRestitution, coefficientOfRestitution);
}

TEST(PhysicsTests, WhenAddingBall_ExpectCorrectInitialization)
{
    float radius{10};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{1, 2, 3};
    Eigen::Vector3f velocity{4, 5, 6};
    Eigen::Vector3f acceleration{7, 8, 9};
    float coefficientOfRestitution{2};

    BallPhysics physics;
    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    EXPECT_EQ(physics.balls[0].radius, radius);
    EXPECT_EQ(physics.balls[0].mass, mass);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, position);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocity);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, acceleration);
    EXPECT_EQ(physics.balls[0].coefficientOfRestitution, coefficientOfRestitution);
}

TEST(PhysicsTests, WhenAddingMultipleBalls_ExpectCorrectInitializationOfAllBalls)
{
    int numberOfBalls{100};
    float radius{10};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{1, 2, 3};
    Eigen::Vector3f velocity{4, 5, 6};
    Eigen::Vector3f acceleration{7, 8, 9};
    float coefficientOfRestitution{2};

    BallPhysics physics;

    for(int index{0}; index < numberOfBalls; index++)
    {
        physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    }

    for(int index{0}; index < numberOfBalls; index++)
    {
        EXPECT_EQ(physics.balls[index].radius, radius);
        EXPECT_EQ(physics.balls[index].mass, mass);
        EXPECT_EQ(physics.balls[index].color, color);
        EXPECT_VECTOR3_FLOAT_EQ(physics.balls[index].position, position);
        EXPECT_VECTOR3_FLOAT_EQ(physics.balls[index].velocity, velocity);
        EXPECT_VECTOR3_FLOAT_EQ(physics.balls[index].acceleration, acceleration);
        EXPECT_EQ(physics.balls[index].coefficientOfRestitution, coefficientOfRestitution);
    }
}

TEST(PhysicsTests, WhenUpdatingGravityPhysicsOverTimeStep_ExpectCorrectPosition)
{
    BallPhysics physics;

    float radius{10};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 1000};
    Eigen::Vector3f velocity{1, 1, 1};
    Eigen::Vector3f acceleration{0, 0, physics.gravity};
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    float deltaTime{5};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected = acceleration;
    Eigen::Vector3f velocityExpected = velocity + accelerationExpected*deltaTime;
    Eigen::Vector3f positionExpected = position + velocityExpected*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingNoPhysicsOverTimeStep_ExpectNoChange)
{
    BallPhysics physics;

    float radius{10};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{10, 10, 10};
    Eigen::Vector3f velocity{0, 0, 0};
    Eigen::Vector3f acceleration{0, 0, 0};
    float coefficientOfRestitution{0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    float deltaTime{10};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected = acceleration;
    Eigen::Vector3f velocityExpected = velocity + accelerationExpected*deltaTime;
    Eigen::Vector3f positionExpected = position + velocityExpected*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingSequentialBallsTwoTimeSteps_ExpectCorrectPositions)
{
    BallPhysics physics;

    float radius{1};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 1000};
    Eigen::Vector3f velocity{1, 1, 1};
    Eigen::Vector3f acceleration{0, 0, physics.gravity};
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    float deltaTime{3};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected1 = acceleration;
    Eigen::Vector3f velocityExpected1 = velocity + accelerationExpected1*deltaTime;
    Eigen::Vector3f positionExpected1 = position + velocityExpected1*deltaTime + 0.5*accelerationExpected1*pow(deltaTime, 2);

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    physics.update(deltaTime);

    velocityExpected1 = velocityExpected1 + accelerationExpected1*deltaTime;
    positionExpected1 = positionExpected1 + velocityExpected1*deltaTime + 0.5*accelerationExpected1*pow(deltaTime, 2);

    Eigen::Vector3f accelerationExpected2 = acceleration;
    Eigen::Vector3f velocityExpected2 = velocity + accelerationExpected2*deltaTime;
    Eigen::Vector3f positionExpected2 = position + velocityExpected2*deltaTime + 0.5*accelerationExpected2*pow(deltaTime, 2);

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected1);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocityExpected1);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, positionExpected1);

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].acceleration, accelerationExpected2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].velocity, velocityExpected2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].position, positionExpected2);
}

TEST(PhysicsTests, WhenUpdatingGroundBallCollision_ExpectCorrectPositionAndOppositeVelocity)
{
    BallPhysics physics;

    float radius{2};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 1.99};
    Eigen::Vector3f velocity{0, 0, -10};
    Eigen::Vector3f acceleration{0, 0, physics.gravity};
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3f velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, physics.balls[0].radius};

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallCollisionInGround_ExpectRadiusPositionAboveGroundAndOppositeVelocity)
{
    BallPhysics physics;

    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, -1};
    Eigen::Vector3f velocity{0, 0, -10};
    Eigen::Vector3f acceleration{0, 0, physics.gravity};
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3f velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, physics.balls[0].radius};

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallBelowGround_ExpectRadiusPositionAboveGroundAndOppositeVelocity)
{
    BallPhysics physics;

    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, -100};
    Eigen::Vector3f velocity{0, 0, -10};
    Eigen::Vector3f acceleration{0, 0, physics.gravity};
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3f velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, physics.balls[0].radius};

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallGroundCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionAboveGroundAndDepletedOppositeVelocity)
{
    BallPhysics physics;

    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, -100};
    Eigen::Vector3f velocity{0, 0, -10};
    Eigen::Vector3f acceleration{0, 0, physics.gravity};
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3f velocityExpected{0, 0, -coefficientOfRestitution*velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, physics.balls[0].radius};

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallXWallCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionInsideBoxAndDepletedOppositeVelocity)
{
    BallPhysics physics;

    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{100, 0, 10};
    Eigen::Vector3f velocity{10, 0, 0};
    Eigen::Vector3f acceleration{0, 0, physics.gravity};
    float coefficientOfRestitution{0.3};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3f velocityExpected{-coefficientOfRestitution*velocity[0], 0, 0};
    Eigen::Vector3f positionExpected{(physics.boxBoundSize-physics.balls[0].radius), 0, 10};

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallYWallCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionInsideBoxAndDepletedOppositeVelocity)
{
    BallPhysics physics;

    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, -100, 10};
    Eigen::Vector3f velocity{0, -10, 0};
    Eigen::Vector3f acceleration{0, 0, physics.gravity};
    float coefficientOfRestitution{0.7};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3f velocityExpected{0, -coefficientOfRestitution*velocity[1], 0};
    Eigen::Vector3f positionExpected{0, -(physics.boxBoundSize-physics.balls[0].radius), 10};

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBalltoBallCollisionWithTrivialCoefficientOfRestitution_ExpectPositionChangeToRadiusAndCorrectVelocity)
{
    BallPhysics physics;

    float radius1{4};
    float mass1{5};
    unsigned int color1{128};
    Eigen::Vector3f position1{0, 0, 100};
    Eigen::Vector3f velocity1{0, 10, 0};
    Eigen::Vector3f acceleration1{0, 0, 0};
    float coefficientOfRestitution1{1.0};

    physics.add_ball(radius1, mass1, color1, position1, velocity1, acceleration1, coefficientOfRestitution1);

    float radius2{5};
    float mass2{2};
    unsigned int color2{128};
    Eigen::Vector3f position2{1, 1, 101};
    Eigen::Vector3f velocity2{0, -10, 0};
    Eigen::Vector3f acceleration2{0, 0, 0};
    float coefficientOfRestitution2{1.0};

    physics.add_ball(radius2, mass2, color2, position2, velocity2, acceleration2, coefficientOfRestitution2);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f positionDifference = position1 - position2;
    float offsetFromBall = positionDifference.norm();
    Eigen::Vector3f velocityDifference = velocity1 - velocity2;
    float totalMass = mass1 + mass2;

    Eigen::Vector3f acceleration1Expected = acceleration1;
    Eigen::Vector3f velocity1Expected = coefficientOfRestitution1*(velocity1 - 2*mass2/totalMass*velocityDifference.dot(positionDifference)/pow(positionDifference.norm(),2)*positionDifference);
    Eigen::Vector3f position1Expected = position1;

    Eigen::Vector3f acceleration2Expected = acceleration2;
    Eigen::Vector3f velocity2Expected = coefficientOfRestitution2*(velocity2 - 2*mass1/totalMass*(-velocityDifference).dot(-positionDifference)/pow(positionDifference.norm(),2)*(-positionDifference));
    Eigen::Vector3f position2Expected = position2 - positionDifference/offsetFromBall*(radius1 + radius2);;

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, acceleration1Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocity1Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, position1Expected);

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].acceleration, acceleration2Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].velocity, velocity2Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].position, position2Expected);
}
