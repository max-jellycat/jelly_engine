#include "Constants.h"
#include "Logger.h"
#include "Game.h"
#include "AssetManager.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"

Logger logger;
EntityManager entityManager;
AssetManager *Game::assetManager = new AssetManager(&entityManager);
SDL_Renderer *Game::renderer;

Game::Game()
        : running(false) {}

Game::~Game() = default;

bool Game::Running() const { return this->running; }

void Game::Init(int width, int height) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logger.SetLevel(Logger::LevelError);
        logger.Error("Error initializing SDL subsystems!");
        return;
    }
    logger.SetLevel(Logger::LevelTrace);
    logger.Trace("SDL subsystems initialized!...");

    this->window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                    SDL_WINDOW_BORDERLESS);
    if (!this->window) {
        logger.SetLevel(Logger::LevelError);
        logger.Error("Error creating SDL window!");
        return;
    }
    logger.SetLevel(Logger::LevelTrace);
    logger.Trace("SDL window created!...");

    Game::renderer = SDL_CreateRenderer(this->window, -1, 0);
    if (!Game::renderer) {
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

void Game::LoadLevel(int levelNumber) {
    // Start including new assets to the asset manager
    std::string textureFilePath = "/Users/max/dev/jelly_engine/assets/images/sprites/tank-big-right.png";
    assetManager->AddTexture("Tank", textureFilePath.c_str());

    // Start including entities to entity manager
    // And add components to them
    Entity &player(entityManager.AddEntity("Tank"));
    player.AddComponent<Transform>(0, 0, 50, 50, 32, 32, 1);
    player.AddComponent<Sprite>("Tank");
}

void Game::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
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

void Game::Update() {
    // Wait until frame target time has ellapsed
    unsigned int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - this->ticksLastFrame);
    if (timeToWait > 0 && timeToWait < FRAME_TARGET_TIME)
        SDL_Delay(timeToWait);

    // Delta time is the difference in ticks form last frame converted to seconds
    float deltaTime = (float)(SDL_GetTicks() - this->ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Set the new ticks for the current frame to be used in the next pass
    this->ticksLastFrame = SDL_GetTicks();

    entityManager.Update(deltaTime);
}

void Game::Render() const {
    SDL_SetRenderDrawColor(Game::renderer, 35, 35, 35, 255);
    SDL_RenderClear(Game::renderer);

    if (entityManager.HasNoEntities())
        return;

    entityManager.Render();

    SDL_RenderPresent(Game::renderer);
}

void Game::Clean() {
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}