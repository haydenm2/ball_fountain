#include "SphereUpdateCallback.hpp"


SphereUpdateCallback::SphereUpdateCallback()
{
}

void SphereUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* visitingNode)
{
    animationFrame++;

    osg::Vec3d positionOfBall(0.0, 0.0, animationStepScale*animationFrame);
    osg::PositionAttitudeTransform *ballTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    ballTransformation->setPosition(positionOfBall);

    traverse(node, visitingNode);

    if(animationFrame>=20)
        animationFrame=0;
}
