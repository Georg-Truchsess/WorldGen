//custom headers
#include"Tile.h"

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




   TileMap map;

  map.GenerateID(289);

  map.GenerateTileCoordinates(289, 17);

  map.GenerateHeightMap(100, -100, 0, 17, gen);

  int it = 0;
for(const auto& item : map.TileHeight)
{
    if(it < 17)
    {
    std::cout<< static_cast<int>(item) << " ";
    }
    if (it > 17){
        std::cout << " " << std::endl;
        it = 0;
    }
}
   
   
    

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
        SDL_Rect rect = {15, 8, 10, 20};
        SDL_RenderCopy(rend, AsciiTable, &rect, NULL);
        SDL_RenderPresent(rend);
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                IsRunning = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    SDL_DestroyTexture(AsciiTable);
    SDL_Quit();

    return 0;

}
