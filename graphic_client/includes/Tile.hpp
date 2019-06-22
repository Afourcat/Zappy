/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef TILE_HPP_
#define TILE_HPP_

#include "Animation.hpp"
#include "Exception.hpp"
#include "SDL2/SDL.h"
#include "protocols.h"
#include <vector>

class Tile {
public:
    Tile(std::string&, SDL_Renderer*);
    ~Tile() = default;

    void setTileContent(int, int, std::vector<int>, int);

    srv_tile_content_t* getTileInfo() { return tile; }
    SDL_Surface* getSurface() { return img; }
    SDL_Texture* getTmp() { return tmp; }

    int getPosX() { return tile->x; }
    int getPosY() { return tile->y; }

    SDL_Rect getArea() { return area; }
    void setArea(SDL_Rect area);

private:
    SDL_Surface* img;
    SDL_Texture* texture;
    SDL_Texture* tmp;

    SDL_Rect area;

    srv_tile_content_t* tile;
};
#endif
