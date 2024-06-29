//
// Created by Devan Parekh on 4/17/24.
//

#ifndef CMAKESFMLPROJECT_TEXTUREMANAGER_H
#define CMAKESFMLPROJECT_TEXTUREMANAGER_H
#include <map>
#include <SFML/Graphics.hpp>
using namespace std;

class TextureManager {
public:
    static map<string, sf::Texture> textures;
    static sf::Texture &getTexture(string textureName);
};


#endif //CMAKESFMLPROJECT_TEXTUREMANAGER_H
