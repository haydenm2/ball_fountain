#ifndef BALLPHYSICS_HPP
#define BALLPHYSICS_HPP

#include "Ball.hpp"
#include <vector>

class BallPhysics
{
public:
    BallPhysics();
    ~BallPhysics();
    void add_ball();
private:
    unsigned int ballCount{0};

};

#endif
