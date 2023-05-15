#include"dorayaki.h"

Dorayaki::Dorayaki(SDL_Renderer *renderer)
{
    dorayaki = loadTexture("dorayaki.png", renderer);
}
Dorayaki::~Dorayaki()
{

}
void Dorayaki::draw(SDL_Renderer *&renderer)
{
    SDL_Rect dorayaki_rect = {x, 350, 40, 23};
    SDL_RenderCopy(renderer, dorayaki, NULL, &dorayaki_rect);
}
void Dorayaki::eat()
{
    if (x < SCREEN_WIDTH / 2)
    {
        x = x + 400 + rand() % (SCREEN_WIDTH / 2 - 500);
    }
    else
    {
        x = x - 400 - rand() % (SCREEN_WIDTH / 2 - 500);
    }
}
