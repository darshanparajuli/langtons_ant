#ifndef WORLD_H_
#define WORLD_H_

#include "entity.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

class World : public Entity
{
public:
    enum
    {
        EMPTY,
        ANT,
        NON_EMPTY
    };

private:
    int m_row_count;
    int m_col_count;
    float m_cell_width;
    float m_cell_height;
    int **m_grid;

    Mesh *m_mesh;
    Shader *m_shader;
    Texture *m_texture;
    Texture *m_texture_block;

    bool m_render_grid;

public:
    World(Camera *camera, int row_count, int col_count);
    virtual ~World();

    virtual void init();
    virtual void update(float delta_time);
    virtual void render();
    void reset(void);
    void print(void);

    inline void set_value(int row, int col, int val)
    {
        m_grid[row][col] = val;
    }
    inline int get_value(int row, int col) const
    {
        return m_grid[row][col];
    }
    inline int get_row_count(void) const
    {
        return m_row_count;
    }
    inline int get_col_count(void) const
    {
        return m_col_count;
    }
    inline float get_cell_width(void) const
    {
        return m_cell_width;
    }
    inline float get_cell_height(void) const
    {
        return m_cell_height;
    }
    inline void set_render_grid(bool render_grid)
    {
        m_render_grid = render_grid;
    }
    inline bool is_grid_rendered() const
    {
        return m_render_grid;
    }
};

#endif
