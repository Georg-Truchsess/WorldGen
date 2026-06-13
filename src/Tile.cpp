#include<SDL2/SDL.h>
#include<vector>
#include "Tile.h"
#include<string>




void TileMap::GenerateID(int Tiles)
{
    TileID.reserve(Tiles);
for(int i = 0; i <= Tiles; i++)
{
    TileID.push_back(i);

}


}


