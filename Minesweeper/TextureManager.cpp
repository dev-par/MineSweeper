//
// Created by Devan Parekh on 4/17/24.
//
#include <map>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

map<string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::getTexture(string textureName) {
    auto res = textures.find(textureName);
    if (res == textures.end()) {
        sf::Texture newTexture;
        newTexture.loadFromFile("files/images/" + textureName + ".png");
        textures[textureName] = newTexture;
        return textures[textureName];
    }
    else {
        return res->second;
    }
}


