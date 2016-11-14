#ifndef ANT_H_
#define ANT_H_

#include "entity.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "utils.h"
#include "world.h"

class Ant : public Entity
{
private:
    enum Direction
    {
        EAST,
        WEST,
        NORTH,
        SOUTH
    };

    Mesh *m_mesh;
    Shader *m_shader;
    Texture *m_texture;

    float m_width;
    float m_height;
    float m_x;
    float m_y;
    float m_target_x;
    float m_target_y;
    float m_speed;
    Direction m_dir;

public:
    Ant(Camera *camera, float w, float h);
    virtual ~Ant(void);
    virtual void init(void);
    virtual void update(float delta_time);
    virtual void render(void);
    void reset(void);
    inline void set_target_x(float x)
    {
        m_target_x = x;
    }
    inline void set_target_y(float y)
    {
        m_target_y = y;
    }
    inline float get_x() const
    {
        return m_x;
    }
    inline float get_y() const
    {
        return m_y;
    }
    void turn_right(void);
    void turn_left(void);
    inline bool reached_target() const
    {
        return utils::float_eq(m_x, m_target_x) && utils::float_eq(m_y, m_target_y);
    }
    inline void set_speed(float speed)
    {
        m_speed = speed;
    }
    inline float get_speed() const
    {
        return m_speed;
    }
};

#endif
