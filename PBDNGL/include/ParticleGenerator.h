#ifndef PARTICLEGENERATOR_H_
#define PARTICLEGENERATOR_H_
#include <cstddef>
#include<vector>
#include<ngl/Vec3.h>
#include<ngl/Vec4.h>
#include<string_view>
#include<ngl/MultiBufferVAO.h>



class particleGenerator
{
    public:
    particleGenerator(size_t _numParticle);
    void initialParticle(size_t _numParticle);
    //accessor
    void set_particlePosition(size_t _index, float _x, float _y, float _z);
    ngl::Vec3 get_particlePosition(size_t _index);
    void set_particleExtForce(size_t _index, float _x, float _y, float _z);
    ngl::Vec3 get_particleExtForce(size_t _index);
    void set_particleProposedPosition(size_t _index,float _x, float _y, float _z);
    ngl::Vec3 get_particleProposedPosition(size_t _index);
    ngl::Vec3 get_particleVelocity(size_t _index);
    void set_particleDampVelocity(size_t _index, float damp);
    void set_particleVelocity(size_t _index,float _x, float _y, float _z);
    void set_particleMass(size_t _index, size_t mass);
    float get_particleInverseMass(size_t _index);
    bool get_ifFixed(size_t _index);

    size_t get_numParticles() const;
    void render() const;
    void paint() const;

    private:
    std::vector<ngl::Vec3> m_positions;
    std::vector<ngl::Vec3> m_extForces;
    std::vector<ngl::Vec3> m_proposedPositions;
    std::vector<ngl::Vec3> m_colours;
    std::vector<ngl::Vec3> m_velocities;
    std::vector<float> m_inverseMasses;
    std::vector<bool> m_ifFixeds;
    std::unique_ptr<ngl::MultiBufferVAO> m_vao;

};

#endif