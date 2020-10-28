#include "SphereUpdateCallback.hpp"


SphereUpdateCallback::SphereUpdateCallback(BallPhysics *systemPhysics): physicsPtr{systemPhysics}
{
}

void SphereUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* visitingNode)
{
    osg::Group *parent = node->getParent(0);
    int nodeNumber = parent->getChildIndex(node);

    osg::Vec3f positionOfBall(physicsPtr->get_ball_ptr(nodeNumber-2)->position[0], physicsPtr->get_ball_ptr(nodeNumber-2)->position[1], physicsPtr->get_ball_ptr(nodeNumber-2)->position[2]);
    osg::PositionAttitudeTransform *ballTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    ballTransformation->setPosition(positionOfBall);

    osg::Geode *ballGeode = ballTransformation->getChild(0)->asGeode();
    osg::ShapeDrawable *ballShapeDrawable = dynamic_cast<osg::ShapeDrawable *> (ballGeode->getDrawable(0));
    ballShapeDrawable->setColor(osgwidgetutils::hue_to_osg_rgba_decimal(physicsPtr->get_ball_ptr(nodeNumber-2)->color));

    osg::Sphere *ball = new osg::Sphere(osg::Vec3(0.f, 0.f, 0.f), physicsPtr->get_ball_ptr(nodeNumber-2)->radius);
    ballShapeDrawable->setShape(ball);

    traverse(node, visitingNode);
}
