#include"Text.h"
#include<cstring>

using namespace std;

Text::Text(SDL_Renderer * renderer, int _x, int _y, string _s)
{
    x = _x;
    y = _y;
    s = _s.c_str();
    ourFont = TTF_OpenFont("Text.ttf",100);
    surfaceText = TTF_RenderText_Solid(ourFont,s,{255,255,255});
    score = SDL_CreateTextureFromSurface(renderer,surfaceText);
}
Text::~Text()
{

}
void Text::draw(SDL_Renderer *& renderer)
{
    SDL_Rect textRect = {x,y,100,30};
    SDL_RenderCopy(renderer, score, NULL, &textRect);
}
