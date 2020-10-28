#ifndef SPHERE_UPDATE_HPP
#define SPHERE_UPDATE_HPP

#include "BallPhysics.hpp"
#include "OSGWidgetUtils.hpp"

#include <osg/NodeVisitor>
#include <osg/PositionAttitudeTransform>
#include <osg/Material>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osg/Geode>

#include <vector>
#include <eigen3/Eigen/Dense>


class SphereUpdateCallback: public osg::NodeCallback
{
public:
    SphereUpdateCallback(BallPhysics *systemPhysics);
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nodeVisitor);

protected:
    BallPhysics *physicsPtr;

};

#endif
