#include <glm/glm.hpp>
#include "Constants.h"
#include "Logger.h"
#include "Game.h"
#include "Components/TransformComponent.h"

Logger logger;

EntityManager entityManager;
SDL_Renderer *Game::renderer;

Game::Game()
    : running(false) {}

Game::~Game() {}

bool Game::Running() const { return this->running; }

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

    this->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
    if (!this->window)
    {
        logger.SetLevel(Logger::LevelError);
        logger.Error("Error creating SDL window!");
        return;
    }
    logger.SetLevel(Logger::LevelTrace);
    logger.Trace("SDL window created!...");

    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    if (!this->renderer)
    {
        logger.SetLevel(Logger::LevelError);
        logger.Error("Error creating SDL renderer!");
        return;
    }
    logger.SetLevel(Logger::LevelTrace);
    logger.Trace("SDL renderer created!...");

    this->LoadLevel(0);

    this->running = true;
    logger.Trace("Game is running...");
}

void Game::LoadLevel(int levelNumber)
{
    Entity &player(entityManager.AddEntity("Player"));
    player.AddComponent<TransformComponent>(0, 0, 50, 50, 24, 24, 1, 1);
    Entity &enemy(entityManager.AddEntity("Enemy"));
    enemy.AddComponent<TransformComponent>(800, 0, -50, 50, 24, 24, 1, 1);
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        this->running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            this->running = false;
        break;
    default:
        break;
    }
}

void Game::Update()
{
    // Wait until frame target time has ellapsed
    unsigned int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - this->ticksLastFrame);
    if (timeToWait > 0 && timeToWait < FRAME_TARGET_TIME)
        SDL_Delay(timeToWait);

    // Delta time is the difference in ticks form last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - this->ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Set the new ticks for the current frame to be used in the next pass
    this->ticksLastFrame = SDL_GetTicks();

    entityManager.Update(deltaTime);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(this->renderer, 35, 35, 35, 255);
    SDL_RenderClear(this->renderer);

    if (entityManager.HasNoEntities())
        return;

    entityManager.Render();

    SDL_RenderPresent(this->renderer);
}

void Game::Clean()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}