#ifndef SPHERE_UPDATE_HPP
#define SPHERE_UPDATE_HPP

#include "SphereUpdateCallback.hpp"
#include "BallPhysics.hpp"

#include <osg/NodeVisitor>
#include <osg/PositionAttitudeTransform>

#include <vector>
#include <chrono>


class SphereUpdateCallback: public osg::NodeCallback
{
public:
    SphereUpdateCallback();
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nodeVisitor);
protected:
    std::chrono::time_point<std::chrono::high_resolution_clock> animationStartTimeOffset{std::chrono::high_resolution_clock::now()};
    double animationTime{0.0};
    double animationTimeScale{1.0};
};

#endif
