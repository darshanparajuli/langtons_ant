#ifndef GAME_WINDOW_H_
#define GAME_WINDOW_H_

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

class GameWindow
{
private:
    const char *m_title;
    int m_width, m_height;
    bool m_running;
    SDL_Window *m_window;
    SDL_GLContext m_gl_context;
    unsigned int m_prev_frame_time;
    unsigned int m_frame_count;
    unsigned int m_prev_time;
    unsigned int m_fps;
    float m_delta_time;

private:
    void handle_input(SDL_Event &event);
    bool init_opengl(void);

public:
    GameWindow(const char *m_title, int width, int height);
    ~GameWindow(void);
    bool init(void);
    void update(void);
    void resize(int width, int height);

public:
    inline bool is_running(void) const
    {
        return m_running;
    }
    inline void clear_screen(void)
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    inline float get_delta_time(void) const
    {
        return m_delta_time;
    }
    inline void exit(void)
    {
        m_running = false;
    }
    inline void set_title(const char *title)
    {
        SDL_SetWindowTitle(m_window, title);
    }
    inline int get_fps() const
    {
        return m_fps;
    }
};

#endif
