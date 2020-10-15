#include "gtest/gtest.h"
#include "BallPhysics.hpp"

void EXPECT_ARRAY3_DOUBLE_EQ(std::array<double, 3> inputVector, std::array<double, 3> truthVector)
{
    for(double index = 0; index < 3; index++)
    {
        EXPECT_EQ(inputVector[index], truthVector[index]);
    }
}

TEST(PhysicsTests, WhenInstantiatingBall_ExpectCorrectInitialization)
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
