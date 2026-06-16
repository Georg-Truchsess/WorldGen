#include<SDL2/SDL.h>
#include<vector>
#include "Tile.h"
#include<string>



// used to give every tile a unique numeric ID to be used as a reference
// Tiles cannot and should not be added after initialization
// Only call this function once during initialization
void TileMap::GenerateID(uint16_t Tiles)
{
    TileID.reserve(Tiles);
for(uint16_t i = 0; i < Tiles; i++)
{
    TileID.push_back(i);

}
}

// Generates the actual tilemap and renders it to the screen
// NumTilesX equals the number of tiles on the x-axis
// NumTilesY equals number of tiles on the y-axis
void TileMap::GenerateTiles(SDL_Rect rect, uint16_t Tiles, SDL_Texture* AsciiTab, SDL_Renderer* rend, uint16_t NumTilesX, uint16_t NumTilesY)
{
    TilePosx.reserve(Tiles);
    TilePosy.reserve(Tiles);
    uint16_t counter = 0;
    
    // Set x value for tile position
for(uint16_t i = 0; i < Tiles; i++)
{

if(counter < (30 * NumTilesX))
{
counter += 30;
TilePosx.push_back(counter);
}
else
{
counter = 0;
}

}

// clear counter
counter = 0;
// Set y value for tile position
for(uint16_t i =0; i < Tiles; i++)
{
    if(counter < (30 * NumTilesY))
    {
        counter += 30;
        TilePosx.push_back(counter);
    }
    else
    {
counter = 0;
    }
}

}




