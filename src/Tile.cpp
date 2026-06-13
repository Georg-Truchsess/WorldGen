#include<SDL2/SDL.h>
#include<vector>
#include "Tile.h"
#include<string>




void TileMap::GenerateID(int Tiles)
{
    TileID.reserve(Tiles);
for(int i = 0; i <= Tiles; i++)
{
    if(i < Tiles - 1)
    {
    TileID.insert(TileID.begin() + i,i + 1);
    }
    else
    {
        TileID.insert(TileID.begin() + i, i);
    }

}


}


