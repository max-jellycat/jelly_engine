#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "EntityManager.h"
#include "Entity.h"
#include "Component.h"

class Game
{
private:
    bool running;
    int ticksLastFrame;
    SDL_Window *window;

public:
    static SDL_Renderer *renderer;
    Game();
    ~Game();
    bool Running() const;
    void Init(int width, int height);
    void LoadLevel(int levelNumber);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
};