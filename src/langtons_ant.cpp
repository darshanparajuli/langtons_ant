#include "headers/langtons_ant.h"
#include <time.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

LangtonsAnt::LangtonsAnt(int width, int height)
    : m_window(new GameWindow("Langton's Ant", width, height)),
      m_grid(nullptr),
      m_mesh(nullptr),
      m_shader(new Shader()),
      m_running(false),
      m_paused(false)
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

    m_projection_matrix = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -1.0f, 100.0f);
    m_view_matrix =
        glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 vertices[] = {glm::vec3(-10.0f, 10.0f, 0.0f), glm::vec3(10.0f, 10.0f, 0.0f),
                            glm::vec3(10.0f, -10.0f, 0.0f), glm::vec3(-10.0f, -10.0f, 0.0f)};
    int indices[] = {0, 1, 3, 1, 3, 2};
    glm::vec2 tex_coords[] = {
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f),
    };
    m_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]),
                      tex_coords, sizeof(tex_coords) / sizeof(tex_coords[0]));
    m_shader->init("shaders/basic.vert", "shaders/basic.frag");

    m_grid = new Grid(100, 100);

    std::srand(time(NULL));
}

LangtonsAnt::~LangtonsAnt()
{
    if (m_window)
    {
        delete m_window;
    }
    delete m_grid;
    delete m_mesh;
    delete m_shader;
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
    m_grid->draw();

    m_mesh->bind();

    m_shader->bind();
    m_shader->set_uniform_mat4("view", m_view_matrix);
    m_shader->set_uniform_mat4("projection", m_projection_matrix);

    glm::mat4 v = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f));
    m_shader->set_uniform_mat4("model", v);

    m_mesh->draw();

    m_shader->unbind();
    m_mesh->unbind();
}

void LangtonsAnt::reset()
{
}
