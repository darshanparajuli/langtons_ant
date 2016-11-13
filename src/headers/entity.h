#ifndef ENTITY_H_
#define ENTITY_H_

#include "camera.h"
#include "transform.h"
#include <glm/glm.hpp>

class Entity
{
protected:
    Transform m_transform;
    Camera *m_camera;

public:
    Entity(Camera *camera) : m_transform(Transform()), m_camera(camera)
    {
    }
    virtual ~Entity(void)
    {
    }
    virtual void init() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render() = 0;
    inline void set_transform(const Transform &transform)
    {
        m_transform = transform;
    }
};

#endif
