#include "Constants.h"
#include "Game.h"

int main() {
    Game *game = new Game();
    game->Init(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->IsRunning()) {
        game->HandleEvents();
        game->Update();
        game->Render();
    }

    game->Clean();
};