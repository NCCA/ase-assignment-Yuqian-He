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
    Generator(size_t _numParticle);
    size_t numParticles() const;
    void update();
    void render() const;

    private:
    std::vector<Particle> m_particles;
    std::unique_ptr<ngl::AbstractVAO> m_vao;

};

#endif