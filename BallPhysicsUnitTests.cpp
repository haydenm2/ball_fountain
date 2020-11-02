#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "BallPhysics.hpp"


TEST(PhysicsTests, WhenSettingNewBallRadius_ExpectCorrectParameter)
{
    float radius{10};
    BallPhysics physics;

    physics.set_new_ball_radius(radius);

    EXPECT_EQ(physics.get_new_ball_radius(), radius);
}

TEST(PhysicsTests, WhenSettingNewBallMass_ExpectCorrectParameter)
{
    float mass{10};
    BallPhysics physics;

    physics.set_new_ball_mass(mass);

    EXPECT_EQ(physics.get_new_ball_mass(), mass);
}

TEST(PhysicsTests, WhenSettingNewBallColor_ExpectCorrectParameter)
{
    unsigned int color{100};
    BallPhysics physics;

    physics.set_new_ball_color(color);

    EXPECT_EQ(physics.get_new_ball_color(), color);
}

TEST(PhysicsTests, WhenSettingNewBallPosition_ExpectCorrectParameter)
{
    Eigen::Vector3f position{1, 2, 3};
    BallPhysics physics;

    physics.set_new_ball_position(position);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_new_ball_position(), position);
}

TEST(PhysicsTests, WhenSettingNewBallVelocity_ExpectCorrectParameter)
{
    Eigen::Vector3f velocity{1, 2, 3};
    BallPhysics physics;

    physics.set_new_ball_velocity(velocity);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_new_ball_velocity(), velocity);
}

TEST(PhysicsTests, WhenSettingNewBallCoefficientOfRestitution_ExpectCorrectParameter)
{
    float coefficientOfRestitution{10};
    BallPhysics physics;

    physics.set_new_ball_coefficient_of_restitution(coefficientOfRestitution);

    EXPECT_EQ(physics.get_new_ball_coefficient_of_restitution(), coefficientOfRestitution);
}

TEST(PhysicsTests, WhenSettingGravity_ExpectCorrectValue)
{
    float gravity{-10};
    BallPhysics physics;

    physics.set_gravity(gravity);

    EXPECT_EQ(physics.get_gravity(), gravity);
}

TEST(PhysicsTests, WhenSettingBoxSize_ExpectCorrectValue)
{
    float boxSize{100};
    BallPhysics physics;

    physics.set_box_size(boxSize);

    EXPECT_EQ(physics.get_box_size(), boxSize);
}

TEST(PhysicsTests, WhenSettingDragCoefficient_ExpectCorrectValue)
{
    float dragCoefficient{100};
    BallPhysics physics;

    physics.set_drag_coefficient(dragCoefficient);

    EXPECT_EQ(physics.get_drag_coefficient(), dragCoefficient);
}

TEST(PhysicsTests, WhenSettingFluidDensity_ExpectCorrectValue)
{
    float fluidDensity{100};
    BallPhysics physics;

    physics.set_fluid_density(fluidDensity);

    EXPECT_EQ(physics.get_fluid_density(), fluidDensity);
}

TEST(PhysicsTests, WhenSettingNewBallParametersSimultaneously_ExpectCorrectParameters)
{
    float radius{10};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{1, 2, 3};
    Eigen::Vector3f velocity{4, 5, 6};
    float coefficientOfRestitution{2};
    BallPhysics physics;

    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    EXPECT_EQ(physics.get_new_ball_radius(), radius);
    EXPECT_EQ(physics.get_new_ball_mass(), mass);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_new_ball_position(), position);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_new_ball_velocity(), velocity);
    EXPECT_EQ(physics.get_new_ball_coefficient_of_restitution(), coefficientOfRestitution);
}

TEST(PhysicsTests, WhenDefaultInitializingPhysics_ExpectDefaultEnvironmentParameters)
{
    float boxSizeExpected{30};
    float fluidDensityExpected{0};
    float gravityExpected{-9.81};

    BallPhysics physics;

    EXPECT_EQ(physics.get_box_size(), boxSizeExpected);
    EXPECT_EQ(physics.get_fluid_density(), fluidDensityExpected);
    EXPECT_EQ(physics.get_gravity(), gravityExpected);
}

TEST(PhysicsTests, WhenInitializingPhysicsWithBox_ExpectCorrectBoxSizeAndDefaultEnvironmentParameters)
{
    float boxSize{100};
    float fluidDensityExpected{0};
    float gravityExpected{-9.81};

    BallPhysics physics(boxSize);

    EXPECT_EQ(physics.get_box_size(), boxSize);
    EXPECT_EQ(physics.get_fluid_density(), fluidDensityExpected);
    EXPECT_EQ(physics.get_gravity(), gravityExpected);
}

TEST(PhysicsTests, WhenInitializingPhysicsWithBoxAndDensity_ExpectCorrectBoxDensityAndDefaultEnvironmentParameters)
{
    float boxSize{100};
    float fluidDensity{20};
    float gravityExpected{-9.81};

    BallPhysics physics(boxSize, fluidDensity);

    EXPECT_EQ(physics.get_box_size(), boxSize);
    EXPECT_EQ(physics.get_fluid_density(), fluidDensity);
    EXPECT_EQ(physics.get_gravity(), gravityExpected);
}

TEST(PhysicsTests, WhenInitializingPhysicsWithBoxDensityAndGravity_ExpectCorrectParameters)
{
    float boxSize{100};
    float fluidDensity{20};
    float gravity{-100};

    BallPhysics physics(boxSize, fluidDensity, gravity);

    EXPECT_EQ(physics.get_box_size(), boxSize);
    EXPECT_EQ(physics.get_fluid_density(), fluidDensity);
    EXPECT_EQ(physics.get_gravity(), gravity);
}

TEST(PhysicsTests, WhenAddingBall_ExpectCorrectInitialization)
{
    float radius{10};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{1, 2, 3};
    Eigen::Vector3f velocity{4, 5, 6};
    float coefficientOfRestitution{2};
    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();

    EXPECT_EQ(physics.get_ball_ptr(0)->radius, radius);
    EXPECT_EQ(physics.get_ball_ptr(0)->mass, mass);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, position);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocity);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_EQ(physics.get_ball_ptr(0)->coefficientOfRestitution, coefficientOfRestitution);
}

TEST(PhysicsTests, WhenAddingMultipleBalls_ExpectCorrectInitializationOfAllBalls)
{
    int numberOfBalls{100};
    float radius{10};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{1, 2, 3};
    Eigen::Vector3f velocity{4, 5, 6};
    float coefficientOfRestitution{2};
    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    for(int index{0}; index < numberOfBalls; index++)
        physics.add_ball();

    for(int index{0}; index < numberOfBalls; index++)
    {
        EXPECT_EQ(physics.get_ball_ptr(index)->radius, radius);
        EXPECT_EQ(physics.get_ball_ptr(index)->mass, mass);
        EXPECT_EQ(physics.get_ball_ptr(index)->color, color);
        EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(index)->position, position);
        EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(index)->velocity, velocity);
        EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(index)->acceleration, accelerationExpected);
        EXPECT_EQ(physics.get_ball_ptr(index)->coefficientOfRestitution, coefficientOfRestitution);
    }
}

TEST(PhysicsTests, WhenGettingBallPointer_ExpectCorrectValuesAtPointerAddress)
{
    int numberOfBalls{20};
    BallPhysics physics;
    for(int index{0}; index < numberOfBalls-2; index++)
        physics.add_ball();
    float radius{10};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{1, 2, 3};
    Eigen::Vector3f velocity{4, 5, 6};
    float coefficientOfRestitution{2};
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    physics.add_ball();

    Ball *ball = physics.get_ball_ptr(numberOfBalls-1);

    EXPECT_EQ(ball->radius, radius);
    EXPECT_EQ(ball->mass, mass);
    EXPECT_EQ(ball->color, color);
    EXPECT_VECTOR3_FLOAT_EQ(ball->position, position);
    EXPECT_VECTOR3_FLOAT_EQ(ball->velocity, velocity);
    EXPECT_EQ(ball->coefficientOfRestitution, coefficientOfRestitution);
}

TEST(PhysicsTests, WhenUpdatingGravityPhysicsOverTimeStep_ExpectCorrectPosition)
{
    float radius{10};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 1000};
    Eigen::Vector3f velocity{1, 1, 1};
    float coefficientOfRestitution{1.0};
    BallPhysics physics;
    float deltaTime{5};
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    physics.add_ball();

    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocityExpected = velocity + accelerationExpected*deltaTime;
    Eigen::Vector3f positionExpected = position + velocityExpected*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingSequentialBallsTwoTimeSteps_ExpectCorrectPositions)
{
    float radius{1};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 1000};
    Eigen::Vector3f velocity{1, 1, 1};
    float coefficientOfRestitution{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();

    float deltaTime{3};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocityExpected1 = velocity + accelerationExpected*deltaTime;
    Eigen::Vector3f positionExpected1 = position + velocityExpected1*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    physics.add_ball();
    physics.update(deltaTime);

    velocityExpected1 = velocityExpected1 + accelerationExpected*deltaTime;
    positionExpected1 = positionExpected1 + velocityExpected1*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    Eigen::Vector3f velocityExpected2 = velocity + accelerationExpected*deltaTime;
    Eigen::Vector3f positionExpected2 = position + velocityExpected2*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected1);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected1);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->velocity, velocityExpected2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->position, positionExpected2);
}

TEST(PhysicsTests, WhenUpdatingGroundBallCollision_ExpectCorrectPositionAndOppositeVelocity)
{
    float radius{2};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 1.99};
    Eigen::Vector3f velocity{0, 0, -10};
    float coefficientOfRestitution{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, physics.get_ball_ptr(0)->radius};

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallCollisionInGround_ExpectRadiusPositionAboveGroundAndOppositeVelocity)
{
    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, -1};
    Eigen::Vector3f velocity{0, 0, -10};
    float coefficientOfRestitution{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, physics.get_ball_ptr(0)->radius};

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallBelowGround_ExpectRadiusPositionAboveGroundAndOppositeVelocity)
{
    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, -100};
    Eigen::Vector3f velocity{0, 0, -10};
    float coefficientOfRestitution{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, physics.get_ball_ptr(0)->radius};

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallGroundCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionAboveGroundAndDepletedOppositeVelocity)
{
    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, -100};
    Eigen::Vector3f velocity{0, 0, -10};
    float coefficientOfRestitution{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocityExpected{0, 0, -coefficientOfRestitution*velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, physics.get_ball_ptr(0)->radius};

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallXWallCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionInsideBoxAndDepletedOppositeVelocity)
{
    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{100, 0, 10};
    Eigen::Vector3f velocity{10, 0, 0};
    float coefficientOfRestitution{0.3};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocityExpected{-coefficientOfRestitution*velocity[0], 0, 0};
    Eigen::Vector3f positionExpected{(physics.get_box_size()-physics.get_ball_ptr(0)->radius), 0, 10};

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBallYWallCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionInsideBoxAndDepletedOppositeVelocity)
{
    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, -100, 10};
    Eigen::Vector3f velocity{0, -10, 0};
    float coefficientOfRestitution{0.7};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocityExpected{0, -coefficientOfRestitution*velocity[1], 0};
    Eigen::Vector3f positionExpected{0, -(physics.get_box_size()-physics.get_ball_ptr(0)->radius), 10};

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST(PhysicsTests, WhenUpdatingBalltoBallCollisionWithTrivialCoefficientOfRestitution_ExpectPositionChangeToRadiusAndCorrectVelocity)
{
    float radius1{4};
    float mass1{5};
    unsigned int color1{128};
    Eigen::Vector3f position1{0, 0, 100};
    Eigen::Vector3f velocity1{0, 10, 0};
    float coefficientOfRestitution1{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius1, mass1, color1, position1, velocity1, coefficientOfRestitution1);

    physics.add_ball();

    float radius2{5};
    float mass2{2};
    unsigned int color2{128};
    Eigen::Vector3f position2{1, 1, 101};
    Eigen::Vector3f velocity2{0, -10, 0};
    float coefficientOfRestitution2{1.0};

    physics.set_new_ball_parameters(radius2, mass2, color2, position2, velocity2, coefficientOfRestitution2);

    physics.add_ball();

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f positionDifference = position1 - position2;
    float offsetFromBall = positionDifference.norm();
    Eigen::Vector3f velocityDifference = velocity1 - velocity2;
    float totalMass = mass1 + mass2;

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocity1Expected = coefficientOfRestitution1*(velocity1 - 2*mass2/totalMass*velocityDifference.dot(positionDifference)/pow(positionDifference.norm(), 2)*positionDifference);
    Eigen::Vector3f position1Expected = position1;

    Eigen::Vector3f velocity2Expected = coefficientOfRestitution2*(velocity2 - 2*mass1/totalMass*(-velocityDifference).dot(-positionDifference)/pow(positionDifference.norm(), 2)*(-positionDifference));
    Eigen::Vector3f position2Expected = position1 - positionDifference/offsetFromBall*(radius1 + radius2);;

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocity1Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, position1Expected);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->velocity, velocity2Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->position, position2Expected);
}

TEST(PhysicsTests, WhenUpdatingBalltoBallWithNoCollision_ExpectNoChange)
{
    float radius1{4};
    float mass1{5};
    unsigned int color1{128};
    Eigen::Vector3f position1{0, 0, 100};
    Eigen::Vector3f velocity1{0, 10, 0};
    float coefficientOfRestitution1{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius1, mass1, color1, position1, velocity1, coefficientOfRestitution1);

    physics.add_ball();

    float radius2{5};
    float mass2{2};
    unsigned int color2{128};
    Eigen::Vector3f position2{10, 10, 10};
    Eigen::Vector3f velocity2{0, -10, 0};
    float coefficientOfRestitution2{1.0};

    physics.set_new_ball_parameters(radius2, mass2, color2, position2, velocity2, coefficientOfRestitution2);

    physics.add_ball();

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocity1Expected = velocity1;
    Eigen::Vector3f position1Expected = position1;

    Eigen::Vector3f velocity2Expected = velocity2;
    Eigen::Vector3f position2Expected = position2;

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocity1Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, position1Expected);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->velocity, velocity2Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->position, position2Expected);
}

TEST(PhysicsTests, WhenAddingBalls_ExpectIncreasedBallCount)
{
    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 100};
    Eigen::Vector3f velocity{0, 10, 0};
    float coefficientOfRestitution{1.0};
    int numberOfBalls{50};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    for(int count{0}; count<numberOfBalls; count++)
        physics.add_ball();

    EXPECT_EQ(physics.get_ball_count(), numberOfBalls);
}

TEST(PhysicsTests, WhenAddingBallsOverMaxLimit_ExpectMaxBallCount)
{
    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 100};
    Eigen::Vector3f velocity{0, 10, 0};
    float coefficientOfRestitution{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    unsigned int numberOfBalls{physics.get_max_ball_count()+10};

    for(int count{0}; count<numberOfBalls; count++)
        physics.add_ball();

    EXPECT_EQ(physics.get_ball_count(), physics.get_max_ball_count());
}

TEST(PhysicsTests, WhenReplacingBallAtSpecificIndex_ExpectCorrectBallParametersAtIndex)
{
    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 100};
    Eigen::Vector3f velocity{0, 10, 0};
    float coefficientOfRestitution{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    for(int count{0}; count<physics.get_max_ball_count(); count++)
        physics.add_ball();

    unsigned int replaceIndex{10};

    float newRadius{11};
    float newMass{13};
    unsigned int newColor{17};
    Eigen::Vector3f newPosition{1, 1, 1};
    Eigen::Vector3f newVelocity{1, 1, 1};
    Eigen::Vector3f newAcceleration{1, 1, 1};
    float newCoefficientOfRestitution{0.5};

    physics.set_new_ball_parameters(newRadius, newMass, newColor, newPosition, newVelocity, newCoefficientOfRestitution);

    physics.update_ball(replaceIndex, newAcceleration);

    EXPECT_EQ(physics.get_ball_ptr(replaceIndex)->radius, newRadius);
    EXPECT_EQ(physics.get_ball_ptr(replaceIndex)->mass, newMass);
    EXPECT_EQ(physics.get_ball_ptr(replaceIndex)->color, newColor);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(replaceIndex)->position, newPosition);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(replaceIndex)->velocity, newVelocity);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(replaceIndex)->acceleration, newAcceleration);
    EXPECT_EQ(physics.get_ball_ptr(replaceIndex)->coefficientOfRestitution, newCoefficientOfRestitution);
}

TEST(PhysicsTests, WhenAddingBallOverMaxLimit_ExpectCorrectBallReplacement)
{
    float radius1{4};
    float mass1{5};
    unsigned int color1{128};
    Eigen::Vector3f position1{0, 0, 100};
    Eigen::Vector3f velocity1{0, 10, 0};
    float coefficientOfRestitution1{1.0};

    float radius2{2};
    float mass2{1};
    unsigned int color2{0};
    Eigen::Vector3f position2{1, 1, -100};
    Eigen::Vector3f velocity2{1, 1, 1};
    float coefficientOfRestitution2{0.2};

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};

    int overCount{10};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius1, mass1, color1, position1, velocity1, coefficientOfRestitution1);

    for(int count{0}; count<physics.get_max_ball_count(); count++)
        physics.add_ball();

    physics.set_new_ball_parameters(radius2, mass2, color2, position2, velocity2, coefficientOfRestitution2);
    for(int count{0}; count<overCount; count++)
        physics.add_ball();

    EXPECT_EQ(physics.get_ball_ptr(overCount-1)->radius, radius2);
    EXPECT_EQ(physics.get_ball_ptr(overCount-1)->mass, mass2);
    EXPECT_EQ(physics.get_ball_ptr(overCount-1)->color, color2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(overCount-1)->position, position2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(overCount-1)->velocity, velocity2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(overCount-1)->acceleration, accelerationExpected);
    EXPECT_EQ(physics.get_ball_ptr(overCount-1)->coefficientOfRestitution, coefficientOfRestitution2);
}

TEST(PhysicsTests, WhenBallIsMovingWithFluidDensity_ExpectDampedBallAcceleration)
{
    float fluidDensity{0.5};
    float boxSize{30};
    BallPhysics physics{BallPhysics(boxSize, fluidDensity)};

    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 100};
    Eigen::Vector3f velocity{100, 10, -5};
    float coefficientOfRestitution{1.0};

    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();
    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    float velocityMagnitude = velocity.norm();
    Eigen::Vector3f dragForce = -(0.5*fluidDensity*pow(velocityMagnitude, 2)*physics.get_drag_coefficient()*(M_PI*pow(radius, 2)))/mass*velocity/velocityMagnitude;

    accelerationExpected += dragForce;

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
}

TEST(PhysicsTests, WhenBallNotMovingWithFluidDensity_ExpectNoChange)
{
    float fluidDensity{0.5};
    float boxSize{30};
    BallPhysics physics{BallPhysics(boxSize, fluidDensity)};

    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 100};
    Eigen::Vector3f velocity{0, 0, 0};
    float coefficientOfRestitution{1.0};

    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();
    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, accelerationExpected);
}

TEST(PhysicsTests, WhenRemovingBall_ExpectReducedBallCount)
{
    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 100};
    Eigen::Vector3f velocity{0, 0, 0};
    float coefficientOfRestitution{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    int numberOfBallsToAdd{20};
    for(int ballNumber{0}; ballNumber<numberOfBallsToAdd; ballNumber++)
        physics.add_ball();
    physics.remove_ball();

    EXPECT_EQ(physics.get_ball_count(), numberOfBallsToAdd-1);
}

TEST(PhysicsTests, WhenRemovingBallWhenNoBalls_ExpectNoBallCount)
{
    BallPhysics physics{BallPhysics()};

    physics.remove_ball();

    EXPECT_EQ(physics.get_ball_count(), 0);
}

TEST(PhysicsTests, WhenRemovingBallWhenNoBalls_ExpectNoBalls)
{
    BallPhysics physics{BallPhysics()};

    physics.remove_ball();

    EXPECT_EQ(physics.get_ball_count(), 0);
}

TEST(PhysicsTests, WhenClearingBalls_ExpectNoBalls)
{
    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 100};
    Eigen::Vector3f velocity{0, 0, 0};
    float coefficientOfRestitution{1.0};

    BallPhysics physics;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    int numberOfBallsToAdd{20};
    for(int ballNumber{0}; ballNumber<numberOfBallsToAdd; ballNumber++)
        physics.add_ball();
    physics.clear_balls();

    EXPECT_EQ(physics.get_ball_count(), 0);
}

TEST(PhysicsTests, WhenClearingNoBalls_ExpectNoBallsAndNoCount)
{
    BallPhysics physics{BallPhysics()};
    physics.clear_balls();

    EXPECT_EQ(physics.get_ball_count(), 0);
}
