
#pragma once

#include<random>
#include<vector>
#include<string>
#include<SDL2/SDL.h>

// struct used to store data for individual tiles
struct TileMap
{
    SDL_Rect Tile;
    
std::vector<uint16_t> TileID{};
std::vector<uint16_t> TilePosx{};
std::vector<uint16_t> TilePosy{};
std::vector<uint8_t> TileHeight {};
std::vector<uint8_t> WaterExposure {};
std::vector<std::string> TileType{};
int Width;
int Height;
uint16_t counterx = 0;
uint16_t countery = 0;

void GenerateID(uint16_t TileCount);


void GenerateTileCoordinates( uint16_t Tiles, uint16_t NumTilesX);

void GenerateHeightMap(int8_t DisplacementValueMax, int8_t DisplacementValueMin);

};

