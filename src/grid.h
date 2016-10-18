#ifndef GRID_H_
#define GRID_H_

#include "mesh.h"
#include "shader.h"
#include "texture.h"

class Grid
{
private:
    int m_row_count;
    int m_col_count;
    int **m_grid;
    Mesh *m_mesh;
    Texture *m_texture;
    Shader *m_shader;

public:
    Grid(int row_count, int col_count);
    ~Grid();
    void reset();
    void set_value(int row, int col, int val);
    int get_value(int row, int col);
    void print(void);
    void draw(void);

public:
    inline int get_row_count() const { return m_row_count; }
    inline int get_col_count() const { return m_col_count; }
};

#endif
