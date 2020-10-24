#include "SphereUpdateCallback.hpp"


SphereUpdateCallback::SphereUpdateCallback(BallPhysics *systemPhysics): physics{systemPhysics}
{
}

void SphereUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* visitingNode)
{
    osg::Group *parent = node->getParent(0);
    int nodeNumber = parent->getChildIndex(node);
    osg::Vec3f positionOfBall(physics->balls[nodeNumber-2].position[0], physics->balls[nodeNumber-2].position[1], physics->balls[nodeNumber-2].position[2]);
    osg::PositionAttitudeTransform *ballTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    ballTransformation->setPosition(positionOfBall);
    osg::Geode *ballGeode = dynamic_cast<osg::Geode *> (ballTransformation->getChild(0));
    osg::ShapeDrawable *ballShapeDrawable = dynamic_cast<osg::ShapeDrawable *> (ballGeode->getDrawable(0));
    ballShapeDrawable->setColor(osg::Vec4(physics->balls[nodeNumber-2].color/255.0, 0.f, 1.f, 1.f));
    osg::Sphere* sphere = dynamic_cast<osg::Sphere *> (ballShapeDrawable->getShape());
    sphere->setRadius(physics->balls[nodeNumber-2].radius);

    traverse(node, visitingNode);
}
