#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

const int SCREEN_WIDTH = 1000;
 const int SCREEN_HEIGHT = 1000;  

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << " SDL could not initialize, error:" << SDL_GetError;

        return 1;
    }

    SDL_Window*  window = SDL_CreateWindow("WorldGen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window== nullptr)
    {
        std::cout << "Window could not be created. Error:" << SDL_GetError;
        SDL_Quit();
    }

    SDL_Renderer* rend = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* surface = IMG_Load("/home/WorldGen/437.png");

    SDL_Texture* AsciiTable = SDL_CreateTextureFromSurface(rend, surface);

    SDL_FreeSurface(surface);
    bool IsRunning = true;

    SDL_Event event;
    

    while(IsRunning)
    {
        SDL_RenderClear(rend);
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
