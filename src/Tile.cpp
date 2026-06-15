#include<SDL2/SDL.h>
#include<vector>
#include "Tile.h"
#include<string>



// used to give every tile a unique numeric ID to be used as a reference
void TileMap::GenerateID(uint16_t Tiles)
{
    TileID.reserve(Tiles);
for(uint16_t i = 0; i <= Tiles; i++)
{
    TileID.push_back(i);

}
}

void TileMap::GenerateTiles(SDL_Rect rect, uint16_t Tiles)
{



}




