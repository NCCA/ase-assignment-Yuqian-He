#ifndef SIMULATIONSOLVER_H_
#define SIMULATIONSOLVER_H_
#include"particleGenerator.h"

class simulationSolver
{
    public:

    private:
    std::unique_ptr<particleGenerator> m_ParticleGenerator;
};
#endif