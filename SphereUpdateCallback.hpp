#ifndef SPHERE_UPDATE_HPP
#define SPHERE_UPDATE_HPP

#include "SphereUpdateCallback.hpp"

#include <osg/NodeVisitor>
#include <osg/PositionAttitudeTransform>

#include <vector>

class SphereUpdateCallback: public osg::NodeCallback
{
public:
    SphereUpdateCallback();
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nodeVisitor);
protected:
    unsigned int animationFrame{0};
    double animationStepScale{1.0/1.0};
};

#endif
