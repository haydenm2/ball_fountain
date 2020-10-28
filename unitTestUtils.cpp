#include "unitTestUtils.hpp"

void EXPECT_VECTOR3_FLOAT_EQ(Eigen::Vector3f inputVector, Eigen::Vector3f truthVector)
{
    for(float index = 0; index < 3; index++)
    {
        EXPECT_EQ(inputVector[index], truthVector[index]);
    }
}

void EXPECT_OSG_VECTOR4_EQ(osg::Vec4 inputVector, osg::Vec4 truthVector)
{
    for(float index = 0; index < 4; index++)
    {
        EXPECT_EQ(inputVector[index], truthVector[index]);
    }
}
