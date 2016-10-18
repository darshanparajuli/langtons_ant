#include "grid.h"
#include <iostream>

Grid::Grid(int row_count, int col_count)
    : m_row_count(row_count), m_col_count(col_count), m_mesh(nullptr), m_texture(nullptr), m_shader(nullptr)
{
    m_grid = new int *[row_count];
    for (int i = 0; i < row_count; i++)
    {
        m_grid[i] = new int[col_count];
    }
    reset();

    glm::vec3 vertices[] = {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.5f, -0.5f, 0.0f),
                            glm::vec3(-0.5f, -0.5f, 0.0f)};
    int indices[] = {0, 1, 2, 0, 2, 3};

    glm::vec2 tex_coord[] = {glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f),
                             glm::vec2(0.0f, 1.0f)};
    m_mesh = new Mesh(vertices, 4, indices, 6, tex_coord, 4);
    m_shader = new Shader();
    m_texture = new Texture("res/textures/ant.png");
}

Grid::~Grid()
{
    for (int i = 0; i < m_row_count; i++)
    {
        delete[] m_grid[i];
    }
    delete[] m_grid;
}

void Grid::reset()
{
    for (int i = 0; i < m_row_count; i++)
    {
        for (int j = 0; j < m_col_count; j++)
        {
            m_grid[i][j] = 0;
        }
    }
}

void Grid::set_value(int row, int col, int value) { m_grid[row][col] = value; }
int Grid::get_value(int row, int col) { return m_grid[row][col]; }
void Grid::draw()
{
    m_shader->bind();
    m_texture->bind();
    m_mesh->draw();
    m_shader->unbind();
    m_texture->unbind();
}

void Grid::print()
{
    std::cout << "Grid" << std::endl;
    for (int r = 0; r < m_row_count; r++)
    {
        for (int c = 0; c < m_col_count; c++)
        {
            std::cout << m_grid[r][c] << " ";
        }
        std::cout << std::endl;
    }
}
