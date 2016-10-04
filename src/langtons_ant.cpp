#include "langtons_ant.h"
#include <time.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

LangtonsAnt::LangtonsAnt(int width, int height)
    : m_window(new GameWindow("Langton's Ant", width, height)), m_running(false), m_paused(false)
{
    if (!m_window->init())
    {
        std::cerr << "Failed to init GameWindow" << std::endl;
        m_running = false;
    }
    else
    {
        m_running = true;
    }

    // m_projection_matrix =
    //     glm::ortho(m_world_size.left, m_world_size.right, m_world_size.bottom, m_world_size.top, -1.0f, 100.0f);
    // m_view_matrix =
    //     glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    std::srand(time(NULL));
}

LangtonsAnt::~LangtonsAnt()
{
    if (m_window)
    {
        delete m_window;
    }
}

void LangtonsAnt::run()
{
    SDL_Event event;
    while (m_running && m_window->is_running())
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_window->exit();
            }
            else if (event.type == SDL_WINDOWEVENT)
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        m_window->resize(event.window.data1, event.window.data2);
                    }
                    break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                    {
                        m_paused = false;
                    }
                    break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                    {
                        m_paused = true;
                    }
                    break;
                }
            }
            else
            {
                handle_input(event);
            }
        }

        update(m_window->get_delta_time());

        m_window->clear_screen();
        draw();
        m_window->update();
    }
}

void LangtonsAnt::handle_input(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_q:
            {
                m_running = false;
            }
            break;
            case SDLK_p:
            {
                m_paused = !m_paused;
            }
            break;
        }
    }
}

void LangtonsAnt::update(float delta)
{
    if (m_paused)
    {
        return;
    }
}

void LangtonsAnt::draw()
{
}

void LangtonsAnt::reset()
{
}
