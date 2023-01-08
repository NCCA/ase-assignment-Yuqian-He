#include<iostream>
#include"SimulationSolver.h"

const float delta_t=0.005;

simulationSolver::simulationSolver(){}

void simulationSolver::initializeParticle(size_t _numParticle)
{
    m_ParticleGenerator.initialParticle(_numParticle);
    
    for(int i=1;i<m_ParticleGenerator.get_numParticles();++i)
    {
        m_ParticleGenerator.set_particleExtForce(i,0.0f,-9.8f,0.0f);
    }
}

void simulationSolver::renderParticle()
{
    m_ParticleGenerator.render();
}

void simulationSolver::addForce(size_t _num, float _x, float _y, float _z)
{
    m_ParticleGenerator.set_particleExtForce(_num, _x, _y, _z);
}

void simulationSolver::dampVelocity(float damp)
{
    for(int i=0; i<m_ParticleGenerator.get_numParticles();++i)
    {
        m_ParticleGenerator.set_particleDampVelocity(i,damp);
    }
}

void simulationSolver::makeProposedPosition()
{
    for(int i=1; i<m_ParticleGenerator.get_numParticles();++i)
    {
        auto acceleration=m_ParticleGenerator.get_particleExtForce(i)*m_ParticleGenerator.get_particleInverseMass(i);
        ngl::Vec3 delta = delta_t*m_ParticleGenerator.get_particleExtForce(i);

        auto _x=delta.m_x+m_ParticleGenerator.get_particleVelocity(i).m_x;
        auto _y=delta.m_y+m_ParticleGenerator.get_particleVelocity(i).m_y;
        auto _z=delta.m_z+m_ParticleGenerator.get_particleVelocity(i).m_z;

        m_ParticleGenerator.set_particleVelocity(i,_x,_y,_z);

        ngl::Vec3 h=m_ParticleGenerator.get_particlePosition(i)+delta*m_ParticleGenerator.get_particleVelocity(i);
        m_ParticleGenerator.set_particleProposedPosition(i,h.m_x,h.m_y,h.m_z);
    }

}

void simulationSolver::projectConstrain(float d, size_t steps)
{
    for(int i=0;i<steps;++i)
    {
        for(int j=0; j<m_ParticleGenerator.get_numParticles();++j)
        {
            C.distanceConstrain(&m_ParticleGenerator, j, d);
        }
    }
    
}

void simulationSolver::finalizeUpdate()
{
    for(int i=0; i<m_ParticleGenerator.get_numParticles();++i)
    {
        ngl::Vec3 p=m_ParticleGenerator.get_particleProposedPosition(i)-m_ParticleGenerator.get_particlePosition(i);
        m_ParticleGenerator.set_particleVelocity(i,(p/delta_t).m_x,(p/delta_t).m_y,(p/delta_t).m_z);

        m_ParticleGenerator.set_particlePosition(i,m_ParticleGenerator.get_particleProposedPosition(i).m_x,
                                                    m_ParticleGenerator.get_particleProposedPosition(i).m_y,
                                                    m_ParticleGenerator.get_particleProposedPosition(i).m_z);
    }
}

void simulationSolver::PBD(float damp,float d,size_t steps)
{
    dampVelocity(damp);
    makeProposedPosition();
    projectConstrain(d,steps);
    void finalizeUpdate();

}
