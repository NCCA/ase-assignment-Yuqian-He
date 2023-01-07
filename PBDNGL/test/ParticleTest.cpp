#include<gtest/gtest.h>
#include"Particle.h"
#include"ParticleGenerator.h"
#include<iostream>
#include<ngl/Vec3.h>
#include<cmath>

//two points length
float pointLength(ngl::Vec3 p1, ngl::Vec3 p2)
{
    float Len = sqrt(pow(p2.m_x-p1.m_x, 2)+pow(p2.m_y-p1.m_y,2)+pow(p2.m_z-p1.m_z,2));
    return Len;
}

void distanceConstrain(ngl::Vec3 p1, ngl::Vec3 p2,float originalLength, float k)
{
    auto currentLength = pointLength(p1,p2);
    auto displacement = (currentLength-originalLength)/currentLength;
    //p1.force -=
}

TEST(Generator,construct)
{
    //std::cout<<"1111"<<'\n';
    //ngl::Vec3 p1 = {1.0f,4.0f,3.0f};
    //ngl::Vec3 p2 = {-1.0f,2.0f,3.0f};
    std::unique_ptr<particleGenerator> m_ParticleGenerator;
    //m_ParticleGenerator=std::make_unique<particleGenerator>(1);
    //auto g = particleGenerator(2);
    //std::cout<<pointLength(p1,p2)<<'\n';
    //ASSERT_EQ(pointLength(p1,p2),sqrt(8));
    // ASSERT_EQ(g.get_particlePosition(0).m_x,0);
    // ASSERT_EQ(g.get_particlePosition(0).m_y,0);
    // ASSERT_EQ(g.get_particlePosition(0).m_z,0);
    // ASSERT_EQ(g.get_particlePosition(1).m_x,0);
    // ASSERT_EQ(g.get_particlePosition(1).m_y,1);
    // ASSERT_EQ(g.get_particlePosition(1).m_z,0);

    // ASSERT_EQ(g.get_particleExtForce(0).m_x,0);
    // ASSERT_EQ(g.get_particleExtForce(0).m_y,0);
    // ASSERT_EQ(g.get_particleExtForce(0).m_z,0);
    // ASSERT_EQ(g.get_particleExtForce(1).m_x,0);
    // ASSERT_EQ(g.get_particleExtForce(1).m_y,0);
    // ASSERT_EQ(g.get_particleExtForce(1).m_z,0);

    // ASSERT_EQ(g.get_ifFixed(0),false);
}


