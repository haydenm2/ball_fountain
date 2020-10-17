#include "SphereUpdateCallback.hpp"


SphereUpdateCallback::SphereUpdateCallback()
{
    double radius{2};
    double mass{5};
    unsigned int color{128};
    std::array<double, 3> position{0.0, 0.0, 2.0};
    std::array<double, 3> velocity{0.0, 0.0, 20.0};
    std::array<double, 3> acceleration{0.0, 0.0, physics.gravity};
    double coefficientOfRestitution{0.5};

    physics.add_ball(radius, mass, color, position, velocity, acceleration, coefficientOfRestitution);
}

void SphereUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* visitingNode)
{
    double deltaTime{1.0/10.0};
    physics.update(deltaTime);
    osg::Vec3d positionOfBall(physics.balls[0].position[0], physics.balls[0].position[1], physics.balls[0].position[2]);
    osg::PositionAttitudeTransform *ballTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    ballTransformation->setPosition(positionOfBall);

    traverse(node, visitingNode);
}
