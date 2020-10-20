#include "SphereUpdateCallback.hpp"


SphereUpdateCallback::SphereUpdateCallback(BallPhysics *systemPhysics): physics{systemPhysics}
{
}

void SphereUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* visitingNode)
{
    osg::Group *parent = node->getParent(0);
    int nodeNumber = parent->getChildIndex(node);
    osg::Vec3f positionOfBall(physics->balls[nodeNumber].position[0], physics->balls[nodeNumber].position[1], physics->balls[nodeNumber].position[2]);
    osg::PositionAttitudeTransform *ballTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    ballTransformation->setPosition(positionOfBall);

    traverse(node, visitingNode);
}
