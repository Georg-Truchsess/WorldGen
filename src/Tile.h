
#pragma once

#include<random>
#include<vector>
#include<iostream>
#include<SDL2/SDL.h>

// struct used to store data for individual tiles
struct TileMap
{

std::vector<std::string> TileType{};
SDL_Rect Tile;
int Width;
int Height;
uint16_t counterx = 0;
uint16_t countery = 0;
std::vector<uint16_t> TileID{};
std::vector<uint16_t> TilePosx{};
std::vector<uint16_t> TilePosy{};
std::vector<uint8_t> TileHeight {};
std::vector<uint8_t> WaterExposure {};



void GenerateID(uint16_t TileCount);


void GenerateTileCoordinates( uint16_t Tiles, uint16_t NumTilesX);

void GenerateHeightMap(int8_t DisplacementValueMax, int8_t DisplacementValueMin, uint16_t Iterations, uint16_t NumTilesX, std::mt19937 Gen);

uint16_t FindMidpoint(uint16_t diviser, uint16_t MidpointX, uint16_t MidpointY);

uint8_t Displace(uint8_t Corner1, uint8_t Corner2, uint8_t Corner3, uint8_t Corner4, uint8_t DisplacementValue, uint8_t Midpoint);

void Smooth(uint16_t Midpoint, uint16_t TopLeft, uint16_t TopRight, uint16_t BottomLeft, uint16_t BottomRight, uint16_t NumTilesX);

uint16_t TileMap::DetermineDistance(uint16_t Midpoint, uint16_t CurrentTile, uint16_t distance, uint16_t TopLeft, uint16_t TopRight, uint16_t BottomLeft, uint16_t BottomRight);
};

