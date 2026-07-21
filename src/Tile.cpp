#include<SDL2/SDL.h>
#include<vector>
#include "Tile.h"
#include<iostream>
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

void TileMap::GenerateHeightMap(int8_t DisplacementValueMax, int8_t DisplacementValueMin, uint16_t Iterations, uint16_t NumTilesX, std::mt19937 Gen)
{
    float scale = 1;
std::uniform_int_distribution<int8_t> rand(DisplacementValueMin, DisplacementValueMax);

uint16_t Index;
// Used for initial iteration
int8_t InitialRoughness = rand(Gen);

uint16_t TopLeft = 0;
uint16_t TopRight = std::ceil(NumTilesX/2);
uint16_t BottomLeft = (TileID.size()/2) - (std::ceil((NumTilesX/2)) - 1);
uint16_t BottomRight = TileID.size()/2;
// Used for remaining iterations
int8_t Roughness;

TileHeight.reserve(TileID.size());

for(uint16_t i = 0; i < TileID.size(); i++)
{
    TileHeight.push_back(0);

}

TileHeight[TileID.size()/2] = Displace(TileHeight[0], TileHeight[NumTilesX-1], TileHeight[NumTilesX * (NumTilesX-1) + 1], TileHeight[TileID.size()-1], InitialRoughness ,TileHeight[TileID.size()/2]);
//Smooth(TileID.size()/2, 0, NumTilesX-1, NumTilesX * (NumTilesX-1) + 1, TileID.size());
for(uint16_t i = 0; i < 4; i++)
{
Roughness = rand(Gen);
switch (i)
{
    case 0: TopLeft = 0; TopRight = NumTilesX/2; BottomLeft = (TileID.size()/2) - ((NumTilesX/2) - 1); BottomRight = TileID.size()/2;
    break;
    case 1: TopLeft = NumTilesX/2;  TopRight = NumTilesX-1; BottomLeft = TileID.size()/2; BottomRight = (TileID.size()/2) +((NumTilesX/2) -1);
    break;
    case 2: TopLeft = (TileID.size()/2) - ((NumTilesX/2) - 1); TopRight = TileID.size()-1; BottomLeft = NumTilesX * (NumTilesX-1) + 1; BottomRight = (TileID.size()-1) - (NumTilesX/2);
    break;
    case 3: TopLeft = TileID.size()/2; TopRight = (TileID.size()/2) + (NumTilesX/2); BottomLeft = (TileID.size()-1) - (NumTilesX/2); BottomRight = TileID.size()-1;
    break;
}
    
    TileHeight[Index] = Displace( TileHeight[TopLeft],TileHeight[TopRight],TileHeight[BottomLeft],TileHeight[BottomLeft], Roughness, TileHeight[Index]);
    //Smooth(TileHeight[Index],TopLeft, TopRight, BottomLeft, BottomRight);
    for(uint16_t i = 0; i < Iterations; i++)
    {
       scale = (scale/2);
        Roughness = rand(Gen) / scale;

    }
}
}

uint16_t TileMap::FindMidpoint(uint16_t TopLeft, uint16_t BottomRight, uint16_t Midpoint)
{

    Midpoint = BottomRight-TopLeft;

return Midpoint;

}

// Values for parameters are TileHeight. Corners go in order of top left, top right, bottom left, bottom right
uint8_t TileMap::Displace(uint8_t Corner1, uint8_t Corner2, uint8_t Corner3, uint8_t Corner4, uint8_t DisplacementValue, uint8_t Midpoint)

{

Midpoint = ((Corner1 + Corner2 + Corner3 + Corner4)/4) + DisplacementValue;

return Midpoint;

}

// Smooths the height of other tiles around the midpoint after being displaced
void TileMap::Smooth(uint16_t Midpoint, uint16_t TopLeft, uint16_t TopRight, uint16_t BottomLeft, uint16_t BottomRight)
{
    uint16_t range = BottomRight-TopLeft;
    uint16_t CurrentTile = TopLeft;
    double distance;
    uint8_t scale = 1;
    for(uint16_t i = 0; i < range; i++)
    {
        
        
        
        distance =  (std::sqrt( (( TilePosx[CurrentTile]- TilePosx[Midpoint]) * ( TilePosx[CurrentTile]- TilePosx[Midpoint])) + ( (TilePosy[Midpoint] - TilePosy[CurrentTile] ) * (TilePosy[Midpoint] - TilePosy[CurrentTile] ) ) )/30);
        scale = static_cast<int16_t>(distance)/2;
        
            if(scale > 0)
            {
            TileHeight[CurrentTile] = TileHeight[CurrentTile] + (TileHeight[Midpoint]/scale);
            }
            else
            {
                scale = 1;
                TileHeight[CurrentTile] = TileHeight[CurrentTile] + (TileHeight[Midpoint]/scale);
            }

        CurrentTile++;
        
    }   

    
}

void TileMap::DrawMap(SDL_Texture* ASCII, SDL_Renderer* render, SDL_Rect* target)
    {



    }
    
void TileMap::DetermineBiome(uint16_t Tile)
    {

    }
/*
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 2, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,1 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0 ,0 ,0
*/
