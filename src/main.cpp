#include <cstdlib>

#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/*
int main(int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("fail!");
        return EXIT_FAILURE;
    }
    
    
    
    SDL_Delay(5000);
    
    SDL_Quit();
    
    return 0;
}
*/

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        return SDL_APP_FAILURE;
    }
    
    SDL_Window* window; 
    window = SDL_CreateWindow("SDL Tutorial", 320, 240, SDL_WINDOW_RESIZABLE);
    return  SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void * appstate, SDL_Event *event)
{
    return  SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void * appstate)
{
    SDL_Delay(5000);
    return  SDL_APP_SUCCESS;
}

void SDL_AppQuit(void * appstate, SDL_AppResult result)
{
    SDL_Quit();
}