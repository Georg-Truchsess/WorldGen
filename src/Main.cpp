#include<iostream>
#include<SDL2/SDL.h>



const int SCREEN_WIDTH = 800;
 const int SCREEN_HEIGHT = 600;  

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


    bool IsRunning = true;

    SDL_Event event;
    

    while(IsRunning)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                IsRunning = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
