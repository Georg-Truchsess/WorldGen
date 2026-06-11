#ifndef TILE_H
#define TILE_H


#include<vector>
#include<string>
#include<SDL2/SDL.h>


struct Tile
{
std::vector<int> TileID{};
std::vector<int> TileHeight {};
std::vector<uint> WaterExposure {};
std::vector<std::string> TileType{};


};
#endif
