#pragma once

#include<SDL.h>
#include<stdio.h>
#include<SDL_image.h>
#include"SDL.h"

class Bird
{
 public:
    int x, y;
    Bird(SDL_Renderer * renderer, int _x, int _y);
    ~Bird();
    void move();
    void draw(SDL_Renderer *&renderer);
 private:
    SDL_Texture* bird1;
    SDL_Texture* bird2;
    SDL_Texture* bird3;
    SDL_Texture* bird4;
};
