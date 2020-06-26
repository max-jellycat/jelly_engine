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
        : m_isRunning(false) {}

Game::~Game() = default;

bool Game::IsRunning() const { return this->m_isRunning; }

void Game::Init(int width, int height) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logger.SetLevel(Logger::LevelError);
        logger.Error("Error initializing SDL subsystems!");
        return;
    }
    logger.SetLevel(Logger::LevelTrace);
    logger.Trace("SDL subsystems initialized!...");

    m_window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                SDL_WINDOW_BORDERLESS);
    if (!m_window) {
        logger.SetLevel(Logger::LevelError);
        logger.Error("Error creating SDL m_window!");
        return;
    }
    logger.SetLevel(Logger::LevelTrace);
    logger.Trace("SDL m_window created!...");

    Game::renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (!Game::renderer) {
        logger.SetLevel(Logger::LevelError);
        logger.Error("Error creating SDL renderer!");
        return;
    }
    logger.SetLevel(Logger::LevelTrace);
    logger.Trace("SDL renderer created!...");

    LoadLevel(0);

    m_isRunning = true;
    logger.Trace("Game is running...");
}

void Game::LoadLevel(int levelNumber) {
    // Start including new assets to the asset m_manager
    assetManager->AddTexture("Tank", "/Users/max/dev/jelly_engine/assets/images/sprites/tank-big-right.png");
    assetManager->AddTexture("Chopper", "/Users/max/dev/jelly_engine/assets/images/sprites/chopper-spritesheet.png");
    assetManager->AddTexture("Radar", "/Users/max/dev/jelly_engine/assets/images/sprites/radar.png");

    // Start including m_entities to entity m_manager
    // And add m_components to them
    Entity &player(entityManager.AddEntity("Player"));
    player.AddComponent<Transform>(0, 0, 0, 0, 32, 32, 1);
    player.AddComponent<Sprite>("Chopper", true, false);
    auto &playerAnimator = player.AddComponent<Animator>();

    Animation downAnimation(0, 2, 90);
    Animation rightAnimation(1, 2, 90);
    Animation leftAnimation(2, 2, 90);
    Animation upAnimation(3, 2, 90);

    playerAnimator.AddAnimation("DownAnimation", downAnimation);
    playerAnimator.AddAnimation("RightAnimation", rightAnimation);
    playerAnimator.AddAnimation("LeftAnimation", leftAnimation);
    playerAnimator.AddAnimation("UpAnimation", upAnimation);

    playerAnimator.Play("DownAnimation");

    Entity &tank(entityManager.AddEntity("Tank"));
    tank.AddComponent<Transform>(30, 30, 0, 0, 32, 32, 1);
    tank.AddComponent<Sprite>("Tank");

    Entity &radar(entityManager.AddEntity("Radar"));
    radar.AddComponent<Transform>(720, 15, 0, 0, 64, 64, 1);
    radar.AddComponent<Sprite>("Radar", true, true);
    Animation radarSeek(0, 8, 150);
    radar.AddComponent<Animator>("RadarSeek", radarSeek);

    entityManager.ListEntities();
}

void Game::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            m_isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                m_isRunning = false;
            break;
        default:
            break;
    }
}

void Game::Update() {
    // Wait until frame target time has ellapsed
    unsigned int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - m_ticksLastFrame);
    if (timeToWait > 0 && timeToWait < FRAME_TARGET_TIME)
        SDL_Delay(timeToWait);

    // Delta time is the difference in ticks form last frame converted to seconds
    float deltaTime = (float) (SDL_GetTicks() - m_ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Set the new ticks for the current frame to be used in the next pass
    m_ticksLastFrame = SDL_GetTicks();

    entityManager.Update(deltaTime);
}

void Game::Render() const {
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);

    if (entityManager.HasNoEntities())
        return;

    entityManager.Render();

    SDL_RenderPresent(Game::renderer);
}

void Game::Clean() {
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}