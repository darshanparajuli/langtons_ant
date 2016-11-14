#include "headers/ant.h"
#include <glm/glm.hpp>
#include <iostream>

Ant::Ant(Camera *camera, float w, float h)
    : Entity(camera),
      m_mesh(nullptr),
      m_shader(nullptr),
      m_texture(nullptr),
      m_width(w),
      m_height(h),
      m_x(0.0f),
      m_y(0.0f),
      m_target_x(m_x),
      m_target_y(m_y),
      m_speed(0.5f),
      m_dir(Ant::Direction::EAST)
{
    glm::vec3 vertices[] = {glm::vec3(-w / 2.0f, -h / 2.0f, 0.0f), glm::vec3(-w / 2.0f, h / 2.0f, 0.0f),
                            glm::vec3(w / 2.0f, h / 2.0f, 0.0f), glm::vec3(w / 2.0f, -h / 2.0f, 0.0f)};

    int indices[] = {0, 1, 3, 1, 2, 3};
    glm::vec2 tex_coords[] = {glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f),
                              glm::vec2(0.0f, 1.0f)};
    m_mesh = new Mesh(vertices, 4, indices, 6, tex_coords, 4);
    m_shader = new Shader();
    m_texture = new Texture("res/textures/ant.png");
}

Ant::~Ant()
{
    delete m_mesh;
    delete m_shader;
    delete m_texture;
}

void Ant::init()
{
    m_shader->init("shaders/ant.vert", "shaders/ant.frag");
    m_texture->load();
    m_transform.set_scale(glm::vec3(0.9f, 0.9f, 1.0f));
}

void Ant::update(float delta_time)
{
    float s = delta_time * m_speed;
    switch (m_dir)
    {
        case EAST:
        {
            m_x += s;
            if (m_x >= m_target_x)
            {
                m_x = m_target_x;
            }
        }
        break;
        case WEST:
        {
            m_x -= s;
            if (m_x <= m_target_x)
            {
                m_x = m_target_x;
            }
        }
        break;
        case NORTH:
        {
            m_y += s;
            if (m_y >= m_target_y)
            {
                m_y = m_target_y;
            }
        }
        break;
        case SOUTH:
        {
            m_y -= s;
            if (m_y <= m_target_y)
            {
                m_y = m_target_y;
            }
        }
        break;
    }
    if (abs(m_x - m_target_x) < 0.001f)
    {
        m_x = m_target_x;
    }
    if (abs(m_y - m_target_y) < 0.001f)
    {
        m_y = m_target_y;
    }
    m_transform.set_position(glm::vec3(m_x, m_y, 0.0f));
}

void Ant::render()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_mesh->bind();
    m_texture->bind();
    m_shader->bind();

    m_shader->set_uniform_mat4("projection", m_camera->get_projection_matrix());
    m_shader->set_uniform_mat4("view", m_camera->get_view_matrix());
    m_shader->set_uniform_mat4("transform", m_transform.apply_transform(glm::mat4(1.0f)));

    m_mesh->draw();

    m_shader->unbind();
    m_texture->unbind();
    m_mesh->unbind();

    glDisable(GL_BLEND);
}

void Ant::turn_left()
{
    switch (m_dir)
    {
        case EAST:
        {
            m_target_y += m_height;
            m_dir = Ant::Direction::NORTH;
        }
        break;
        case WEST:
        {
            m_target_y -= m_height;
            m_dir = Ant::Direction::SOUTH;
        }
        break;
        case NORTH:
        {
            m_target_x -= m_width;
            m_dir = Ant::Direction::WEST;
        }
        break;
        default:
        {
            m_target_x += m_width;
            m_dir = Ant::Direction::EAST;
        }
        break;
    }
}

void Ant::turn_right()
{
    switch (m_dir)
    {
        case EAST:
        {
            m_target_y -= m_height;
            m_dir = Ant::Direction::SOUTH;
        }
        break;
        case WEST:
        {
            m_target_y += m_height;
            m_dir = Ant::Direction::NORTH;
        }
        break;
        case NORTH:
        {
            m_target_x += m_width;
            m_dir = Ant::Direction::EAST;
        }
        break;
        default:
        {
            m_target_x -= m_width;
            m_dir = Ant::Direction::WEST;
        }
        break;
    }
}

void Ant::reset()
{
    m_dir = Ant::Direction::EAST;
    m_x = 0.0f;
    m_y = 0.0f;
    m_target_x = 0.0f;
    m_target_y = 0.0f;
    m_speed = 0.5f;
}
