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
    bool running;
    int ticksLastFrame{};
    SDL_Window *window{};

public:
    static SDL_Renderer *renderer;
    static AssetManager *assetManager;

    Game();

    ~Game();

    bool Running() const;

    void Init(int width, int height);

    static void LoadLevel(int levelNumber);

    void HandleEvents();

    void Update();

    void Render() const;

    void Clean();
};