#ifndef DISTANCECONSTRAIN_H_
#define DISTANCECONSTRAIN_H_
#include "Constrain.h"

class distanceConstrain : public constrain
{
    public:
    distanceConstrain();
    distanceConstrain(float _stiffness):stiffness(_stiffness){}
    void set_stiffness(float _stiffness);
    float get_stiffness();
    void projection(std::shared_ptr<particleGenerator> particle, size_t _index, float originalLength) override;

    float stiffness;
};

#endif