#include<SDL2/SDL.h>
#include<vector>
#include "Tile.h"
#include<string>
#include<random>


// used to give every tile a unique numeric ID to be used as a reference
// Tiles cannot and should not be added after initialization
void TileMap::GenerateID(uint16_t TileCount)
{
    TileID.clear();
    TileID.reserve(TileCount);
for(uint16_t i = 0; i < TileCount; i++)
{
    TileID.push_back(i);

}
}

// Generates the coordinates for each tile before they render to the screen
void TileMap::GenerateTileCoordinates( uint16_t Tiles, uint16_t NumTilesX)

{
    TilePosx.clear();
    TilePosy.clear();
    TilePosx.reserve(Tiles);
    TilePosy.reserve(Tiles);
   
    
    // Set x and y values for tile position
for(uint16_t i = 0; i < Tiles; i++)
{
if(TilePosx.size() == 0)
{
    TilePosx.push_back(counterx);
    TilePosy.push_back(countery);
}
else if(counterx >= (30 * (NumTilesX - 1)))
{
counterx = 0;
countery += 30;

TilePosx.push_back(counterx);
TilePosy.push_back(countery);


}
else
{


counterx += 30;
TilePosx.push_back(counterx);
TilePosy.push_back(countery);

}


}



}


void TileMap::GenerateHeightMap(int8_t DisplacementValueMax, int8_t DisplacementValueMin, uint16_t Iterations)
{
std::uniform_int_distribution<int8_t> rand(DisplacementValueMin, DisplacementValueMax);

uint16_t MidpointX;
uint16_t MidpointY;

FindMidpoint(2,MidpointX, MidpointY);

//Displace(TileHeight[0]);

for(uint16_t i = 0; i < Iterations; i++)
{


}


}

uint16_t TileMap::FindMidpoint(uint16_t diviser, uint16_t MidpointX, uint16_t MidpointY)
{

MidpointX = TilePosx.size() / diviser;

MidpointY = TilePosy.size() / diviser;

return MidpointX, MidpointY;


}

// Values for parameters are TileHeight
uint8_t TileMap::Displace(uint8_t Corner1, uint8_t Corner2, uint8_t Corner3, uint8_t Corner4, uint8_t DisplacementValue, uint8_t Midpoint)
{

Midpoint = ((Corner1 + Corner2 + Corner3 + Corner4)/4) + DisplacementValue;

return Midpoint;

}
