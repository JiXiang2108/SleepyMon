#include"mon.h"

Mon::Mon(SDL_Renderer * renderer, int _x, int _y)
{
    mon = loadTexture("picwish.png", renderer);
    x = _x;
    y = _y;
}
Mon::~Mon()
{

}
void Mon::move(int delta_x, int delta_y)
{
    x += delta_x * MON_SPEED;
    y += delta_y * MON_SPEED;
}
void Mon::draw(SDL_Renderer *&renderer)
{
    SDL_Rect mon_rect = {x,y,100,95};
    SDL_RenderCopy(renderer,mon,NULL, &mon_rect);
}

