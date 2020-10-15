#include "SphereUpdateCallback.hpp"


SphereUpdateCallback::SphereUpdateCallback()
{
}

void SphereUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* visitingNode)
{
    std::chrono::duration<double> localTime = std::chrono::high_resolution_clock::now() - animationStartTimeOffset;
    animationTime = localTime.count();

    osg::Vec3d positionOfBall(0.0, 0.0, animationTimeScale*animationTime);
    osg::PositionAttitudeTransform *ballTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    ballTransformation->setPosition(positionOfBall);

    traverse(node, visitingNode);
}
