#pragma once

#include<SDL.h>
#include<stdio.h>
#include<SDL_image.h>
#include"SDL.h"

class Cloud
{
 public:
    int x, y;
    Cloud(SDL_Renderer * renderer, int _x, int _y);
    ~Cloud();
    void move();
    void draw(SDL_Renderer *&renderer);
 private:
    SDL_Texture* cloud;
};
