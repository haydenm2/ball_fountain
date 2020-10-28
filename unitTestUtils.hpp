#ifndef UNIT_TEST_UTILS_HPP
#define UNIT_TEST_UTILS_HPP

#include "gtest/gtest.h"
#include <eigen3/Eigen/Dense>
#include <osg/Vec4>

void EXPECT_VECTOR3_FLOAT_EQ(Eigen::Vector3f inputVector, Eigen::Vector3f truthVector);
void EXPECT_OSG_VECTOR4_EQ(osg::Vec4 inputVector, osg::Vec4 truthVector);

#endif
