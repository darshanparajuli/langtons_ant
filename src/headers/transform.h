#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/glm.hpp>

class Transform
{
private:
    glm::vec3 m_scale;
    float m_rotation;
    glm::vec3 m_position;

public:
    Transform(void);
    ~Transform(void);
    glm::mat4 apply_transform(const glm::mat4 &model);
    inline float get_rotation(void) const
    {
        return m_rotation;
    }
    inline void set_rotation(float r)
    {
        m_rotation = r;
    }
    inline glm::vec3 get_scale(void) const
    {
        return m_scale;
    }
    inline void set_scale(glm::vec3 s)
    {
        m_scale = s;
    }
    inline glm::vec3 get_position(void)
    {
        return m_position;
    }
    inline void set_position(glm::vec3 p)
    {
        m_position = p;
    }
};

#endif
