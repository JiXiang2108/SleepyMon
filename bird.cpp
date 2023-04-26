#include"bird.h"

using namespace std;

Bird::Bird(SDL_Renderer * renderer, int _x, int _y)
{
    bird1 = loadTexture("1.png",renderer);
    bird2 = loadTexture("2.png",renderer);
    bird3 = loadTexture("3.png",renderer);
    bird4 = loadTexture("4.png",renderer);
    x = _x;
    y = _y;
}
Bird::~Bird()
{

}
void Bird::move()
{
    x += 5;
    y -= 5;
}
void Bird::draw(SDL_Renderer *&renderer)
{
    SDL_Rect bird_rect = {x, y, 100, 70};
    //SDL_RenderCopy(renderer, cloud, NULL, &cloud_rect);
    if (y % 120 >= 0 && y % 120 < 20)
    {
        SDL_RenderCopy(renderer,bird1,NULL,&bird_rect);
    }
    else if (y % 120 >= 20 && y % 120 < 40)
    {
        SDL_RenderCopy(renderer,bird2,NULL,&bird_rect);
    }
    else if (y % 120 >= 40 && y % 120 < 60)
    {
        SDL_RenderCopy(renderer,bird3,NULL,&bird_rect);
    }
    else if (y % 120 >= 60 && y % 120 < 80)
    {
        SDL_RenderCopy(renderer,bird4,NULL,&bird_rect);
    }
    else if (y % 120 >= 80)
    {
        SDL_RenderCopy(renderer,bird3,NULL,&bird_rect);
    }
    else
    {
        SDL_RenderCopy(renderer,bird2,NULL,&bird_rect);
    }
}

