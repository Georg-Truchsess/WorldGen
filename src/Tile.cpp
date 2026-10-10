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
TileHeight.clear();

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

    
        
    }
}
int TilesAboveSeaLevel = 0;
int SeaLevel = 10;

for(int i = 0; i < TileHeight.size(); i++)
{
    if(TileHeight[i] > SeaLevel)
    {
        TilesAboveSeaLevel++;
    }
}
if(TilesAboveSeaLevel < TileHeight.size()/2)
{
    GenerateHeightMap(DisplacementValueMax, DisplacementValueMin, Iterations, NumTilesX, Gen);
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
        
        
        
        distance =  Distance(TilePosx[CurrentTile], TilePosy[CurrentTile], TilePosx[Midpoint], TilePosy[Midpoint]);
        
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
            RenderBiome(i, &Tile, ASCII);

            SDL_RenderCopy(render, ASCII, &Tile, target);

            

        }


    }
    
void TileMap::RenderBiome(uint16_t Index, SDL_Rect* T, SDL_Texture* ASCII)
    {
        /*
        if(TileHeight[Index] >= 15 && TileHash[Index] != River)
            
        {
            T -> x = 15;

            T -> y = 6;

            T -> w = 10;

            T -> h = 15;
        }
        else if(TileHash[Index] == River)
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
        */
        
          switch(TileHash[Index])
        {
            case Plain: 
            T -> x = 15; 
            T -> y = 6; 
            T -> w = 10; 
            T -> h = 15;

            SDL_SetTextureColorMod(ASCII, 0, 250, 0);
             break;

            case River: 
            T -> x = 25;
            T -> y = 6; 
            T -> w = 10;
            T -> h = 15;

            SDL_SetTextureColorMod(ASCII, 0, 0, 255);
            break;

            case Ocean:
            T -> x = 0;
            T -> y = 0; 
            T -> w = 1;
            T -> h = 1; 
            break;

            case Mountain:
            T -> x = 277;
            T -> y = 9;
            T -> w = 8;
            T -> h = 12;

            SDL_SetTextureColorMod(ASCII, 104, 104, 104);
            break;

            case TemperateRainforest:
            T -> x = 225;
            T -> y = 7;
            T -> w = 6;
            T -> h = 10;

            SDL_SetTextureColorMod(ASCII, 0, 150, 0);
            break;
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

    void TileMap::CalculateWaterExposure( uint16_t NumTilesX)
    {

        WaterExposure.reserve(TileID.size());
        for(uint16_t i = 0; i < TileID.size(); i++)
        {
            WaterExposure.push_back(0);
        }
        ExposureByRiver(NumTilesX);
        GenerateWindPattern(NumTilesX);
        
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
                    if(DistanceFromRiver <= 5 && WaterExposure[i] != 100)
                    {
                        if ( TileHash[i] != Ocean && TileHash[i] != River )
                        {
                        // formula to subtract 20 from added sum every tile away from river
                        WaterExposure[i] += ((6 - DistanceFromRiver) * 20);
                        }
                    }
                }
            }





           
        }
    }

    void TileMap::GenerateWindPattern(uint16_t MapWidth)
    {
        // One sixth of the map size
        uint16_t Tenth = TileID.size()/10;
        // Northern winds
        uint16_t NorthernPolarEasterlies = Tenth;
        uint16_t NorthernWesterlies = Tenth * 3;
        uint16_t NorthernTradeWinds = Tenth * 5;
        // Southern winds
        uint16_t SouthernTradeWinds = Tenth * 7;
        uint16_t SouthernWesterlies = Tenth * 9;
        uint16_t SouthernPolarEasterlies = TileID.size()-1;

        
        std::cout << NorthernPolarEasterlies<< std::endl;
        for( uint16_t i = 0; i < 6; i++)
        {
        
            switch(i)
            {
                
                case 1: 
                EastToWest(MapWidth, NorthernPolarEasterlies, 0);
                break;

                case 2:
                WestToEast(MapWidth, NorthernWesterlies, NorthernTradeWinds);
                break;

                case 3: 
                EastToWest(MapWidth, NorthernTradeWinds, NorthernWesterlies);
                break;

                case 4: 
                EastToWest(MapWidth, SouthernTradeWinds, NorthernTradeWinds);
                break; 

                case 5:
                WestToEast(MapWidth, SouthernWesterlies, SouthernPolarEasterlies);
                break;

                case 6:
                EastToWest(MapWidth, SouthernPolarEasterlies, SouthernWesterlies);
                break;
            }
            
        }

    }

    // Simulates a wind pattern going from East to West
    // Stops when entering tile under another pattern
    void TileMap::EastToWest(uint16_t MapWidth, uint16_t WindPattern, uint16_t PreviousPattern)
    {
        uint16_t WindMoistureValue = 0;

        uint16_t WindwardSide;

        uint16_t PickupOverOcean = 10;
        uint16_t LeewardSide;
        for(int i = WindPattern; i > PreviousPattern; i--)
                {
                    WindwardSide = i+1;
                    if(i-1 > -1)
                    {
                    LeewardSide = i-1;
                    }
                    else{
                        LeewardSide = i;
                    }
                    // Wind picks up moisture over oceans
                    
                    if(TileHash[i] == Ocean)
                    {
                        WindMoistureValue += PickupOverOcean;
                    }
                    else
                    {
                        // Wind deposits moisture onto land
                        WaterExposure[i] += PickupOverOcean;
                        WindMoistureValue -= PickupOverOcean;
                    }
                        
                    // Rain shadow is created if mountain is hit by wind
                    //Windward side of mountain has all moisture deposited
                    
                    if(TileHeight[i] >= TileHeight[LeewardSide])
                    {
                        WaterExposure[WindwardSide] += WindMoistureValue;
                        WindMoistureValue = 0;
                    }
                }

    }
    // SImulates wind going from West to East
    void TileMap::WestToEast(uint16_t MapWidth, uint16_t WindPattern, uint16_t NextPattern)
    {
        uint16_t WindMoistureValue = 0;

        uint16_t WindwardSide;

        uint16_t PickupOverOcean = 10;
        uint16_t LeewardSide;
        for(int i = WindPattern; i < NextPattern; i++)
                {
                    WindwardSide = i+1;
                    if(i-1 > -1)
                    {
                    LeewardSide = i-1;
                    }
                    else{
                        LeewardSide = i;
                    }
                    // Wind picks up moisture over oceans
                    
                    if(TileHash[i] == Ocean)
                    {
                        WindMoistureValue += PickupOverOcean;
                    }
                    else
                    {
                        // Wind deposits moisture onto land
                        WaterExposure[i] += PickupOverOcean;
                        WindMoistureValue -= PickupOverOcean;
                    }
                        
                    // Rain shadow is created if mountain is hit by wind
                    //Windward side of mountain has all moisture deposited
                    
                    if(TileHeight[i] >= TileHeight[LeewardSide])
                    {
                        WaterExposure[WindwardSide] += WindMoistureValue;
                        WindMoistureValue = 0;
                    }
                }

    }

    std::vector<uint64_t> TileMap::HashRuntimeStrings(const std::vector<std::string>& TargetStrings)
    {
        std::vector<uint64_t> hashes;

        hashes.reserve(TargetStrings.size());
        for(const auto& item : TargetStrings)
        {
            hashes.push_back(FNV1A::hash64(item));
        }

        return hashes;

    }

    void TileMap::DetermineTemperature(uint16_t MapWidth)
    {
        uint16_t BaseTemp = 85;
        uint16_t Distance;
        Temperature.reserve(TileID.size());
        for(int i=0; i < TileID.size()-1; i++)
        {
            Temperature.push_back(0);
        }

        //Temperature by distance from equator
        for(int i = 0; i < Temperature.size()-1; i ++)
        {
            
            Distance = DistanceFromEquator(i,MapWidth);
            Temperature[i] += BaseTemp - (Distance/2);
            

        }

        //Temperature by altitude
        for(int i = 0; i < Temperature.size()-1; i++)
        {
            if(TileHash[i] != Ocean && TileHash[i] != River)
            Temperature[i] -= 3 * (TileHeight[i]/2);
           // std::cout << 3 * (TileHeight[i]/10) << std::endl;

        }

    }

    uint16_t TileMap::DistanceFromEquator(uint16_t CurrentTile, uint16_t MapWidth)
    {

        uint16_t DistanceFromEquator;

        uint16_t EquatorTile = TileID.size()/2;

        if(std::abs(EquatorTile - CurrentTile) <= (MapWidth/2))
        {
            DistanceFromEquator = 0;
        }
        else
        {
            DistanceFromEquator = Distance(TilePosx[EquatorTile], TilePosy[EquatorTile], TilePosx[CurrentTile], TilePosy[CurrentTile]);
        }

       

        return DistanceFromEquator;

        
    }

    void TileMap::DetermineBiome()
    {
        uint8_t Humidity;
        uint8_t Temp;
       
        for(int i = 0; i < TileID.size()-1; i++)
        {
             if(TileHash[i] != River && TileHash[i] != Ocean)
            {
                if(TileHeight[i] >= 60 && TileHash[i] != River)
                {
                    TileType[i] = "Mountain";
                }
                else if(Temperature[i] >= 50 && Temperature[i] <= 85 && WaterExposure[i] >= 60 && WaterExposure[i] <= 100)
                {   

                TileType[i] = "Temperate rainforest";

                }
                else if(Temperature[i] >= 70 && Temperature[i] <= 90 && WaterExposure[i] >= 80 )
                {
                    TileType[i] = "Tropical rainforest";
                }
                else if(Temperature[i] >= 85 && WaterExposure[i] <= 15)
                {
                    TileType[i] = "Desert";
                }
                else if(Temperature[i] >= 70 && Temperature[i] <= 90 && WaterExposure[i] >= 10 && WaterExposure[i] <=20)
                {
                    TileType[i] = "Savanna";
                }
                

            }
        }
    }
