#include<SDL2/SDL.h>
#include<vector>
#include "Tile.h"
#include<string>


struct Tile
{
    int Width;
    int Height;
std::vector<uint8_t> TileID {};
std::vector<uint8_t> TileHeight {};
std::vector<uint8_t> WaterExposure {};
std::vector<std::string> TileType{};



};