#pragma once

#include <glad//glad.h>
#include <gl/GL.h>
#define SDL_FUNCTION_POINTER_IS_VOID_POINTER
#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "Particles.h"

struct App
{
    const bool* keysstate;
    SDL_Window* window;
    SDL_GLContext glContext;

    /*
    SDL_Renderer* renderer;
    Particles particles{1000};

    SDL_Surface* surface;
    */  
    int initResult;
    
    App(int argc, char* argv[]);
    
    ~App();
    
    bool running = true;

    bool fullscreen = false;
    
    Uint64 fps = 0;
    
    Uint64 lastTime = 0;

    void getOpenGLVersionInfo();
    
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