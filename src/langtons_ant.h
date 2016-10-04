#ifndef GAME_H_
#define GAME_H_

#include <glm/glm.hpp>
#include "game_window.h"
#include "grid.h"

class LangtonsAnt
{
private:
    GameWindow *m_window;

    glm::mat4 m_projection_matrix;
    glm::mat4 m_view_matrix;

    bool m_running;
    bool m_paused;

public:
    LangtonsAnt(int width, int height);
    ~LangtonsAnt();
    void run(void);

private:
    void handle_input(const SDL_Event &event);
    void update(float delta);
    void draw(void);
    void reset(void);
};

#endif
