
#pragma once

#include<random>
#include<vector>
#include<iostream>
#include<SDL2/SDL.h>
#include"FNV1A.h"


// struct used to store data for individual tiles
struct TileMap
{


std::vector<std::string> TileType{};
std::vector<uint64_t> TileHash{};
std::vector<uint64_t> WindHash{};
// Biomes
//std::string TileTypes [20] = {"Plain","Ocean","Mountain","Wetland","River","Desert","Hills"};
static constexpr std::string_view PlainTile = "Plain";
static constexpr uint64_t Plain = FNV1A::hash64(PlainTile);

static constexpr std::string_view RiverTile = "River";
static constexpr uint64_t River = FNV1A::hash64(RiverTile);

static constexpr std::string_view OceanTile = "Ocean";
static constexpr uint64_t Ocean = FNV1A::hash64(OceanTile);

static constexpr std::string_view MountainTile = "Mountain";
static constexpr uint64_t Mountain = FNV1A::hash64(MountainTile);

static constexpr std::string_view WetlandTile = "Wetland";
static constexpr uint64_t Wetland =  FNV1A::hash64(WetlandTile);

static constexpr std::string_view SavannaTile = "Savanna";
static constexpr uint64_t Savanna = FNV1A::hash64(SavannaTile);

static constexpr std::string_view DesertTile = "Desert";
static constexpr uint64_t Desert = FNV1A::hash64(DesertTile);
SDL_Rect Tile;
int Width;
int Height;
int AtlasArrayx [20] = {};
int AtlasArrayy [20] = {};
std::vector <uint32_t> TilePopulation{};
uint16_t counterx = 0;
uint16_t countery = 0;
std::vector<uint16_t> TileID{};
std::vector<uint16_t> TilePosx{};
std::vector<uint16_t> TilePosy{};


std::vector<int8_t> TileHeight {};
std::vector<uint8_t> WaterExposure {};




void GenerateID(uint16_t TileCount);


void GenerateTileCoordinates( uint16_t Tiles, uint16_t NumTilesX);

void GenerateHeightMap(int8_t DisplacementValueMax, int8_t DisplacementValueMin, uint16_t Iterations, uint16_t NumTilesX, std::mt19937 Gen);

uint16_t FindMidpoint(uint16_t TopLeft, uint16_t BottomRight, uint16_t Midpoint);

uint8_t Displace(uint8_t Corner1, uint8_t Corner2, uint8_t Corner3, uint8_t Corner4, uint8_t DisplacementValue, uint8_t Midpoint);

void Smooth(uint16_t Midpoint, uint16_t TopLeft, uint16_t TopRight, uint16_t BottomLeft, uint16_t BottomRight);

void DrawMap(SDL_Texture* ASCII, SDL_Renderer* render, SDL_Rect* target);

void DetermineBiome(uint16_t Index, SDL_Rect* T);

void GenerateRivers(uint16_t CurrentTile, uint16_t NumTilesX);

void CalculateWaterExposure(uint16_t NumTilesX);

void ExposureByRiver(uint16_t NumTilesX);

void GenerateWindPattern(uint16_t MapWidth);

void EastToWest(uint16_t MapWidth, uint16_t WindPattern, uint16_t PreviousPattern);

void WestToEast(uint16_t MapWidth, uint16_t WindPattern, uint16_t NextPattern);

std::vector<uint64_t> HashRuntimeStrings(const std::vector<std::string>& TargetStrings);


};

