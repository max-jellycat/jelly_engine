#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "EntityManager.h"
#include "Entity.h"
#include "Component.h"
#include "AssetManager.h"

class AssetManager;

class Game {
private:
    bool m_isRunning;
    int m_ticksLastFrame{};
    SDL_Window *m_window{};

public:
    static SDL_Renderer *renderer;
    static AssetManager *assetManager;

    Game();

    ~Game();

    bool IsRunning() const;

    void Init(int width, int height);

    static void LoadLevel(int levelNumber);

    void HandleEvents();

    void Update();

    void Render() const;

    void Clean();
};