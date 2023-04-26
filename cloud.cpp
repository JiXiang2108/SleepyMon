#include"cloud.h"

using namespace std;

Cloud::Cloud(SDL_Renderer * renderer, int _x, int _y)
{
    cloud = loadTexture("picwish (2).png",renderer);
    x = _x;
    y = _y;
}
Cloud::~Cloud()
{

}
void Cloud::move()
{
    x += 3;
    y += 3;
}
void Cloud::draw(SDL_Renderer *&renderer)
{
    SDL_Rect cloud_rect = {x, y, 269, 187};
    SDL_RenderCopy(renderer, cloud, NULL, &cloud_rect);
}
