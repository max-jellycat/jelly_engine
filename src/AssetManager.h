#pragma once

#include <map>
#include <string>
#include "EntityManager.h"
#include "TextureManager.h"

class AssetManager {
private:
    EntityManager *manager;
    std::map<std::string, SDL_Texture*> textures;

public:
    explicit AssetManager(EntityManager *manager);
    ~AssetManager();
    void ClearData();
    void AddTexture(std::string textureId, const char* filePath);
    SDL_Texture *GetTexture(const std::string& textureId);
};
