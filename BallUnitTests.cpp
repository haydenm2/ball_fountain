#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "Ball.hpp"


TEST(BallTests, WhenInstantiatingBall_ExpectCorrectInitializationValues)
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
