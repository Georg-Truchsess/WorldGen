
#pragma once

#include<vector>
#include<string>
#include<SDL2/SDL.h>

// struct used to store data for individual tiles
struct TileMap
{
    SDL_Rect Tile;
    int Width;
    int Height;
std::vector<uint16_t> TileID{};
std::vector<uint8_t> TilePosx{};
std::vector<uint8_t> TilePosy{};
std::vector<uint8_t> TileHeight {};
std::vector<uint8_t> WaterExposure {};
std::vector<std::string> TileType{};

void GenerateID(uint16_t Tiles);


void TileMap::GenerateTiles(SDL_Rect rect, uint16_t Tiles, SDL_Texture* AsciiTab, SDL_Renderer* rend, uint16_t NumTilesX, uint16_t NumTileY);


};

