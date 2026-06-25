#include "App.h"

App::App(int argc, char* argv[])
{
    running = true;
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
    initResult = onInit(args);
    lastTime = 0;
    fps = 0;
}


void App::quit()
{
    running = false;
}

App::~App()
{
    onQuit();
}

int App::mainLoop()
{
    Uint64 currentTick = SDL_GetTicks();
    onTick();
    SDL_Delay(16);
    fps++;
    Uint64 deltaTime = SDL_GetTicks() - currentTick;
    if (currentTick > lastTime + 1000)
    {
        lastTime = currentTick;
        std::string title = "Fps: " + std::to_string(fps);
        SDL_SetWindowTitle(window, title.c_str());
        fps = 0;
    }
    
    if (running == false)
    {
        return 1;
    }
    return 0;
}

void App::onTick()
{
    onUpdate();
    onRender();
}

int App::eventLoop(SDL_Event* event)
{
    onEvent(event);
    if (running == false)
    {
        return 1;
    }
    return 0;
}

int App::onInit(std::vector<std::string> args)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        return -1;
    }
    
    window = SDL_CreateWindow("SDL Tutorial", 320, 240, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, nullptr);
    
    if (renderer == nullptr) {
        SDL_Log("Failed to create renderer");
        return -1;
    }
    else
    {
        SDL_Log("Renderer: %s", SDL_GetRendererName(renderer));
        /*
        SDL_Log("Available renderer drivers:");
        for (int i = 0; i < SDL_GetNumRenderDrivers(); i++)
        {
            SDL_Log("%d, %s,", i + 1, SDL_GetRenderDriver(i));
        }
        */
        
        SDL_SetRenderLogicalPresentation(renderer, 320, 240, SDL_LOGICAL_PRESENTATION_STRETCH);
    }
    
    int w,h;
    SDL_GetWindowSize(window, &w, &w);
/*
#ifdef __APPLE__
    surface = SDL_LoadBMP("../../../Untitled.bmp");
#else
    surface = SDL_LoadBMP("./Untitled.bmp");
#endif
    
    if (surface == nullptr) {
        SDL_Log("Failed to load bitmap image");
        return -1;
    }
*/    
    keysstate = SDL_GetKeyboardState(nullptr);
    return 0;   
}

void App::onEvent(SDL_Event* event)
{
    //SDL_WarpMouseInWindow(window, 320/2, 240/2);
    if (event->type == SDL_EVENT_QUIT)
    {
        quit();
    }
    else if (event->type == SDL_EVENT_KEY_DOWN)
    {
        SDL_Log(" a key was pressed %d", event->key.key);
#ifndef __APPLE__
        if (event->key.key == SDLK_F11) {
            fullscreen = !fullscreen;
            SDL_SetWindowFullscreen(window, fullscreen);
        }
#else
        if (event->key.key == SDLK_F11) {
            if (keysstate[SDL_SCANCODE_LGUI] == true) {
                fullscreen = !fullscreen;
                SDL_SetWindowFullscreen(window, fullscreen);
            }
        }
#endif
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
#ifdef __APPLE__
    if (keysstate[SDL_SCANCODE_LGUI] == true)
    {
        fullscreen = !fullscreen;
        SDL_SetWindowFullscreen(window, fullscreen);
    }
#endif
}

void App::onUpdate()
{
    for (int i = 0; i < particles.particles.size(); i++)
    {
        Particles::Particle particle = particles.particles[i];
        //particle.point.x += 0.1f;
        particle.point.y += particle.speed * .1f;
        particle.point.x += SDL_sinf(particle.velocity) * 2.0f;
        particle.velocity += 0.2f;
        if (particle.point.y > 240)
        {
            particle.point.y = 0;
        }
        particles.particles[i] = particle;
    }
}

void App::onRender()
{
    /*
    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    if (nullptr != windowSurface) {
        bool result = SDL_BlitSurface(surface, nullptr, windowSurface, nullptr);
        if (!result) {
            SDL_Log("Render failed");
        }
        SDL_UpdateWindowSurface(window);
    }
    */
    
    
    
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xff, 0xff);
    SDL_RenderLine(renderer, 0.f, 0.f, 100.f, 50.f);
    
    SDL_FRect rect {
        .x = 100.f,
        .y = 50.f,
        .w = 100.f,
        .h = 100.f
    };
    SDL_RenderRect(renderer, &rect);
    SDL_RenderPoints(renderer, particles.points().data(), particles.particles.size());
    
    SDL_RenderPresent(renderer);
}

void App::onQuit()
{
    SDL_Quit();
}
