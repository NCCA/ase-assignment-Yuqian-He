#ifndef COLLISIONCONSTRAIN_H_
#define COLLISIONCONSTRAIN_H_
#include "Constrain.h"
#include <ngl/Obj.h>
#include <ngl/Transformation.h>

class collisionConstrain : public constrain
{
    public:
    collisionConstrain();
    collisionConstrain(std::shared_ptr<ngl::Obj> _mesh,ngl::Transformation cube_model,ngl::Mat4 m_mouseGlobalTX,float _collisionStiffness);
    void projection(std::shared_ptr<particleGenerator> particle, size_t _index, float originalLength) override;
    //void detection();
    std::shared_ptr<ngl::Obj> mesh;

    private:
    std::vector<bool> m_objCollider;
    ngl::Transformation cube_model;
    ngl::Mat4 m_mouseGlobalTX;
    std::vector<ngl::Vec3> normal;
    std::vector<ngl::Vec3> vertex;
    std::vector<ngl::Face> face;
    float collisionStiffness;
    float minDistance;
};

#endif