#include "gtest/gtest.h"
#include "BallPhysics.hpp"
#include "OSGWidgetUtils.hpp"

void EXPECT_VECTOR3_FLOAT_EQ(Eigen::Vector3f inputVector, Eigen::Vector3f truthVector)
{
    for(float index = 0; index < 3; index++)
    {
        EXPECT_EQ(inputVector[index], truthVector[index]);
    }
}

void EXPECT_OSG_VECTOR4_EQ(osg::Vec4 inputVector, osg::Vec4 truthVector)
{
    for(float index = 0; index < 4; index++)
    {
        EXPECT_EQ(inputVector[index], truthVector[index]);
    }
}


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

TEST(OSGUtilsTests, WhenConverting0HueToRGB_ExpectRed)
{
    int inputHue{0};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting60HueToRGB_ExpectRedGreen)
{
    int inputHue{60};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting120HueToRGB_ExpectGreen)
{
    int inputHue{120};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting180HueToRGB_ExpectGreenBlue)
{
    int inputHue{180};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting240HueToRGB_ExpectBlue)
{
    int inputHue{240};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting300HueToRGB_ExpectRedBlue)
{
    int inputHue{300};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(1.0f, 0.0f, 1.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConverting360HueToRGB_ExpectRed)
{
    int inputHue{360};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
}

TEST(OSGUtilsTests, WhenConvertingOutOfRangeHueToRGB_ExpectBlack)
{
    int inputHue{600};
    osg::Vec4 rgbOutput{osgwidgetutils::hue_to_osg_rgba_decimal(inputHue)};
    osg::Vec4 rgbExpected{osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f)};
    EXPECT_OSG_VECTOR4_EQ(rgbOutput, rgbExpected);
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
    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);
    EXPECT_EQ(physics.balls[0].radius, radius);
    EXPECT_EQ(physics.balls[0].mass, mass);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, position);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocity);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
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
    float coefficientOfRestitution{2};

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};

    BallPhysics physics;

    for(int index{0}; index < numberOfBalls; index++)
    {
        physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);
    }

    for(int index{0}; index < numberOfBalls; index++)
    {
        EXPECT_EQ(physics.balls[index].radius, radius);
        EXPECT_EQ(physics.balls[index].mass, mass);
        EXPECT_EQ(physics.balls[index].color, color);
        EXPECT_VECTOR3_FLOAT_EQ(physics.balls[index].position, position);
        EXPECT_VECTOR3_FLOAT_EQ(physics.balls[index].velocity, velocity);
        EXPECT_VECTOR3_FLOAT_EQ(physics.balls[index].acceleration, accelerationExpected);
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
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);

    float deltaTime{5};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
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
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);

    float deltaTime{3};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocityExpected1 = velocity + accelerationExpected*deltaTime;
    Eigen::Vector3f positionExpected1 = position + velocityExpected1*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);
    physics.update(deltaTime);

    velocityExpected1 = velocityExpected1 + accelerationExpected*deltaTime;
    positionExpected1 = positionExpected1 + velocityExpected1*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    Eigen::Vector3f velocityExpected2 = velocity + accelerationExpected*deltaTime;
    Eigen::Vector3f positionExpected2 = position + velocityExpected2*deltaTime + 0.5*accelerationExpected*pow(deltaTime, 2);

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocityExpected1);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, positionExpected1);

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].acceleration, accelerationExpected);
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
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
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
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
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
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
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
    float coefficientOfRestitution{1.0};

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
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
    float coefficientOfRestitution{0.3};

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
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
    float coefficientOfRestitution{0.7};

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
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
    float coefficientOfRestitution1{1.0};

    physics.add_ball(radius1, mass1, color1, position1, velocity1, coefficientOfRestitution1);

    float radius2{5};
    float mass2{2};
    unsigned int color2{128};
    Eigen::Vector3f position2{1, 1, 101};
    Eigen::Vector3f velocity2{0, -10, 0};
    float coefficientOfRestitution2{1.0};

    physics.add_ball(radius2, mass2, color2, position2, velocity2, coefficientOfRestitution2);

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

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocity1Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, position1Expected);

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].velocity, velocity2Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].position, position2Expected);
}

TEST(PhysicsTests, WhenUpdatingBalltoBallWithNoCollision_ExpectNoChange)
{
    BallPhysics physics;

    float radius1{4};
    float mass1{5};
    unsigned int color1{128};
    Eigen::Vector3f position1{0, 0, 100};
    Eigen::Vector3f velocity1{0, 10, 0};
    float coefficientOfRestitution1{1.0};

    physics.add_ball(radius1, mass1, color1, position1, velocity1, coefficientOfRestitution1);

    float radius2{5};
    float mass2{2};
    unsigned int color2{128};
    Eigen::Vector3f position2{10, 10, 10};
    Eigen::Vector3f velocity2{0, -10, 0};
    float coefficientOfRestitution2{1.0};

    physics.add_ball(radius2, mass2, color2, position2, velocity2, coefficientOfRestitution2);

    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    Eigen::Vector3f velocity1Expected = velocity1;
    Eigen::Vector3f position1Expected = position1;

    Eigen::Vector3f velocity2Expected = velocity2;
    Eigen::Vector3f position2Expected = position2;

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].velocity, velocity1Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].position, position1Expected);

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].acceleration, accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].velocity, velocity2Expected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[1].position, position2Expected);
}

TEST(PhysicsTests, WhenAddingBalls_ExpectIncreasedBallCount)
{
    BallPhysics physics;

    float radius1{4};
    float mass1{5};
    unsigned int color1{128};
    Eigen::Vector3f position1{0, 0, 100};
    Eigen::Vector3f velocity1{0, 10, 0};
    float coefficientOfRestitution1{1.0};
    int numberOfBalls{50};

    for(int count{0}; count<numberOfBalls; count++)
        physics.add_ball(radius1, mass1, color1, position1, velocity1, coefficientOfRestitution1);

    EXPECT_EQ(physics.ballCount, numberOfBalls);
}

TEST(PhysicsTests, WhenAddingBallsOverMaxLimit_ExpectMaxBallCount)
{
    BallPhysics physics;

    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 100};
    Eigen::Vector3f velocity{0, 10, 0};
    float coefficientOfRestitution{1.0};
    unsigned int numberOfBalls{physics.maxBallCount+10};

    for(int count{0}; count<numberOfBalls; count++)
        physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);

    EXPECT_EQ(physics.ballCount, physics.maxBallCount);
}

TEST(PhysicsTests, WhenReplacingBallAtSpecificIndex_ExpectCorrectBallParametersAtIndex)
{
    BallPhysics physics;

    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 100};
    Eigen::Vector3f velocity{0, 10, 0};
    float coefficientOfRestitution{1.0};

    for(int count{0}; count<physics.maxBallCount; count++)
        physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);

    unsigned int replaceIndex{10};

    float newRadius{11};
    float newMass{13};
    unsigned int newColor{17};
    Eigen::Vector3f newPosition{1, 1, 1};
    Eigen::Vector3f newVelocity{1, 1, 1};
    Eigen::Vector3f newAcceleration{1, 1, 1};
    float newCoefficientOfRestitution{0.5};
    physics.update_ball(replaceIndex, newRadius, newMass, newColor, newPosition, newVelocity, newAcceleration, newCoefficientOfRestitution);

    EXPECT_EQ(physics.balls[replaceIndex].radius, newRadius);
    EXPECT_EQ(physics.balls[replaceIndex].mass, newMass);
    EXPECT_EQ(physics.balls[replaceIndex].color, newColor);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[replaceIndex].position, newPosition);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[replaceIndex].velocity, newVelocity);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[replaceIndex].acceleration, newAcceleration);
    EXPECT_EQ(physics.balls[replaceIndex].coefficientOfRestitution, newCoefficientOfRestitution);
}

TEST(PhysicsTests, WhenAddingBallOverMaxLimit_ExpectCorrectBallReplacement)
{
    BallPhysics physics;

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
    unsigned int numberOfBalls{physics.maxBallCount+overCount};

    for(int count{0}; count<numberOfBalls; count++)
    {
        if(count < physics.maxBallCount)
            physics.add_ball(radius1, mass1, color1, position1, velocity1, coefficientOfRestitution1);
        else
            physics.add_ball(radius2, mass2, color2, position2, velocity2, coefficientOfRestitution2);
    }

    EXPECT_EQ(physics.balls[overCount-1].radius, radius2);
    EXPECT_EQ(physics.balls[overCount-1].mass, mass2);
    EXPECT_EQ(physics.balls[overCount-1].color, color2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[overCount-1].position, position2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[overCount-1].velocity, velocity2);
    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[overCount-1].acceleration, accelerationExpected);
    EXPECT_EQ(physics.balls[overCount-1].coefficientOfRestitution, coefficientOfRestitution2);
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

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);
    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};
    float velocityMagnitude = velocity.norm();
    Eigen::Vector3f dragForce = -(0.5*fluidDensity*pow(velocityMagnitude, 2)*physics.dragCoefficient*(M_PI*pow(radius, 2)))/mass*velocity/velocityMagnitude;

    accelerationExpected += dragForce;

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
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

    physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);
    float deltaTime{0.0};
    physics.update(deltaTime);

    Eigen::Vector3f accelerationExpected{0, 0, -9.81};

    EXPECT_VECTOR3_FLOAT_EQ(physics.balls[0].acceleration, accelerationExpected);
}

TEST(PhysicsTests, WhenClearingBalls_ExpectNoBallsAndNoCount)
{
    BallPhysics physics{BallPhysics()};

    float radius{4};
    float mass{5};
    unsigned int color{128};
    Eigen::Vector3f position{0, 0, 100};
    Eigen::Vector3f velocity{0, 0, 0};
    float coefficientOfRestitution{1.0};

    int numberOfBallsToAdd{20};
    for(int ballNumber{0}; ballNumber<numberOfBallsToAdd; ballNumber++)
        physics.add_ball(radius, mass, color, position, velocity, coefficientOfRestitution);
    physics.clear_balls();

    EXPECT_EQ(physics.ballCount, 0);
    EXPECT_EQ(physics.balls.size(), 0);
}

TEST(PhysicsTests, WhenClearingNoBalls_ExpectNoBallsAndNoCount)
{
    BallPhysics physics{BallPhysics()};
    physics.clear_balls();

    EXPECT_EQ(physics.ballCount, 0);
    EXPECT_EQ(physics.balls.size(), 0);
}
