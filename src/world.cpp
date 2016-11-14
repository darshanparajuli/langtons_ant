#include "headers/world.h"
#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "headers/utils.h"

World::World(Camera *camera, int row_count, int col_count)
    : Entity(camera),
      m_row_count(row_count),
      m_col_count(col_count),
      m_cell_width(2.0f / (float)col_count),
      m_cell_height(2.0f / (float)row_count),
      m_speed(5.0f),
      m_grid(nullptr),
      m_cur_scale(nullptr),
      m_target_scale(nullptr),
      m_mesh(nullptr),
      m_shader(nullptr),
      m_texture(nullptr),
      m_texture_block(nullptr),
      m_render_grid(false)
{
    m_grid = new int *[row_count];
    m_cur_scale = new float *[row_count];
    m_target_scale = new float *[row_count];
    for (int i = 0; i < row_count; ++i)
    {
        m_grid[i] = new int[col_count];
        m_cur_scale[i] = new float[col_count];
        m_target_scale[i] = new float[col_count];
    }
    reset();

    glm::vec3 vertices[] = {glm::vec3(-m_cell_width / 2.0f, -m_cell_height / 2.0f, 0.0f),
                            glm::vec3(-m_cell_width / 2.0f, m_cell_height / 2.0f, 0.0f),
                            glm::vec3(m_cell_width / 2.0f, m_cell_height / 2.0f, 0.0f),
                            glm::vec3(m_cell_width / 2.0f, -m_cell_height / 2.0f, 0.0f)};
    int indices[] = {0, 1, 3, 1, 2, 3};
    glm::vec2 tex_coords[] = {glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f),
                              glm::vec2(0.0f, 1.0f)};
    m_mesh = new Mesh(vertices, 4, indices, 6, tex_coords, 4);
    m_shader = new Shader();
    m_texture = new Texture("res/textures/line.png");
    m_texture_block = new Texture("res/textures/block.png");
}

World::~World()
{
    for (int i = 0; i < m_row_count; ++i)
    {
        delete[] m_grid[i];
        delete[] m_cur_scale[i];
        delete[] m_target_scale[i];
    }
    delete[] m_grid;
    delete[] m_cur_scale;
    delete[] m_target_scale;
    delete m_mesh;
    delete m_shader;
    delete m_texture;
    delete m_texture_block;
}

void World::reset()
{
    for (int i = 0; i < m_row_count; ++i)
    {
        for (int j = 0; j < m_col_count; ++j)
        {
            m_grid[i][j] = 0;
            m_cur_scale[i][j] = 0.0f;
            m_target_scale[i][j] = 0.0f;
        }
    }
}

void World::init()
{
    m_shader->init("shaders/world.vert", "shaders/world.frag");
    m_texture->load();
    m_texture_block->load();
}

void World::update(float delta_time)
{
    for (int r = 0; r < m_row_count; ++r)
    {
        for (int c = 0; c < m_col_count; ++c)
        {
            float t = delta_time * m_speed;
            t = utils::clamp(t, 0.0f, 1.0f);
            m_cur_scale[r][c] = utils::lerp(m_cur_scale[r][c], m_target_scale[r][c], t);
        }
    }
}

void World::render()
{
    m_mesh->bind();
    m_shader->bind();

    m_shader->set_uniform_mat4("projection", m_camera->get_projection_matrix());
    m_shader->set_uniform_mat4("view", m_camera->get_view_matrix());

    m_texture_block->bind();
    m_shader->set_uniform_float("intensity", 1.0f);

    glm::mat4 model = glm::mat4(1.0f);
    m_transform.set_scale(glm::vec3(0.9f, 0.9f, 1.0f));

    for (int r = 0; r < m_row_count; ++r)
    {
        for (int c = 0; c < m_col_count; ++c)
        {
            float x = (c - m_col_count / 2) * m_cell_width;
            float y = (r - m_row_count / 2) * m_cell_height;
            m_transform.set_position(glm::vec3(x, y, 0.0f));
            float scale = m_cur_scale[r][c];
            m_transform.set_scale(glm::vec3(scale, scale, 1.0f));
            m_shader->set_uniform_mat4("transform", m_transform.apply_transform(model));
            m_mesh->draw();
        }
    }

    m_texture_block->unbind();

    if (m_render_grid)
    {
        m_texture->bind();

        m_shader->set_uniform_float("intensity", 0.5f);

        float vline_width = 10.0f / m_col_count;
        m_transform.set_scale(glm::vec3(vline_width, 1.0f * m_row_count * 2, 1.0f));
        for (int i = -m_col_count / 2 + 1; i <= m_col_count / 2; ++i)
        {
            m_transform.set_position(glm::vec3(i * m_cell_width - m_cell_width / 2.0f, -1.0f, 0.0f));
            m_shader->set_uniform_mat4("transform", m_transform.apply_transform(model));
            m_mesh->draw();
        }
        float hline_width = 10.0f / m_row_count;
        m_transform.set_scale(glm::vec3(1.0f * m_col_count * 2, hline_width, 1.0f));
        for (int i = -m_row_count / 2 + 1; i <= m_row_count / 2; ++i)
        {
            m_transform.set_position(glm::vec3(-1.0f, i * m_cell_height - m_cell_height / 2.0f, 0.0f));
            m_shader->set_uniform_mat4("transform", m_transform.apply_transform(model));
            m_mesh->draw();
        }

        m_texture->unbind();
    }

    m_shader->unbind();
    m_mesh->unbind();
}

void World::print()
{
    std::cout << "World" << std::endl;
    for (int r = 0; r < m_row_count; ++r)
    {
        for (int c = 0; c < m_col_count; ++c)
        {
            std::cout << m_grid[r][c] << " ";
        }
        std::cout << std::endl;
    }
}

void World::set_value(int row, int col, int val)
{
    m_grid[row][col] = val;
    m_target_scale[row][col] = val == EMPTY ? 0.0f : 0.9f;
}
