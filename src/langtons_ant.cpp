#include "headers/langtons_ant.h"
#include <time.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

LangtonsAnt::LangtonsAnt(int width, int height)
    : m_window(nullptr), m_camera(nullptr), m_world(nullptr), m_ant(nullptr), m_running(true), m_paused(false)
{
    m_window = new GameWindow("Langton's Ant", width, height);
    if (!m_window->init())
    {
        std::cerr << "Failed to init GameWindow" << std::endl;
        m_running = false;
    }

    m_camera = new Camera();
    m_world = new World(m_camera, 50, 50);
    m_ant = new Ant(m_camera, m_world->get_cell_width(), m_world->get_cell_height());
    init();
}

LangtonsAnt::~LangtonsAnt()
{
    if (m_window)
    {
        delete m_window;
    }
    delete m_camera;
    delete m_world;
    delete m_ant;
}

void LangtonsAnt::init()
{
    std::srand(time(NULL));
    m_world->init();
    m_ant->init();
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
        render();
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
            case SDLK_UP:
            {
                m_ant->set_speed(m_ant->get_speed() + 0.01f);
            }
            break;
            case SDLK_DOWN:
            {
                m_ant->set_speed(m_ant->get_speed() - 0.01f);
                if (m_ant->get_speed() < 0.0f)
                {
                    m_ant->set_speed(0.0f);
                }
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
    m_world->update(delta);
    m_ant->update(delta);

    if (m_ant->reached_target())
    {
        int r = get_world_row_index(m_ant->get_y());
        int c = get_world_col_index(m_ant->get_x());
        int value = m_world->get_value(r, c);
        if (value == World::EMPTY)
        {
            m_world->set_value(r, c, World::NON_EMPTY);
            m_ant->turn_left();
        }
        else
        {
            m_world->set_value(r, c, World::EMPTY);
            m_ant->turn_right();
        }
    }
}

void LangtonsAnt::render()
{
    m_world->render();
    m_ant->render();
}

void LangtonsAnt::reset()
{
}
