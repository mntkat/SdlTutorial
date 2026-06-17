#include <cstdlib>

#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <string>
#include <vector>

#include "App.h"

static SDL_AppResult processResult(int result)
{
    if (result == -1)
        return SDL_APP_FAILURE;
    else if (result == 0)
        return SDL_APP_CONTINUE;
    else
        return  SDL_APP_SUCCESS;
}

App* app;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    app = new App(argc, argv);
    return processResult(app->initResult);
}

SDL_AppResult SDL_AppEvent(void * appstate, SDL_Event *event) { return processResult(app->onEvent(event)); }

SDL_AppResult SDL_AppIterate(void * appstate) { return processResult(app->onUpdate()); }

void SDL_AppQuit(void * appstate, SDL_AppResult result) { delete app; }