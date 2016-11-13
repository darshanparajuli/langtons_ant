#include "headers/transform.h"
#include <glm/gtx/transform.hpp>

Transform::Transform() : m_scale(glm::vec3(1.0f, 1.0f, 1.0f)), m_rotation(0.0f), m_position(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::apply_transform(const glm::mat4 &model)
{
    glm::mat4 m = glm::translate(model, m_position);
    m = glm::rotate(m, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    m = glm::scale(m, m_scale);
    return m;
}
