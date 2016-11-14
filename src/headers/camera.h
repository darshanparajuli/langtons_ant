#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
private:
    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;

public:
    Camera();
    ~Camera();
    inline const glm::mat4& get_view_matrix() const
    {
        return m_view_matrix;
    }
    inline const glm::mat4& get_projection_matrix() const
    {
        return m_projection_matrix;
    }
    inline void move_left()
    {
        m_view_matrix = glm::translate(m_view_matrix, glm::vec3(-0.1f, 0.0f, 0.0f));
    }
};

#endif
