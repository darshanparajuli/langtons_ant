#include "grid.h"
#include <iostream>

Grid::Grid(int row_count, int col_count) : m_row_count(row_count), m_col_count(col_count)
{
    m_grid = new int *[row_count];
    for (int i = 0; i < row_count; i++)
    {
        m_grid[i] = new int[col_count];
    }
    reset();
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

void Grid::set_value(int row, int col, int value)
{
    m_grid[row][col] = value;
}

int Grid::get_value(int row, int col)
{
    return m_grid[row][col];
}

void Grid::draw()
{
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
