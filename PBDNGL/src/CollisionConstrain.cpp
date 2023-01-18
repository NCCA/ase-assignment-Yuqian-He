#include <iostream>
#include "CollisionConstrain.h"

collisionConstrain::collisionConstrain(){}

collisionConstrain::collisionConstrain(std::shared_ptr<ngl::Obj> _mesh,ngl::Transformation _cube_model,ngl::Mat4 _mouseGlobalTX,float _collisionStiffness)
{
    m_mouseGlobalTX=_mouseGlobalTX;
    cube_model=_cube_model;
    mesh=_mesh;
    collisionStiffness=_collisionStiffness;
    //get the facelist
    face=mesh->getFaceList();
    normal.resize(face.size()/2);
    m_objCollider.resize(normal.size());
    //get the vertex list in object space
    vertex=mesh->getVertexList();
    //change vertex from object space to world space
    for(int i=0;i<vertex.size();++i)
    {
        vertex[i]=m_mouseGlobalTX*cube_model.getMatrix() * ngl::Vec4(vertex[i],1.0f);
    }
    //inistial bool collider
    for(int i=0;i<m_objCollider.size();++i)
    {
        m_objCollider[i]=false;
    }
    //calculate every face normal
    for(int i=0;i<normal.size();++i)
    {
        auto f1 = face[i];
        ngl::Vec3 edge1 = vertex[f1.m_vert[1]] - vertex[f1.m_vert[0]];
        ngl::Vec3 edge2 = vertex[f1.m_vert[2]] - vertex[f1.m_vert[0]];
        ngl::Vec3 normal1 = edge1.cross(edge2);
        if(normal1.m_x==-0)
        {
            normal1.m_x=0;
        }
        normal1.normalize(); 
        normal[i]=normal1;
    }
}

void collisionConstrain::projection(std::shared_ptr<particleGenerator> particle, size_t _index, float originalLength)
{
    ngl::Vec3 direction;
    ngl::Real detection;
    //collision detection
    auto count=0;
    for(int i=0;i<face.size()/2;++i)
    {
        direction=particle->get_worldPosition(_index)-vertex[face[i].m_vert[0]];
        detection=direction.dot(normal[i]);
        //std::cout<<detection<<'\n';
        if(detection<0.2)
        {
            m_objCollider[i]=true;
            count++;
        }
    }
    if(count==m_objCollider.size())
    {
        particle->set_ifCollider(_index,true);
    }else
    {
        particle->set_ifCollider(_index,false);
    }

    if(particle->get_ifCollider(_index)==true)
    {
        particle->set_particleVelocity(_index,-normal[0].m_x,-normal[0].m_y,-normal[0].m_z);
    }
}