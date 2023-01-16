#include <iostream>
#include "CollisionConstrain.h"

collisionConstrain::collisionConstrain(){}

collisionConstrain::collisionConstrain(std::shared_ptr<ngl::Obj> _mesh,ngl::Transformation _cube_model,ngl::Mat4 _mouseGlobalTX)
{
    m_mouseGlobalTX=_mouseGlobalTX;
    cube_model=_cube_model;
    mesh=_mesh;
    //get the facelist
    face=mesh->getFaceList();
    normal.resize(face.size());
    m_objCollider.resize(face.size());
    auto n=mesh->getNormalList();
    //calculate every face normal
    for(int i=0;i<face.size();++i)
    {
        auto f1 = face[i];
        ngl::Vec3 normal1 = normal[f1.m_vert[0]] + normal[f1.m_vert[1]] + normal[f1.m_vert[2]];
        normal1.normalize(); 
        normal[i]=normal1;
    }
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
}

void collisionConstrain::projection(std::shared_ptr<particleGenerator> particle, size_t _index, float originalLength)
{
    //collision detection
    auto count=0;
    for(int i=0;i<face.size();++i)
    {
        auto direction=particle->get_particlePosition(_index)-vertex[face[i].m_vert[0]];
        auto detection=direction.dot(normal[i]);
        if(detection<0)
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

}