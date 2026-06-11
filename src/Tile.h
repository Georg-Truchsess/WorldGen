#ifndef TILE_H
#define TILE_H


#include<vector>
#include<string>
#include<SDL2/SDL.h>


struct Tile
{
std::vector<uint8_t> TileID{};
std::vector<uint8_t> TileHeight {};
std::vector<uint8_t> WaterExposure {};
std::vector<std::string> TileType{};


};
#endif
