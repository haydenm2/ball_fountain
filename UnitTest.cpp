#include "gtest/gtest.h"
#include "BallPhysics.hpp"

void EXPECT_VECTOR3_DOUBLE_EQ(Eigen::Vector3d inputVector, Eigen::Vector3d truthVector)
{
    for(double index = 0; index < 3; index++)
    {
        EXPECT_EQ(inputVector[index], truthVector[index]);
    }
}

TEST(BallTests, WhenInstantiatingBall_ExpectCorrectInitialization)
{
    double radiusExpected{1};
    double massExpected{1};
    unsigned int colorExpected{0};
    Eigen::Vector3d positionExpected{0, 0, 0};
    Eigen::Vector3d velocityExpected{0, 0, 0};
    Eigen::Vector3d accelerationExpected{0, 0, 0};
    double coefficientOfRestitutionExpected{0};

    Ball ball;
    EXPECT_EQ(ball.radius, radiusExpected);
    EXPECT_EQ(ball.mass, massExpected);
    EXPECT_EQ(ball.color, colorExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(ball.position, positionExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(ball.velocity, velocityExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(ball.acceleration, accelerationExpected);
    EXPECT_EQ(ball.coefficientOfRestitution, coefficientOfRestitutionExpected);
}

TEST(BallTests, WhenInstantiatingBallWithValues_ExpectCorrectInitialization)
{
    double radius{10};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{1, 2, 3};
    Eigen::Vector3d velocity{4, 5, 6};
    Eigen::Vector3d acceleration{7, 8, 9};
    double coefficientOfRestitution{2};

    Ball ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    EXPECT_EQ(ball.radius, radius);
    EXPECT_EQ(ball.mass, mass);
    EXPECT_EQ(ball.color, color);
    EXPECT_VECTOR3_DOUBLE_EQ(ball.position, position);
    EXPECT_VECTOR3_DOUBLE_EQ(ball.velocity, velocity);
    EXPECT_VECTOR3_DOUBLE_EQ(ball.acceleration, acceleration);
    EXPECT_EQ(ball.coefficientOfRestitution, coefficientOfRestitution);
}

TEST(PhysicsTests, WhenAddingBall_ExpectCorrectInitialization)
{
    double radius{10};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{1, 2, 3};
    Eigen::Vector3d velocity{4, 5, 6};
    Eigen::Vector3d acceleration{7, 8, 9};
    double coefficientOfRestitution{2};

    BallPhysics physics;
    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    EXPECT_EQ(physics.balls[0].radius, radius);
    EXPECT_EQ(physics.balls[0].mass, mass);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].position, position);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].velocity, velocity);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].acceleration, acceleration);
    EXPECT_EQ(physics.balls[0].coefficientOfRestitution, coefficientOfRestitution);
}

TEST(PhysicsTests, WhenAddingMultipleBalls_ExpectCorrectInitializationOfAllBalls)
{
    int numberOfBalls{100};
    double radius{10};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{1, 2, 3};
    Eigen::Vector3d velocity{4, 5, 6};
    Eigen::Vector3d acceleration{7, 8, 9};
    double coefficientOfRestitution{2};

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
        EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[index].position, position);
        EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[index].velocity, velocity);
        EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[index].acceleration, acceleration);
        EXPECT_EQ(physics.balls[index].coefficientOfRestitution, coefficientOfRestitution);
    }
}

TEST(PhysicsTests, WhenUpdatingGravityPhysicsOverTimeStep_ExpectCorrectPosition)
{
    BallPhysics physics;

    double radius{10};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{0, 0, 1000};
    Eigen::Vector3d velocity{1, 1, 1};
    Eigen::Vector3d acceleration{0, 0, physics.gravity};
    double coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{5};
    physics.update(deltaTime);

    Eigen::Vector3d accelerationExpected = acceleration;
    Eigen::Vector3d velocityExpected = velocity + accelerationExpected*deltaTime;
    Eigen::Vector3d positionExpected = position + velocityExpected*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingNoPhysicsOverTimeStep_ExpectNoChange)
{
    BallPhysics physics;

    double radius{10};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{10, 10, 10};
    Eigen::Vector3d velocity{0, 0, 0};
    Eigen::Vector3d acceleration{0, 0, 0};
    double coefficientOfRestitution{0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{10};
    physics.update(deltaTime);

    Eigen::Vector3d accelerationExpected = acceleration;
    Eigen::Vector3d velocityExpected = velocity + accelerationExpected*deltaTime;
    Eigen::Vector3d positionExpected = position + velocityExpected*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingSequentialBallsTwoTimeSteps_ExpectCorrectPositions)
{
    BallPhysics physics;

    double radius{1};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{0, 0, 1000};
    Eigen::Vector3d velocity{1, 1, 1};
    Eigen::Vector3d acceleration{0, 0, physics.gravity};
    double coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{3};
    physics.update(deltaTime);

    Eigen::Vector3d accelerationExpected1 = acceleration;
    Eigen::Vector3d velocityExpected1 = velocity + accelerationExpected1*deltaTime;
    Eigen::Vector3d positionExpected1 = position + velocityExpected1*deltaTime + 0.5*accelerationExpected1*pow(deltaTime, 2);

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    physics.update(deltaTime);

    velocityExpected1 = velocityExpected1 + accelerationExpected1*deltaTime;
    positionExpected1 = positionExpected1 + velocityExpected1*deltaTime + 0.5*accelerationExpected1*pow(deltaTime, 2);

    Eigen::Vector3d accelerationExpected2 = acceleration;
    Eigen::Vector3d velocityExpected2 = velocity + accelerationExpected2*deltaTime;
    Eigen::Vector3d positionExpected2 = position + velocityExpected2*deltaTime + 0.5*accelerationExpected2*pow(deltaTime, 2);

    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected1);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected1);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].position, positionExpected1);

    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[1].acceleration, accelerationExpected2);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[1].velocity, velocityExpected2);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[1].position, positionExpected2);
}

TEST(PhysicsTests, WhenUpdatingGroundBallCollision_ExpectCorrectPositionAndOppositeVelocity)
{
    BallPhysics physics;

    double radius{2};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{0, 0, 1.99};
    Eigen::Vector3d velocity{0, 0, -10};
    Eigen::Vector3d acceleration{0, 0, physics.gravity};
    double coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3d accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3d velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3d positionExpected{0, 0, physics.balls[0].radius};

    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallCollisionInGround_ExpectRadiusPositionAboveGroundAndOppositeVelocity)
{
    BallPhysics physics;

    double radius{4};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{0, 0, -1};
    Eigen::Vector3d velocity{0, 0, -10};
    Eigen::Vector3d acceleration{0, 0, physics.gravity};
    double coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3d accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3d velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3d positionExpected{0, 0, physics.balls[0].radius};

    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallBelowGround_ExpectRadiusPositionAboveGroundAndOppositeVelocity)
{
    BallPhysics physics;

    double radius{4};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{0, 0, -100};
    Eigen::Vector3d velocity{0, 0, -10};
    Eigen::Vector3d acceleration{0, 0, physics.gravity};
    double coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3d accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3d velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3d positionExpected{0, 0, physics.balls[0].radius};

    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallGroundCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionAboveGroundAndDepletedOppositeVelocity)
{
    BallPhysics physics;

    double radius{4};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{0, 0, -100};
    Eigen::Vector3d velocity{0, 0, -10};
    Eigen::Vector3d acceleration{0, 0, physics.gravity};
    double coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3d accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3d velocityExpected{0, 0, -coefficientOfRestitution*velocity[2]};
    Eigen::Vector3d positionExpected{0, 0, physics.balls[0].radius};

    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallXWallCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionInsideBoxAndDepletedOppositeVelocity)
{
    BallPhysics physics;

    double radius{4};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{100, 0, 10};
    Eigen::Vector3d velocity{10, 0, 0};
    Eigen::Vector3d acceleration{0, 0, physics.gravity};
    double coefficientOfRestitution{0.3};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3d accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3d velocityExpected{-coefficientOfRestitution*velocity[0], 0, 0};
    Eigen::Vector3d positionExpected{(physics.boxBoundSize-physics.balls[0].radius), 0, 10};

    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallYWallCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionInsideBoxAndDepletedOppositeVelocity)
{
    BallPhysics physics;

    double radius{4};
    double mass{5};
    unsigned int color{128};
    Eigen::Vector3d position{0, -100, 10};
    Eigen::Vector3d velocity{0, -10, 0};
    Eigen::Vector3d acceleration{0, 0, physics.gravity};
    double coefficientOfRestitution{0.7};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3d accelerationExpected{0, 0, physics.gravity};
    Eigen::Vector3d velocityExpected{0, -coefficientOfRestitution*velocity[1], 0};
    Eigen::Vector3d positionExpected{0, -(physics.boxBoundSize-physics.balls[0].radius), 10};

    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_VECTOR3_DOUBLE_EQ(physics.balls[0].position, positionExpected);
}
