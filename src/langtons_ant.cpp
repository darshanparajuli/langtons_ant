#include "headers/langtons_ant.h"
#include <time.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

LangtonsAnt::LangtonsAnt(int width, int height)
    : m_window(nullptr), m_camera(nullptr), m_world(nullptr), m_ant(nullptr), m_running(true), m_paused(false), m_gen(0)
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
    init_random_ant_pos();
}

void LangtonsAnt::init_random_ant_pos()
{
    // int rx = rand() % (m_world->get_col_count() - 5) - (m_world->get_col_count() - 5) / 2;
    // int ry = rand() % (m_world->get_row_count() - 5) - (m_world->get_row_count() - 5) / 2;
    // m_ant->set_x(m_world->get_cell_width() * rx);
    // m_ant->set_y(m_world->get_cell_height() * ry);
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
                        // m_paused = false;
                    }
                    break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                    {
                        // m_paused = true;
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
            case SDLK_r:
            {
                reset();
            }
            break;
            case SDLK_LEFT:
            {
                m_camera->move_left();
            }
            break;
            case SDLK_UP:
            {
                if (!m_paused)
                {
                    m_ant->set_speed(m_ant->get_speed() + 0.05f);
                }
            }
            break;
            case SDLK_DOWN:
            {
                if (!m_paused)
                {
                    m_ant->set_speed(m_ant->get_speed() - 0.05f);
                    if (m_ant->get_speed() < 0.0f)
                    {
                        m_ant->set_speed(0.0f);
                    }
                }
            }
            break;
            case SDLK_g:
            {
                m_world->set_render_grid(!m_world->is_grid_rendered());
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

        if (r >= 0 && r < m_world->get_row_count() && c >= 0 && c < m_world->get_col_count())
        {
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

            ++m_gen;
            char buf[128];
            sprintf(buf, "Langton's Ant  -  Gen: %d  -  FPS: %d", m_gen, m_window->get_fps());
            m_window->set_title(buf);
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
    m_gen = 0;
    m_world->reset();
    m_ant->reset();
    init_random_ant_pos();
}
