
#pragma once

#include<vector>
#include<string>
#include<SDL2/SDL.h>

// struct used to store data for individual tiles
struct TileMap
{
    int Width;
    int Height;
std::vector<uint16_t> TileID{};
std::vector<uint8_t> TileHeight {};
std::vector<uint8_t> WaterExposure {};
std::vector<std::string> TileType{};

void GenerateID(int Tiles);




};

