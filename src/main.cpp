#include <cstdlib>

#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <string>
#include <vector>

struct App
{
    const bool* keysstate;
    SDL_Window* window;
    
    App() {}
    
    ~App()
    {
        onQuit();
    }
    
    int onInit(std::vector<std::string> args)
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            return -1;
        }
        int w,h;
        SDL_GetWindowSize(window, &w, &w);
        window = SDL_CreateWindow("SDL Tutorial", 320, 240, SDL_WINDOW_RESIZABLE);
    
        keysstate = SDL_GetKeyboardState(nullptr);
        return 0;    
    }
    
    int onEvent(SDL_Event *event)
    {
        //SDL_WarpMouseInWindow(window, 320/2, 240/2);
        if (event->type == SDL_EVENT_QUIT)
        {
            return 1;
        }
        else if (event->type == SDL_EVENT_KEY_DOWN)
        {
            SDL_Log(" a key was pressed %d", event->key.key);
        }
        /*else if (event->type == SDL_EVENT_MOUSE_MOTION)
        {
            SDL_Log("x,y: %f, %f", event->motion.x, event->motion.y);
            SDL_Log("xrel,yrel: %f, %f", event->motion.xrel, event->motion.yrel);
        }*/
        else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (event->button.button == SDL_BUTTON_LEFT)
            {
                SDL_Log("Left Button Clicked");
                SDL_Log("Left Clicks: %d", event->button.clicks);
            }
            else if (event->button.button == SDL_BUTTON_RIGHT)
            {
                SDL_Log("Right Button Clicked");
                SDL_Log("Right Clicks: %d", event->button.clicks);
            }
            else if (event->button.button == SDL_BUTTON_MIDDLE)
            {
                SDL_Log("Middle Button Clicked");
                SDL_Log("Middle Clicks: %d", event->button.clicks);
            }
        }
        
        if (keysstate[SDL_SCANCODE_L] == true && keysstate[SDL_SCANCODE_LSHIFT] == true)
        {
            SDL_Log("SDL_SCANCODE_L key way pressed");
        }
        
        return 0;
    }
    
    int onInterate()
    {
        return 0;
    }
    
    void onQuit()
    {
        SDL_Quit();
    }
};


App* app;

static SDL_AppResult processResult(int result)
{
    if (result == -1)
        return SDL_APP_FAILURE;
    else if (result == 0)
        return SDL_APP_CONTINUE;
    else
        return  SDL_APP_SUCCESS;
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    app = new App();
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
    return processResult(app->onInit(args));
}

SDL_AppResult SDL_AppEvent(void * appstate, SDL_Event *event) { return processResult(app->onEvent(event)); }

SDL_AppResult SDL_AppIterate(void * appstate) { return processResult(app->onInterate()); }

void SDL_AppQuit(void * appstate, SDL_AppResult result) { delete app; }