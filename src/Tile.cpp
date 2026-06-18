#include<SDL2/SDL.h>
#include<vector>
#include "Tile.h"
#include<string>



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

// Generates the actual tilemap and renders it to the screen
void TileMap::GenerateTileCoordinates( uint16_t Tiles, uint16_t NumTilesX, uint16_t NumTilesY)
{
    TilePosx.clear();
    TilePosy.clear();
    TilePosx.reserve(Tiles);
    TilePosy.reserve(Tiles);
   
    
    // Set x and y values for tile position
for(uint16_t i = 0; i < Tiles; i++)
{

if(counterx >= (30 * NumTilesX))
{
counterx = 0;
countery += 30;
TilePosy.push_back(countery);
}
else
{


counterx += 30;
TilePosx.push_back(counterx);


}

//if(countery < (30 * NumTilesY)){
// countery += 30;
//TilePosy.push_back(countery);
//}
}



}




