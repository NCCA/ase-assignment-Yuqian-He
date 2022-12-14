#ifndef GENERATOR_H_
#define GENERATOR_H_
#include <cstddef>
#include<Particle.h>
#include<vector>
#include<string_view>
#include<ngl/AbstractVAO.h>


class Generator
{
    public:
    std::vector<Particle> m_particles;
    Generator(size_t _numParticle);
    //accessor
    void set_particlePosition(Particle &i_p, float _x, float _y, float _z);
    ngl::Vec3 get_particlePosition(Particle &o_p);
    void set_particleExtForce(Particle &i_p, float _x, float _y, float _z);
    ngl::Vec3 get_particleExtForce(Particle &o_p);
    void set_particleProposedPosition(Particle &o_p);
    ngl::Vec3 get_particleProposedPosition(Particle &o_p);
    ngl::Vec3 get_particleVelocity(Particle &o_p);
    void set_particleMass(Particle &i_p, size_t mass);
    size_t get_particleMass(Particle &o_p);
    bool get_ifFixed(Particle &o_p);

    size_t get_numParticles() const;
    void update();
    void render() const;

    private:
    std::unique_ptr<ngl::AbstractVAO> m_vao;

};

#endif