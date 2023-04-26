#pragma once

#include<stdio.h>
#include<SDL_image.h>
#include"SDL.h"

using namespace std;
const int MON_SPEED = 20;

class Mon
{
 public:
    int x, y;
    Mon(SDL_Renderer * renderer, int _x, int _y);
    ~Mon();
    void move(int delta_x, int delta_y);
    void draw(SDL_Renderer *&renderer);
 private:
    SDL_Texture * mon;
};

