#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "Particles.h"

struct App
{
    const bool* keysstate;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Particles particles{50};

    SDL_Surface* surface;
    
    int initResult;
    
    App(int argc, char* argv[]);
    
    ~App();
    
    bool running = true;
    
    Uint64 fps = 0;
    
    Uint64 lastTime = 0;
    
    void quit();
    
    int mainLoop();
    
    int eventLoop(SDL_Event *event);
    
    int onInit(std::vector<std::string> args);
    
    void onEvent(SDL_Event *event);
    
    void onTick();
    
    void onUpdate();
    
    void onRender();
    
    void onQuit();
};