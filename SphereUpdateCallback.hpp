#ifndef SPHERE_UPDATE_HPP
#define SPHERE_UPDATE_HPP

#include "SphereUpdateCallback.hpp"
#include "BallPhysics.hpp"

#include <osg/NodeVisitor>
#include <osg/PositionAttitudeTransform>

#include <vector>
#include <eigen3/Eigen/Dense>


class SphereUpdateCallback: public osg::NodeCallback
{
public:
    SphereUpdateCallback(BallPhysics *systemPhysics);
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nodeVisitor);

protected:
    BallPhysics *physics;

};

#endif
