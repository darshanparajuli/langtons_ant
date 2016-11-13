#ifndef GAME_H_
#define GAME_H_

#include <glm/glm.hpp>
#include "ant.h"
#include "camera.h"
#include "game_window.h"
#include "world.h"

class LangtonsAnt
{
private:
    GameWindow *m_window;
    Camera *m_camera;
    World *m_world;
    Ant *m_ant;

    bool m_running;
    bool m_paused;

public:
    LangtonsAnt(int width, int height);
    ~LangtonsAnt(void);
    void run(void);

private:
    void init();
    void handle_input(const SDL_Event &event);
    void update(float delta);
    void render(void);
    void reset(void);
    inline int get_world_row_index(float y) const
    {
        return (int)(y * m_world->get_row_count() * 0.5f + m_world->get_row_count() / 2);
    }
    inline int get_world_col_index(float x) const
    {
        return (int)(x * m_world->get_col_count() * 0.5f + m_world->get_col_count() / 2);
    }
};

#endif
