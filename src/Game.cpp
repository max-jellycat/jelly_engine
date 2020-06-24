#include <iostream>
#include "Logger.h"
#include "Game.h"

Logger logger;
float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 1.0f;
float projectileVelY = 1.0f;

Game::Game()
    : m_running(false) {}

Game::~Game() {}

bool Game::Running() const { return m_running; }

void Game::Init(int width, int height)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logger.SetLevel(Logger::LevelError);
        logger.Error("Error initializing SDL subsystems!");
        return;
    }
    logger.SetLevel(Logger::LevelTrace);
    logger.Trace("SDL subsystems initialized!...");

    m_window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
    if (!m_window)
    {
        logger.SetLevel(Logger::LevelError);
        logger.Error("Error creating SDL window!");
        return;
    }
    logger.SetLevel(Logger::LevelTrace);
    logger.Trace("SDL window created!...");

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (!m_renderer)
    {
        logger.SetLevel(Logger::LevelError);
        logger.Error("Error creating SDL renderer!");
        return;
    }
    logger.SetLevel(Logger::LevelTrace);
    logger.Trace("SDL renderer created!...");

    m_running = true;
    logger.Trace("Game is running...");
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        m_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            m_running = false;
        break;
    default:
        break;
    }
}

void Game::Update()
{
    projectilePosX += projectileVelX;
    projectilePosY += projectileVelY;
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 35, 35, 35, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 239, 239, 239, 255);
    SDL_Rect projectile{
        (int)projectilePosX,
        (int)projectilePosY,
        10,
        10};
    SDL_RenderFillRect(m_renderer, &projectile);
    SDL_RenderPresent(m_renderer);
}

void Game::Clean()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}