#ifndef CONSTRAIN_H_
#define CONSTRAIN_H_
#include"ParticleGenerator.h"
#include<iostream>

class constrain
{
    public:
    virtual void projection(std::shared_ptr<particleGenerator> particle, size_t _index, float originalLength){};
};


#endif