#pragma once

#include<string>
#include<SDL_ttf.h>
#include"SDL.h"
#include<cstring>

using namespace std;

class Text
{
 public:
     int x, y, w, h;
     const char * s;
     Text(SDL_Renderer* renderer, int _x, int _y, int _w, int _h, string _s);
     ~Text();
     void draw(SDL_Renderer * &renderer);
 private:
    SDL_Texture * score;
    SDL_Surface* surfaceText;
    TTF_Font * ourFont;
};
