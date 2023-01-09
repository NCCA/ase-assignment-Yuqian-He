#ifndef CONSTRAIN_H_
#define CONSTRAIN_H_
#include"ParticleGenerator.h"

class constrain
{
    public:

    constrain();
    void set_stiffness(float _stiffness);
    float get_stiffness();
    void distanceConstrain(std::shared_ptr<particleGenerator> particle, size_t _index, float originalLength);

    private:
    float m_stiffness;
};


#endif