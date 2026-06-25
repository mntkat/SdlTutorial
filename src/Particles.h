#pragma once

#include "SDL3/SDL.h"
#include <vector>

struct Particles
{
    struct Particle
    {
        SDL_FPoint point;
        float speed;
    };
    std::vector<Particle> particles;
    
    Particles(size_t numberOfPoints) {
        for (int i = 0; i < numberOfPoints; i++)
        {
            Particle particle;
            particle.point = SDL_FPoint{
                .x = static_cast<float>(SDL_rand(320)),
                .y = static_cast<float>(SDL_rand(10))
            };
            
            particles.push_back(particle);
        }
    }
    
    std::vector<SDL_FPoint> points()
    {
        std::vector<SDL_FPoint> points;
        for (int i = 0; i < particles.size(); i++)
        {
            points.push_back(particles[i].point);
        }
        return points;
    }
};
