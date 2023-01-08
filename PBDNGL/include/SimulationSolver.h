#ifndef SIMULATIONSOLVER_H_
#define SIMULATIONSOLVER_H_
#include"ParticleGenerator.h"
#include"Constrain.h"

class simulationSolver
{
    public:
    simulationSolver();
    void initializeParticle(int _num);
    void renderParticle();
    void addForce(size_t _num, float _x, float _y, float _z);
    void dampVelocity(float damp);
    void makeProposedPosition();
    void PBD(size_t step);
    void projectConstrain(size_t _index, float d, size_t steps);
    void finalizeUpdate();

    private:
    particleGenerator* m_ParticleGenerator;
    constrain C;
};
#endif