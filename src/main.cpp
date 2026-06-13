#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("fail!");
        return -1;
    }
    
    SDL_Window* window; 
    window = SDL_CreateWindow("SDL Tutorial", 320, 240, SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);
    
    SDL_Delay(5000);
    
    SDL_Quit();
    
    return 0;
}