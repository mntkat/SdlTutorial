#include "App.h"

App::App(int argc, char* argv[])
{
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
    initResult = onInit(args);
}


App::~App()
{
    onQuit();
}

int App::onInit(std::vector<std::string> args)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        return -1;
    }
    
    window = SDL_CreateWindow("SDL Tutorial", 320, 240, SDL_WINDOW_RESIZABLE);
    int w,h;
    SDL_GetWindowSize(window, &w, &w);
    
    keysstate = SDL_GetKeyboardState(nullptr);
    return 0;   
}

int App::onEvent(SDL_Event* event)
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

int App::onUpdate()
{
    return 0;
}

void App::onQuit()
{
    SDL_Quit();
}
