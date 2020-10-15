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

TEST(PhysicsTests, WhenAddingMultipleBalls_ExpectCorrectInitialization)
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

