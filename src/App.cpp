#define SDL_FUNCTION_POINTER_IS_VOID_POINTER
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
    SDL_GL_SwapWindow(window);
    SDL_Delay(16);
    fps++;
    Uint64 deltaTime = SDL_GetTicks() - currentTick;
    if (currentTick > lastTime + 1000)
    {
        lastTime = currentTick;
        std::string title = "SDL/GL Tutorial - Fps: " + std::to_string(fps);
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
    
    window = SDL_CreateWindow("SDL/OpenGL Tutorial", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        return -1;
    }
    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        SDL_Log("Failed to create OpenGL Context");
        return -1;
    }

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        SDL_Log("Failed to initialize glad");
        return -1;
    }

    getOpenGLVersionInfo();

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    //if ()

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 4);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    /*renderer = SDL_CreateRenderer(window, nullptr);
    
    if (renderer == nullptr) {
        SDL_Log("Failed to create renderer");
        return -1;
    }
    else
    {
        SDL_Log("Renderer: %s", SDL_GetRendererName(renderer));
        
        SDL_Log("Available renderer drivers:");
        for (int i = 0; i < SDL_GetNumRenderDrivers(); i++)
        {
            SDL_Log("%d, %s,", i + 1, SDL_GetRenderDriver(i));
        }
        
        
        SDL_SetRenderLogicalPresentation(renderer, 320, 240, SDL_LOGICAL_PRESENTATION_STRETCH);
    }*/
    
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

void App::getOpenGLVersionInfo() {
    SDL_Log("Vendor: %s", glGetString(GL_VENDOR));
    SDL_Log("Renderer: %s", glGetString(GL_RENDERER));
    SDL_Log("Version: %s", glGetString(GL_VERSION));
    SDL_Log("Shading Language: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
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
    /*for (int i = 0; i < particles.particles.size(); i++)
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
    }*/
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
    
    
    /*
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
    */

    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(window);
}

void App::onQuit()
{
    SDL_Quit();
}
