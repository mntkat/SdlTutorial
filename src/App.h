#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <string>
#include <vector>

struct App
{
    const bool* keysstate;
    SDL_Window* window;
    
    int initResult;
    
    App(int argc, char* argv[]);
    
    ~App();
    
    int onInit(std::vector<std::string> args);
    
    int onEvent(SDL_Event *event);
    
    int onUpdate();
    
    void onQuit();
};