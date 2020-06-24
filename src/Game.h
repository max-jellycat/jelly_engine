#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game
{
private:
    bool m_running;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

public:
    Game();
    ~Game();
    bool Running() const;
    void Init(int width, int height);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
};