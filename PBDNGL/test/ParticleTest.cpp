#include<gtest/gtest.h>
#include"Particle.h"
#include"Generator.h"

TEST(Generator,construct)
{
    auto g = Generator(2);
    ASSERT_EQ(g.get_numParticles(),2);
    ASSERT_EQ(g.get_particlePosition(g.m_particles[0]).m_x,0);
    ASSERT_EQ(g.get_particlePosition(g.m_particles[0]).m_y,0);
    ASSERT_EQ(g.get_particlePosition(g.m_particles[0]).m_z,0);
    ASSERT_EQ(g.get_particlePosition(g.m_particles[1]).m_x,0);
    ASSERT_EQ(g.get_particlePosition(g.m_particles[1]).m_y,1);
    ASSERT_EQ(g.get_particlePosition(g.m_particles[1]).m_z,0);

    ASSERT_EQ(g.get_particleExtForce(g.m_particles[0]).m_x,0);
    ASSERT_EQ(g.get_particleExtForce(g.m_particles[0]).m_y,0);
    ASSERT_EQ(g.get_particleExtForce(g.m_particles[0]).m_z,0);
    ASSERT_EQ(g.get_particleExtForce(g.m_particles[1]).m_x,0);
    ASSERT_EQ(g.get_particleExtForce(g.m_particles[1]).m_y,0);
    ASSERT_EQ(g.get_particleExtForce(g.m_particles[1]).m_z,0);

    ASSERT_EQ(g.get_particleVelocity(g.m_particles[0]).m_x,0);
    ASSERT_EQ(g.get_particleVelocity(g.m_particles[0]).m_y,0);
    ASSERT_EQ(g.get_particleVelocity(g.m_particles[0]).m_z,0);
    ASSERT_EQ(g.get_particleVelocity(g.m_particles[1]).m_x,0);
    ASSERT_EQ(g.get_particleVelocity(g.m_particles[1]).m_y,0);
    ASSERT_EQ(g.get_particleVelocity(g.m_particles[1]).m_z,0);

    ASSERT_EQ(g.get_particleMass(g.m_particles[0]),10000);
    ASSERT_EQ(g.get_particleMass(g.m_particles[1]),10000);
}
