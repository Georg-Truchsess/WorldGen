//custom headers
#include"Tile.h"
#include "Utils.h"
#include"FNV1A.h"
//std libraries
#include<iostream>
#include<random>

//3rd party libraries
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

const int SCREEN_WIDTH = 1900;
 const int SCREEN_HEIGHT = 1000;  

int main(int argc, char* argv[])
{

    //RNG seeding
std::random_device rd;
std::mt19937 gen(rd());
uint8_t Min = 1;
uint8_t Max = 7;
 std::uniform_int_distribution<int> distrib(Min, Max); 

 // NumX must always be equal to (2^n) + 1
 // This makes sure that there is always a midpoint
uint16_t NumX = 65;
uint16_t SeaLevel = 15;
int TableSize = NumX * NumX;
uint8_t chance;
uint16_t NumberofRiverTiles = 0;
   TileMap map; 

  map.GenerateID(TableSize);

  map.GenerateTileCoordinates(TableSize, NumX);

  
    
  map.GenerateHeightMap(100, -100, 5, NumX, gen);
map.TileType.reserve(map.TileID.size());
map.TilePopulation.reserve(map.TileID.size());
for(int i = 0; i < map.TileID.size(); i++)
{
    map.TileType.push_back("None");
    map.TilePopulation.push_back(0);
}
for(int i = 0; i < map.TileID.size()-1; i++)
{
    if(map.TileHeight[i] >= SeaLevel)
    {
        map.TileType[i] = "Plain";

        
    }
    else
    {
        map.TileType[i] = "Ocean";
    }
}
    
  for(int i = 0; i < (map.TileID.size()-1); i++)
  {
    if(map.TileHeight[i] > 35)
    {
        chance = distrib(gen);
        if(chance == 1)
        {
        map.GenerateRivers(i, NumX);
       }
    }
  }
  
  map.TileHash = map.HashRuntimeStrings(map.TileType);
  for(int i = 0; i <= map.TileID.size()-1; i++)
  {
    if(map.TileHash[i] == map.River)
    {
        NumberofRiverTiles++;
    }

  }
    if(NumberofRiverTiles < (map.TileID.size()/20))
    {
        
        std::uniform_int_distribution<int> LowlandRiverDistrib(1, 30); 
        for(int i = 0; i < (map.TileID.size()-1); i++)
         { 
            if(map.TileHeight[i] < 35 && map.TileHash[i] != map.Ocean)
            {
                chance = LowlandRiverDistrib(gen);
                if(chance == 1)
                {   
                map.GenerateRivers(i, NumX);
                }
                
            }
        }

    }

  map.CalculateWaterExposure(NumX);

  map.DetermineTemperature(NumX);

  map.DetermineBiome();
  
   map.TileHash = map.HashRuntimeStrings(map.TileType);

   PrintVector(NumX, map.WaterExposure);
   
    

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << " SDL could not initialize, error:" << SDL_GetError;

        return 1;
    }

    SDL_Window*  window = SDL_CreateWindow("WorldGen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        std::cout << "Window could not be created. Error:" << SDL_GetError;
        SDL_Quit();
    }

    SDL_Renderer* rend = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* surface;

    surface = IMG_Load("437.png");
    if(!surface)
    {
        std::cout << "image has not loaded" << std::endl; 
        IMG_GetError();
    }

    SDL_Texture* AsciiTable = SDL_CreateTextureFromSurface(rend, surface);

    

    

    SDL_FreeSurface(surface);
    bool IsRunning = true;

    SDL_Event event;
    

    while(IsRunning)
    {
        SDL_SetRenderDrawColor(rend, 0, 0, 0,255);
        SDL_RenderClear(rend);
        SDL_Rect rect = {15, 5, 10, 15};
        SDL_Rect r2 = {0, 0, 30, 30};

        map.Tile = rect;
        map.DrawMap(AsciiTable, rend, &r2);

        
        SDL_RenderPresent(rend);
        while(SDL_PollEvent(&event) != 0)
        {
           const Uint8* state = SDL_GetKeyboardState(NULL);

            if(event.type == SDL_QUIT)
            {
                IsRunning = false;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                 
                    if( state[SDL_SCANCODE_UP])
                    {
                    for(uint16_t i = 0; i < map.TileID.size(); i++)
                    {
                        map.TilePosy[i] += 30;
                    }
                    }
                     
                    if( state[SDL_SCANCODE_DOWN])
                    {
                    
                    for(uint16_t  i = 0; i < map.TileID.size(); i++)
                    {
                        map.TilePosy[i] -= 30;
                    }
                    }
                

                    if(state[SDL_SCANCODE_LEFT])
                    {
                    for(uint16_t i = 0; i < map.TileID.size(); i++)
                    {
                        map.TilePosx[i] += 30;
                        
                    }
                    }   
                    
                    if(state[SDL_SCANCODE_RIGHT])
                    {
                    for(uint16_t i = 0; i < map.TileID.size(); i++)
                    {
                        map.TilePosx[i] -= 30;
                    }
                    }
                    
                
                    }
                    
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    SDL_DestroyTexture(AsciiTable);
    SDL_Quit();

    return 0;

}
