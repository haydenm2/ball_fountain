#include "gtest/gtest.h"
#include "BallPhysics.hpp"

void EXPECT_ARRAY3_DOUBLE_EQ(std::array<double, 3> inputVector, std::array<double, 3> truthVector)
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
    std::array<double, 3> positionExpected{0, 0, 0};
    std::array<double, 3> velocityExpected{0, 0, 0};
    std::array<double, 3> accelerationExpected{0, 0, 0};
    double coefficientOfRestitutionExpected{0};

    Ball ball;
    EXPECT_EQ(ball.radius, radiusExpected);
    EXPECT_EQ(ball.mass, massExpected);
    EXPECT_ARRAY3_DOUBLE_EQ(ball.position, positionExpected);
    EXPECT_ARRAY3_DOUBLE_EQ(ball.velocity, velocityExpected);
    EXPECT_ARRAY3_DOUBLE_EQ(ball.acceleration, accelerationExpected);
    EXPECT_EQ(ball.coefficientOfRestitution, coefficientOfRestitutionExpected);
}

TEST(BallTests, WhenInstantiatingBallWithValues_ExpectCorrectInitialization)
{
    double radius{10};
    double mass{5};
    unsigned int color{128};
    std::array<double, 3> position{1, 2, 3};
    std::array<double, 3> velocity{4, 5, 6};
    std::array<double, 3> acceleration{7, 8, 9};
    double coefficientOfRestitution{2};

    Ball ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    EXPECT_EQ(ball.radius, radius);
    EXPECT_EQ(ball.mass, mass);
    EXPECT_ARRAY3_DOUBLE_EQ(ball.position, position);
    EXPECT_ARRAY3_DOUBLE_EQ(ball.velocity, velocity);
    EXPECT_ARRAY3_DOUBLE_EQ(ball.acceleration, acceleration);
    EXPECT_EQ(ball.coefficientOfRestitution, coefficientOfRestitution);
}

TEST(PhysicsTests, WhenAddingBall_ExpectCorrectInitialization)
{
    double radius{10};
    double mass{5};
    unsigned int color{128};
    std::array<double, 3> position{1, 2, 3};
    std::array<double, 3> velocity{4, 5, 6};
    std::array<double, 3> acceleration{7, 8, 9};
    double coefficientOfRestitution{2};

    BallPhysics physics;
    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    EXPECT_EQ(physics.balls[0].radius, radius);
    EXPECT_EQ(physics.balls[0].mass, mass);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].position, position);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].velocity, velocity);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].acceleration, acceleration);
    EXPECT_EQ(physics.balls[0].coefficientOfRestitution, coefficientOfRestitution);
}

TEST(PhysicsTests, WhenAddingMultipleBalls_ExpectCorrectInitializationOfAllBalls)
{
    int numberOfBalls{100};
    double radius{10};
    double mass{5};
    unsigned int color{128};
    std::array<double, 3> position{1, 2, 3};
    std::array<double, 3> velocity{4, 5, 6};
    std::array<double, 3> acceleration{7, 8, 9};
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
        EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[index].position, position);
        EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[index].velocity, velocity);
        EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[index].acceleration, acceleration);
        EXPECT_EQ(physics.balls[index].coefficientOfRestitution, coefficientOfRestitution);
    }
}

TEST(PhysicsTests, WhenUpdatingGravityPhysicsOverTimeStep_ExpectCorrectPosition)
{
    BallPhysics physics;

    double radius{10};
    double mass{5};
    unsigned int color{128};
    std::array<double, 3> position{0, 0, 0};
    std::array<double, 3> velocity{1, 1, 1};
    std::array<double, 3> acceleration{0, 0, physics.gravity};
    double coefficientOfRestitution{0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{10};
    physics.update(deltaTime);

    std::array<double, 3> accelerationExpected{0, 0, physics.gravity};
    std::array<double, 3> velocityExpected{1, 1, 1+acceleration[2]*deltaTime};
    std::array<double, 3> positionExpected{0+velocity[0]*deltaTime, 0+velocity[1]*deltaTime, 0+velocity[2]*deltaTime+0.5*acceleration[2]*pow(deltaTime, 2)};

    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingNoPhysicsOverTimeStep_ExpectNoChange)
{
    BallPhysics physics;

    double radius{10};
    double mass{5};
    unsigned int color{128};
    std::array<double, 3> position{0, 0, 0};
    std::array<double, 3> velocity{0, 0, 0};
    std::array<double, 3> acceleration{0, 0, 0};
    double coefficientOfRestitution{0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{10};
    physics.update(deltaTime);

    std::array<double, 3> accelerationExpected{0, 0, 0};
    std::array<double, 3> velocityExpected{0, 0, 0};
    std::array<double, 3> positionExpected{0, 0, 0};

    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingSequentialBallsTwoTimeSteps_ExpectCorrectPositions)
{
    BallPhysics physics;

    double radius{10};
    double mass{5};
    unsigned int color{128};
    std::array<double, 3> position{0, 0, 0};
    std::array<double, 3> velocity{1, 1, 1};
    std::array<double, 3> acceleration{0, 0, physics.gravity};
    double coefficientOfRestitution{0};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);

    double deltaTime{10};
    physics.update(deltaTime);

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
    physics.update(deltaTime);

    std::array<double, 3> accelerationExpected1{0, 0, physics.gravity};
    std::array<double, 3> velocityExpected1{1, 1, 1+acceleration[2]*(2*deltaTime)};
    std::array<double, 3> positionExpected1{0+velocity[0]*(2*deltaTime), 0+velocity[1]*(2*deltaTime), 0+velocity[2]*(2*deltaTime)+0.5*acceleration[2]*pow((2*deltaTime), 2)};

    std::array<double, 3> accelerationExpected2{0, 0, physics.gravity};
    std::array<double, 3> velocityExpected2{1, 1, 1+acceleration[2]*deltaTime};
    std::array<double, 3> positionExpected2{0+velocity[0]*deltaTime, 0+velocity[1]*deltaTime, 0+velocity[2]*deltaTime+0.5*acceleration[2]*pow(deltaTime, 2)};

    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].acceleration, accelerationExpected1);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].velocity, velocityExpected1);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[0].position, positionExpected1);

    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[1].acceleration, accelerationExpected2);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[1].velocity, velocityExpected2);
    EXPECT_ARRAY3_DOUBLE_EQ(physics.balls[1].position, positionExpected2);
}
