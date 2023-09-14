#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

static int a_button_count = 0;

int main(int argc, char* argv[]) 
{
    //SDL_SetMainReady();

    SDL_Window* window = SDL_CreateWindow("Controller Input Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    std::cout<<"program start."<<std::endl;

    bool quit = false;
    SDL_Event e;
    while (!quit) 
    {
        while (SDL_PollEvent(&e)) 
        {
            std::cout << "event!"<<e.type << SDL_KEYDOWN<< std::endl;
            switch (e.type) 
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.scancode == SDL_SCANCODE_T && e.key.repeat == 0) 
                    {
                        std::cout << "T key pressed!" << std::endl;
                    }
                    break;
                case SDL_KEYUP:
                    if (e.key.keysym.scancode == SDL_SCANCODE_T && e.key.repeat == 0) 
                    {
                        std::cout << "T key released!" << std::endl;
                    }
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
