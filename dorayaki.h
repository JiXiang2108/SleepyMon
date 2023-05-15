#pragma once

#include<SDL.h>
#include<stdio.h>
#include<SDL_image.h>
#include"SDL.h"

class Dorayaki
{
 public:
     int x;
     Dorayaki(SDL_Renderer* renderer);
     ~Dorayaki();
     void draw(SDL_Renderer *&renderer);
     void eat();
 private:
    SDL_Texture* dorayaki;
};
