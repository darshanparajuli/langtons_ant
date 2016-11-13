#include "headers/camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
    : m_view_matrix(
          glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
      m_projection_matrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 100.0f))
{
}

Camera::~Camera()
{
}
