#include<SDL2/SDL.h>
#include<vector>
#include "Tile.h"
#include "Utils.h"
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
uint16_t TLH;
uint16_t TRH;
uint16_t BLH;
uint16_t BRH;
uint16_t Midpoint;
// Used for initial iteration
int8_t InitialRoughness = rand(Gen);

uint16_t TopLeft = 0;
uint16_t TopRight = NumTilesX/2;
uint16_t BottomLeft = (TileID.size()/2) - ((NumTilesX/2) - 1);
uint16_t BottomRight = TileID.size()/2;
// Used for remaining iterations
int8_t Roughness;

TileHeight.reserve(TileID.size());

for(uint16_t i = 0; i < TileID.size(); i++)
{
    TileHeight.push_back(0);

}

TileHeight[TileID.size()/2] = Displace(TileHeight[0], TileHeight[NumTilesX-1], TileHeight[NumTilesX * (NumTilesX-1) + 1], TileHeight[TileID.size()-1], InitialRoughness ,TileHeight[TileID.size()/2]);
Smooth(TileID.size()/2, 0, NumTilesX-1, NumTilesX * (NumTilesX-1) + 1, TileID.size());
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
    Smooth(Index, TopLeft, TopRight, BottomLeft, BottomRight);
    for(uint16_t i = 0; i < Iterations; i++)
    {
       scale = (scale/2);
        Roughness = static_cast<int8_t>(rand(Gen) / scale);
    
        TopLeft /= 2; TopRight /= 2; BottomLeft /= 2; BottomRight /= 2;
        TLH = TopLeft; TRH = TopRight; BLH = BottomLeft; BRH = BottomRight;
        FindMidpoint(TopLeft, BottomRight, Midpoint);

        TileHeight[Midpoint] = Displace(TileHeight[TopLeft], TileHeight[TopRight], TileHeight[BottomLeft], TileHeight[BottomRight], Roughness, TileHeight[Midpoint]);
        Smooth(Midpoint, TopLeft, TopRight, BottomLeft, BottomRight);
        TopLeft += (TopRight-TopLeft); TopRight += (TopRight-TopLeft); BottomLeft += (BottomRight-BottomLeft); BottomRight += (BottomRight-BottomLeft);

        FindMidpoint(TopLeft, BottomRight, Midpoint);

        TileHeight[Midpoint] = Displace(TileHeight[TopLeft], TileHeight[TopRight], TileHeight[BottomLeft], TileHeight[BottomRight], Roughness,TileHeight[Midpoint] );
        TopLeft = TLH; TopRight = TRH; BottomLeft = BLH; BottomRight = BRH;

       // TopLeft *= (BottomLeft/TopLeft); TopRight *= (BottomRight/TopRight);

        //FindMidpoint(TopLeft, BottomRight, Midpoint);

        //TileHeight[Midpoint] = Displace(TileHeight[TopLeft], TileHeight[TopRight], TileHeight[BottomLeft], TileHeight[BottomRight], Roughness,TileHeight[Midpoint] );
        //TopLeft = TLH; TopRight = TRH; BottomLeft = BLH; BottomRight = BRH;
        
    }
}
}

//used to find midpoint between two values
uint16_t TileMap::FindMidpoint(uint16_t TopLeft, uint16_t BottomRight, uint16_t Midpoint)
{



    Midpoint = (BottomRight-TopLeft)/2;

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
            

           

        for(uint16_t i = 0; i < TileID.size(); i++)
        {
            target -> x = TilePosx[i];
            target -> y = TilePosy[i];
            DetermineBiome(i, &Tile);

            SDL_RenderCopy(render, ASCII, &Tile, target);

            

        }


    }
    
void TileMap::DetermineBiome(uint16_t Index, SDL_Rect* T)
    {

        if(TileHeight[Index] >= 15 && TileType[Index] != "River")
            
        {
            T -> x = 15;

            T -> y = 6;

            T -> w = 10;

            T -> h = 15;
        }
        else if(TileType[Index] == "River")
        {
            T -> x = 25;

            T -> y = 6;

            T -> w = 10;
            
            T -> h = 15;

        }
        else
        {
            T -> x = 0;

            T -> y = 0;

            T -> w = 1;

            T -> h = 1;
        }

    }

    // Generates rivers from mountains
    void TileMap::GenerateRivers(uint16_t CurrentTile, uint16_t NumTilesX)
    {
        TileType[CurrentTile] = "River";
        bool EndOfRiver = false;

        uint16_t PreviousTile;
    
        // Conditions of if statements check to see if the next tile is lower in height than the current tile, they check if the next tile is not the previous tile, and they check to see if the next tile is an ocean tile
        while(EndOfRiver == false)
        {
            if(TileHeight[CurrentTile + 1] < TileHeight[CurrentTile] && CurrentTile + 1 < TileID.size()-1 && CurrentTile + 1 != PreviousTile && TileType[CurrentTile+1] != "Ocean")
            {
                PreviousTile = CurrentTile;
                CurrentTile += 1;

                TileType[CurrentTile] = "River";

            }
            else if(TileHeight[CurrentTile - 1] < TileHeight[CurrentTile] && CurrentTile - 1 < TileID.size()-1 && CurrentTile -1 != PreviousTile && TileType[CurrentTile-1] != "Ocean")
            {
                PreviousTile = CurrentTile;
                CurrentTile -= 1;

                TileType[CurrentTile] = "River";

            }
            else if(TileHeight[CurrentTile + NumTilesX] < TileHeight[CurrentTile] && CurrentTile + NumTilesX < TileID.size()-1 && CurrentTile + NumTilesX != PreviousTile && TileType[CurrentTile + NumTilesX] != "Ocean")
            {
                PreviousTile = CurrentTile;
                CurrentTile += NumTilesX;

                TileType[CurrentTile] = "River";

            }
            else if(TileHeight[CurrentTile + NumTilesX + 1] < TileHeight[CurrentTile] && CurrentTile + NumTilesX + 1 < TileID.size()-1 && CurrentTile + NumTilesX + 1 != PreviousTile && TileType[CurrentTile + NumTilesX + 1] != "Ocean")
            {
                PreviousTile = CurrentTile;
                CurrentTile += NumTilesX + 1;

                TileType[CurrentTile] = "River";

            }
            else if(TileHeight[CurrentTile + NumTilesX - 1] < TileHeight[CurrentTile] && CurrentTile + NumTilesX - 1 < TileID.size()-1 && CurrentTile + NumTilesX -1 != PreviousTile && TileType[CurrentTile + NumTilesX -1] != "Ocean")
            {
                PreviousTile = CurrentTile;
                CurrentTile += NumTilesX -1;

                TileType[CurrentTile] = "River";

            }
            else if(TileHeight[CurrentTile - NumTilesX] < TileHeight[CurrentTile] && CurrentTile - NumTilesX < TileID.size()-1 && CurrentTile - NumTilesX != PreviousTile && TileType[CurrentTile - NumTilesX] != "Ocean")
            {
                
                PreviousTile = CurrentTile;
                CurrentTile -= NumTilesX;

                TileType[CurrentTile] = "River";

            }
            else if(TileHeight[CurrentTile - NumTilesX + 1] < TileHeight[CurrentTile] && CurrentTile - NumTilesX + 1 < TileID.size()-1 && CurrentTile - NumTilesX + 1 != PreviousTile && TileType[CurrentTile - NumTilesX + 1] != "Ocean")
            {
                
                PreviousTile = CurrentTile;
                CurrentTile -= NumTilesX + 1;

                TileType[CurrentTile] = "River";

            }
            else if(TileHeight[CurrentTile - NumTilesX - 1] < TileHeight[CurrentTile] && CurrentTile - NumTilesX - 1 < TileID.size()-1 && CurrentTile - NumTilesX -1 != PreviousTile && TileType[CurrentTile - NumTilesX - 1] != "Ocean")
            {
                PreviousTile = CurrentTile;
                CurrentTile -= NumTilesX - 1;

                TileType[CurrentTile] = "River";

            }
            else
            {
                EndOfRiver = true;
            }

        }

    }

    void TileMap::CalculateWaterExposure(uint16_t CurrentTile, uint16_t NumTilesX)
    {

        WaterExposure.reserve(TileID.size());
        for(uint16_t i = 0; i < TileID.size(); i++)
        {
            WaterExposure.push_back(0);
        }
        ExposureByRiver(NumTilesX);
        
    }

    void TileMap::ExposureByRiver( uint16_t NumTilesX)
    {
        uint16_t RiverTile;
        uint16_t DistanceFromRiver;
        for(uint16_t i = 0; i < TileID.size(); i++)
        {

            if(TileHash[i] == River)
            {
                RiverTile = TileID[i];
                for(uint16_t i = 0; i < TileID.size()-1; i++)
                {
                    DistanceFromRiver = Distance(TilePosy[RiverTile], TilePosx[RiverTile], TilePosy[i], TilePosy[i]);
                    if(DistanceFromRiver <= 5)
                    {
                        // formula to subtract 20 from added sum every tile away from river
                    WaterExposure[i] += ((6 - DistanceFromRiver) * 20);
                    }
                }
            }





           
        }
    }

    void TileMap::HashRuntimeStrings()
    {
        TileHash.reserve(TileID.size());
        for(int i = 0; i< TileID.size(); i++)
        {
            TileHash.push_back(0);
        }

        for(const auto& item : TileHash)
        {
           TileHash[item] = FNV1A::hash64(TileType[item]);
        }

    }