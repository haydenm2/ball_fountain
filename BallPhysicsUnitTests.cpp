#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "BallPhysics.hpp"


class PhysicsTests : public ::testing::Test
{
protected:
    BallPhysics physics;
    float radius{10};
    float mass{5};
    unsigned int color{100};
    Eigen::Vector3f position{-1, -1, 100};
    Eigen::Vector3f velocity{1, 1, 1};
    Eigen::Vector3f acceleration{0, 0, -9.81};
    float coefficientOfRestitution{0.5};
    float coefficientOfRestitutionDefault{1};
    float gravity{-10};
    float boxSize{100};
    float dragCoefficient{100};
    float fluidDensity{100};
    float boxSizeDefault{30};
    float fluidDensityDefault{0};
    float gravityDefault{-9.81};
    float deltaTime{1};
    float zeroTime{0};
};

TEST_F(PhysicsTests, WhenSettingNewBallRadius_ExpectCorrectParameter)
{
    physics.set_new_ball_radius(radius);

    EXPECT_EQ(physics.get_new_ball_radius(), radius);
}

TEST_F(PhysicsTests, WhenSettingNewBallMass_ExpectCorrectParameter)
{
    physics.set_new_ball_mass(mass);

    EXPECT_EQ(physics.get_new_ball_mass(), mass);
}

TEST_F(PhysicsTests, WhenSettingNewBallColor_ExpectCorrectParameter)
{
    physics.set_new_ball_color(color);

    EXPECT_EQ(physics.get_new_ball_color(), color);
}

TEST_F(PhysicsTests, WhenSettingNewBallPosition_ExpectCorrectParameter)
{
    physics.set_new_ball_position(position);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_new_ball_position(), position);
}

TEST_F(PhysicsTests, WhenSettingNewBallVelocity_ExpectCorrectParameter)
{
    physics.set_new_ball_velocity(velocity);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_new_ball_velocity(), velocity);
}

TEST_F(PhysicsTests, WhenSettingNewBallCoefficientOfRestitution_ExpectCorrectParameter)
{
    physics.set_new_ball_coefficient_of_restitution(coefficientOfRestitution);

    EXPECT_EQ(physics.get_new_ball_coefficient_of_restitution(), coefficientOfRestitution);
}

TEST_F(PhysicsTests, WhenSettingGravity_ExpectCorrectValue)
{
    physics.set_gravity(gravity);

    EXPECT_EQ(physics.get_gravity(), gravity);
}

TEST_F(PhysicsTests, WhenSettingBoxSize_ExpectCorrectValue)
{
    physics.set_box_size(boxSize);

    EXPECT_EQ(physics.get_box_size(), boxSize);
}

TEST_F(PhysicsTests, WhenSettingDragCoefficient_ExpectCorrectValue)
{
    physics.set_drag_coefficient(dragCoefficient);

    EXPECT_EQ(physics.get_drag_coefficient(), dragCoefficient);
}

TEST_F(PhysicsTests, WhenSettingFluidDensity_ExpectCorrectValue)
{
    physics.set_fluid_density(fluidDensity);

    EXPECT_EQ(physics.get_fluid_density(), fluidDensity);
}

TEST_F(PhysicsTests, WhenSettingNewBallParametersSimultaneously_ExpectCorrectParameters)
{
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    EXPECT_EQ(physics.get_new_ball_radius(), radius);
    EXPECT_EQ(physics.get_new_ball_mass(), mass);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_new_ball_position(), position);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_new_ball_velocity(), velocity);
    EXPECT_EQ(physics.get_new_ball_coefficient_of_restitution(), coefficientOfRestitution);
}

TEST_F(PhysicsTests, WhenDefaultInitializingPhysics_ExpectDefaultEnvironmentParameters)
{
    EXPECT_EQ(physics.get_box_size(), boxSizeDefault);
    EXPECT_EQ(physics.get_fluid_density(), fluidDensityDefault);
    EXPECT_EQ(physics.get_gravity(), gravityDefault);
}

TEST_F(PhysicsTests, WhenInitializingPhysicsWithBox_ExpectCorrectBoxSizeAndDefaultEnvironmentParameters)
{
    physics = BallPhysics(boxSize);

    EXPECT_EQ(physics.get_box_size(), boxSize);
    EXPECT_EQ(physics.get_fluid_density(), fluidDensityDefault);
    EXPECT_EQ(physics.get_gravity(), gravityDefault);
}

TEST_F(PhysicsTests, WhenInitializingPhysicsWithBoxAndDensity_ExpectCorrectBoxDensityAndDefaultEnvironmentParameters)
{
    physics = BallPhysics(boxSize, fluidDensity);

    EXPECT_EQ(physics.get_box_size(), boxSize);
    EXPECT_EQ(physics.get_fluid_density(), fluidDensity);
    EXPECT_EQ(physics.get_gravity(), gravityDefault);
}

TEST_F(PhysicsTests, WhenInitializingPhysicsWithBoxDensityAndGravity_ExpectCorrectParameters)
{
    physics = BallPhysics(boxSize, fluidDensity, gravity);

    EXPECT_EQ(physics.get_box_size(), boxSize);
    EXPECT_EQ(physics.get_fluid_density(), fluidDensity);
    EXPECT_EQ(physics.get_gravity(), gravity);
}

TEST_F(PhysicsTests, WhenAddingBall_ExpectCorrectInitialization)
{
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();

    EXPECT_EQ(physics.get_ball_ptr(0)->radius, radius);
    EXPECT_EQ(physics.get_ball_ptr(0)->mass, mass);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, position);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocity);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_EQ(physics.get_ball_ptr(0)->coefficientOfRestitution, coefficientOfRestitution);
}

TEST_F(PhysicsTests, WhenAddingMultipleBalls_ExpectCorrectInitializationOfAllBalls)
{
    int numberOfBalls{100};
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
        EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(index)->acceleration, acceleration);
        EXPECT_EQ(physics.get_ball_ptr(index)->coefficientOfRestitution, coefficientOfRestitution);
    }
}

TEST_F(PhysicsTests, WhenGettingBallPointer_ExpectCorrectValuesAtPointerAddress)
{
    int numberOfBalls{20};
    for(int index{0}; index < numberOfBalls-2; index++)
        physics.add_ball();
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

TEST_F(PhysicsTests, WhenUpdatingGravityPhysicsOverTimeStep_ExpectCorrectPosition)
{
    Eigen::Vector3f velocityExpected = velocity + acceleration*deltaTime;
    Eigen::Vector3f positionExpected = position + velocityExpected*deltaTime + 0.5*acceleration*pow(deltaTime, 2);
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    physics.add_ball();

    physics.update(deltaTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST_F(PhysicsTests, WhenUpdatingSequentialBallsTwoTimeSteps_ExpectCorrectPositions)
{
    Eigen::Vector3f velocityExpected1 = velocity + acceleration*deltaTime;
    Eigen::Vector3f positionExpected1 = position + velocityExpected1*deltaTime + 0.5*acceleration*pow(deltaTime, 2);
    velocityExpected1 = velocityExpected1 + acceleration*deltaTime;
    positionExpected1 = positionExpected1 + velocityExpected1*deltaTime + 0.5*acceleration*pow(deltaTime, 2);
    Eigen::Vector3f velocityExpected2 = velocity + acceleration*deltaTime;
    Eigen::Vector3f positionExpected2 = position + velocityExpected2*deltaTime + 0.5*acceleration*pow(deltaTime, 2);
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    physics.add_ball();
    physics.update(deltaTime);
    physics.add_ball();
    physics.update(deltaTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected1);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected1);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->velocity, velocityExpected2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->position, positionExpected2);
}

TEST_F(PhysicsTests, WhenUpdatingGroundBallCollision_ExpectCorrectPositionAndOppositeVelocity)
{
    position = Eigen::Vector3f{0, 0, 1.99};
    velocity = Eigen::Vector3f{0, 0, -10};
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitutionDefault);
    physics.add_ball();
    Eigen::Vector3f velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, radius};

    physics.update(zeroTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST_F(PhysicsTests, WhenUpdatingBallCollisionInGround_ExpectRadiusPositionAboveGroundAndOppositeVelocity)
{
    position = Eigen::Vector3f {0, 0, -1};
    velocity = Eigen::Vector3f{0, 0, -10};
    Eigen::Vector3f velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, radius};
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitutionDefault);
    physics.add_ball();

    physics.update(zeroTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST_F(PhysicsTests, WhenUpdatingBallBelowGround_ExpectRadiusPositionAboveGroundAndOppositeVelocity)
{
    position = Eigen::Vector3f{0, 0, -100};
    velocity = Eigen::Vector3f{0, 0, -10};
    Eigen::Vector3f velocityExpected{0, 0, -velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, radius};
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitutionDefault);
    physics.add_ball();

    physics.update(zeroTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST_F(PhysicsTests, WhenUpdatingBallGroundCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionAboveGroundAndDepletedOppositeVelocity)
{
    position = Eigen::Vector3f{0, 0, -100};
    velocity = Eigen::Vector3f{0, 0, -10};
    Eigen::Vector3f velocityExpected{0, 0, -coefficientOfRestitution*velocity[2]};
    Eigen::Vector3f positionExpected{0, 0, radius};
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    physics.add_ball();

    physics.update(zeroTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST_F(PhysicsTests, WhenUpdatingBallXWallCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionInsideBoxAndDepletedOppositeVelocity)
{
    position = Eigen::Vector3f{100, 0, 10};
    velocity = Eigen::Vector3f{10, 0, 0};
    Eigen::Vector3f velocityExpected{-coefficientOfRestitution*velocity[0], 0, 0};
    Eigen::Vector3f positionExpected{(physics.get_box_size()-radius), 0, 10};
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    physics.add_ball();

    physics.update(zeroTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST_F(PhysicsTests, WhenUpdatingBallYWallCollisionWithNonTrivialCoefficientOfRestitution_ExpectRadiusPositionInsideBoxAndDepletedOppositeVelocity)
{
    position = Eigen::Vector3f{0, -100, 10};
    velocity = Eigen::Vector3f{0, -10, 0};
    Eigen::Vector3f velocityExpected{0, -coefficientOfRestitution*velocity[1], 0};
    Eigen::Vector3f positionExpected{0, -(physics.get_box_size()-radius), 10};
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    physics.add_ball();

    physics.update(zeroTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, positionExpected);
}

TEST_F(PhysicsTests, WhenUpdatingBalltoBallCollisionWithTrivialCoefficientOfRestitution_ExpectPositionChangeToRadiusAndCorrectVelocity)
{
    float radius1{4};
    float mass1{5};
    unsigned int color1{128};
    Eigen::Vector3f position1{0, 0, 100};
    Eigen::Vector3f velocity1{0, 10, 0};
    float coefficientOfRestitution1{1.0};

    float radius2{5};
    float mass2{2};
    unsigned int color2{128};
    Eigen::Vector3f position2{1, 1, 101};
    Eigen::Vector3f velocity2{0, -10, 0};
    float coefficientOfRestitution2{1.0};

    Eigen::Vector3f positionDifference = position1 - position2;
    float offsetFromBall = positionDifference.norm();
    Eigen::Vector3f velocityDifference = velocity1 - velocity2;
    float totalMass = mass1 + mass2;
    Eigen::Vector3f velocity1Expected = coefficientOfRestitution1*(velocity1 - 2*mass2/totalMass*velocityDifference.dot(positionDifference)/pow(positionDifference.norm(), 2)*positionDifference);
    Eigen::Vector3f position1Expected = position1;
    Eigen::Vector3f velocity2Expected = coefficientOfRestitution2*(velocity2 - 2*mass1/totalMass*(-velocityDifference).dot(-positionDifference)/pow(positionDifference.norm(), 2)*(-positionDifference));
    Eigen::Vector3f position2Expected = position1 - positionDifference/offsetFromBall*(radius1 + radius2);

    physics.set_new_ball_parameters(radius1, mass1, color1, position1, velocity1, coefficientOfRestitution1);
    physics.add_ball();
    physics.set_new_ball_parameters(radius2, mass2, color2, position2, velocity2, coefficientOfRestitution2);
    physics.add_ball();

    physics.update(zeroTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocity1Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, position1Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->velocity, velocity2Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->position, position2Expected);
}

TEST_F(PhysicsTests, WhenUpdatingBalltoBallWithNoCollision_ExpectNoChange)
{
    float radius1{4};
    float mass1{5};
    unsigned int color1{128};
    Eigen::Vector3f position1{0, 0, 100};
    Eigen::Vector3f velocity1{0, 10, 0};
    physics.set_new_ball_parameters(radius1, mass1, color1, position1, velocity1, coefficientOfRestitutionDefault);
    physics.add_ball();

    float radius2{5};
    float mass2{2};
    unsigned int color2{128};
    Eigen::Vector3f position2{10, 10, 10};
    Eigen::Vector3f velocity2{0, -10, 0};

    physics.set_new_ball_parameters(radius2, mass2, color2, position2, velocity2, coefficientOfRestitutionDefault);
    physics.add_ball();

    physics.update(zeroTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->velocity, velocity1);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->position, position1);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->acceleration, acceleration);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->velocity, velocity2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(1)->position, position2);
}

TEST_F(PhysicsTests, WhenAddingBalls_ExpectIncreasedBallCount)
{
    int numberOfBalls{50};
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);

    for(int count{0}; count<numberOfBalls; count++)
        physics.add_ball();

    EXPECT_EQ(physics.get_ball_count(), numberOfBalls);
}

TEST_F(PhysicsTests, WhenAddingBallsOverMaxLimit_ExpectMaxBallCount)
{
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    unsigned int numberOfBalls{physics.get_max_ball_count()+10};

    for(int count{0}; count<numberOfBalls; count++)
        physics.add_ball();

    EXPECT_EQ(physics.get_ball_count(), physics.get_max_ball_count());
}

TEST_F(PhysicsTests, WhenReplacingBallAtSpecificIndex_ExpectCorrectBallParametersAtIndex)
{
    unsigned int replaceIndex{10};
    float newRadius{11};
    float newMass{13};
    unsigned int newColor{17};
    Eigen::Vector3f newPosition{1, 1, 1};
    Eigen::Vector3f newVelocity{1, 1, 1};
    Eigen::Vector3f newAcceleration{1, 1, 1};
    float newCoefficientOfRestitution{0.2};

    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    for(int count{0}; count<physics.get_max_ball_count(); count++)
        physics.add_ball();
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

TEST_F(PhysicsTests, WhenAddingBallOverMaxLimit_ExpectCorrectBallReplacement)
{
    float newRadius{11};
    float newMass{13};
    unsigned int newColor{17};
    Eigen::Vector3f newPosition{1, 1, 1};
    Eigen::Vector3f newVelocity{1, 1, 1};
    float newCoefficientOfRestitution{0.2};
    int overCount{10};

    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    for(int count{0}; count<physics.get_max_ball_count(); count++)
        physics.add_ball();

    physics.set_new_ball_parameters(newRadius, newMass, newColor, newPosition, newVelocity, newCoefficientOfRestitution);
    for(int count{0}; count<overCount; count++)
        physics.add_ball();

    EXPECT_EQ(physics.get_ball_ptr(overCount-1)->radius, newRadius);
    EXPECT_EQ(physics.get_ball_ptr(overCount-1)->mass, newMass);
    EXPECT_EQ(physics.get_ball_ptr(overCount-1)->color, newColor);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(overCount-1)->position, newPosition);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(overCount-1)->velocity, newVelocity);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(overCount-1)->acceleration, acceleration);
    EXPECT_EQ(physics.get_ball_ptr(overCount-1)->coefficientOfRestitution, newCoefficientOfRestitution);
}

TEST_F(PhysicsTests, WhenBallIsMovingWithFluidDensity_ExpectDampedBallAcceleration)
{
    physics = BallPhysics(boxSize, fluidDensity);

    float velocityMagnitude = velocity.norm();
    Eigen::Vector3f dragForce = -(0.5*fluidDensity*pow(velocityMagnitude, 2)*physics.get_drag_coefficient()*(M_PI*pow(radius, 2)))/mass*velocity/velocityMagnitude;
    acceleration += dragForce;
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    physics.add_ball();

    physics.update(zeroTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
}

TEST_F(PhysicsTests, WhenBallNotMovingWithFluidDensity_ExpectNoChange)
{
    physics = BallPhysics(boxSize, fluidDensity);
    velocity = Eigen::Vector3f{0, 0, 0};
    physics.set_new_ball_parameters(radius, mass, color, position, velocity, coefficientOfRestitution);
    physics.add_ball();

    physics.update(zeroTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_ball_ptr(0)->acceleration, acceleration);
}

TEST_F(PhysicsTests, WhenRemovingBall_ExpectReducedBallCount)
{
    int numberOfBallsToAdd{20};
    for(int ballNumber{0}; ballNumber<numberOfBallsToAdd; ballNumber++)
        physics.add_ball();

    physics.remove_ball();

    EXPECT_EQ(physics.get_ball_count(), numberOfBallsToAdd-1);
}

TEST_F(PhysicsTests, WhenRemovingBallWhenNoBalls_ExpectNoBallCount)
{
    physics.remove_ball();

    EXPECT_EQ(physics.get_ball_count(), 0);
}

TEST_F(PhysicsTests, WhenClearingBalls_ExpectNoBalls)
{
    int numberOfBallsToAdd{20};
    for(int ballNumber{0}; ballNumber<numberOfBallsToAdd; ballNumber++)
        physics.add_ball();

    physics.clear_balls();

    EXPECT_EQ(physics.get_ball_count(), 0);
}

TEST_F(PhysicsTests, WhenClearingNoBalls_ExpectNoBallsAndNoCount)
{
    physics.clear_balls();

    EXPECT_EQ(physics.get_ball_count(), 0);
}
