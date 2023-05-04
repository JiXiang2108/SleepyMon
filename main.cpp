#include<iostream>
#include<SDL.h>
#include<stdio.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include"SDL.h"
#include"bird.h"
#include"cloud.h"
#include"mon.h"
#include<chrono>
#include<ctime>
#include<vector>
#include <cstdlib>
#include"Text.h"

using namespace std;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    TTF_Init();
    SDL_Event e;

    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);
    Mix_Music *gMusic = NULL;
    gMusic = Mix_LoadMUS( "BG.wav" );
    Mix_PlayMusic(gMusic, -1);
    bool quit = false;
    bool start = false;
    //Màn hình đầu tiên
    SDL_Texture* background1 = loadTexture("SleepyMon.png", renderer);
    SDL_Texture* background2 = loadTexture("SleepyMon(1).png", renderer);
    SDL_Texture* background3 = loadTexture("SleepyMon(2).png", renderer);
    SDL_Texture* gameover = loadTexture("Game over.png", renderer);
    int a;
    while (!start)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background1, NULL, NULL);

        //Vị trí nút play và exit
        SDL_Rect play_button;
        play_button.x = 460;
        play_button.y = 478;
        play_button.w = 280;
        play_button.h = 106;
        SDL_Rect exit_button;
        exit_button.x = 460;
        exit_button.y = 613;
        exit_button.w = 280;
        exit_button.h = 106;

        while (SDL_PollEvent(&e))
        {
            if (SDL_MOUSEMOTION == e.type)
            {
                SDL_Point mouse;
                SDL_GetMouseState(&mouse.x, &mouse.y);
                if (SDL_PointInRect(&mouse, &play_button))
                {
                    //SDL_RenderClear(renderer);
                    //SDL_RenderCopy(renderer, background2, NULL, NULL);
                    //if (SDL_MOUSEBUTTONDOWN == e.type) a = 4;
                     a = 1;
                }
                else if (SDL_PointInRect(&mouse, &exit_button))
                {
                    //SDL_RenderClear(renderer);
                    //SDL_RenderCopy(renderer, background3, NULL, NULL);
                    //if (SDL_MOUSEBUTTONDOWN == e.type) a = 5;
                     a = 2;
                }
                else
                {
                    //SDL_RenderClear(renderer);
                    //SDL_RenderCopy(renderer, background1, NULL, NULL);
                    a = 3;
                }
            }
            if (SDL_MOUSEBUTTONDOWN == e.type && a == 1) a = 4;
            if (SDL_MOUSEBUTTONDOWN == e.type && a == 2) a = 5;
        }
        if (a == 1)
        {
            SDL_RenderCopy(renderer, background2, NULL, NULL);
        }
        else if (a == 2)
        {
            SDL_RenderCopy(renderer, background3, NULL, NULL);
        }
        else if (a == 3)
        {
            SDL_RenderCopy(renderer, background1, NULL, NULL);
        }
        else if (a == 4)
        {
            start = true;
        }
        else
        {
            start = true;
            quit = true;
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    //đồng hồ và biến đếm thời gian
    Uint32 start_time = SDL_GetTicks();
    Uint32 obstacle_timer = 0;
    Uint32 obstacle_timer2 = 0;
    SDL_Texture* background = loadTexture("164546.jpg", renderer);
    SDL_RenderCopy(renderer,background, NULL, NULL);
    //Khởi tạo dora & cloud
    Mon mon(renderer, 580, 320);
    //Cloud cloud(rand() % 1200, 0);
    vector<Cloud> clouds;
    vector<Bird> birds;

    int tocdo = 0;
    /*
    Cloud cloud(renderer, rand() % 400, 0);
    clouds.push_back(cloud);
    Bird bird(renderer, rand() % 600 + 200, 850);
    birds.push_back(bird);
    Bird bird2(renderer, rand() % 600 + 200, 850);
    birds.push_back(bird2);
    */
    int t = 0;
    while (!quit)
    {
        t = 1;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                // Thoát game
                quit = true;
                break;
            case SDL_KEYDOWN: {
                // Di chuyển nhân vật chính
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    if (mon.x > 10)
                    {
                        tocdo = -TOC_DO;

                        break;
                    }
                case SDLK_RIGHT:
                    if (mon.x < SCREEN_WIDTH - 100)
                    {
                        tocdo = TOC_DO;

                        break;
                    }
                }
                break;
            }
            }
        }
        Uint32 currentTime = SDL_GetTicks();
        /*
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 20.0f;
        lastTime = currentTime;
        */
        if (mon.x <= 10) tocdo = TOC_DO;
        if (mon.x >= SCREEN_WIDTH - 100) tocdo = - TOC_DO;
        mon.x += tocdo;
        // Tạo vật cản mới nếu đến đúng thời điểm
        Uint32 elapsed_time = SDL_GetTicks() - start_time;
        if (elapsed_time / 1000 >= 4 && elapsed_time / 1000 - obstacle_timer >= 4) {
            Cloud cloud(renderer, rand() % 400 + 300, 0);
            clouds.push_back(cloud);
            obstacle_timer = elapsed_time / 1000;
        }
        if (elapsed_time / 1000 >= 3 && elapsed_time / 1000 - obstacle_timer2 >= 3) {
            Bird bird(renderer, rand() % 600 + 200, 850);
            birds.push_back(bird);
            Bird bird2(renderer, rand() % 600 + 200, 850);
            birds.push_back(bird2);
            obstacle_timer2 = elapsed_time / 1000;
        }
        currentTime /= 2000;
        string time_ = to_string(currentTime);
        string score_ = "Score: " + time_;
        Text scoreGame(renderer, SCREEN_WIDTH - 150, 60,100, 30, score_);
        /*
        SDL_Surface* surfaceText = TTF_RenderText_Solid(fontchu, score, {255,255,255});
        SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
        */
        //Kiểm tra xem vật cản nào ra ngoài màn hình thì xóa
        for (auto &cloud : clouds) {
            cloud.move();
            if (cloud.x - 80 <= mon.x && mon.x <= cloud.x + 200 && cloud.y - 80 <= mon.y && mon.y <= cloud.y + 140) {
                quit = true; // Nếu nhân vật chính chạm vào vật cản thì kết thúc game
                break;
            }
            while(clouds.size() >= 5) clouds.erase(clouds.begin() + 0);
        }
        for (auto &bird : birds) {
            bird.move();

            if (bird.y + 70 > mon.y && bird.y < mon.y + 70 && bird.x + 70 > mon.x && bird.x < mon.x + 70) {
                quit = true; // Nếu nhân vật chính chạm vào vật cản thì kết thúc game
                break;
            }
            while(birds.size() >= 5) birds.erase(birds.begin() + 0);

        }
        // Xóa màn hình game cũ và vẽ lại
        SDL_RenderClear(renderer);
        //SDL_Texture* background = loadTexture("164546.jpg", renderer);
        SDL_RenderCopy(renderer,background, NULL, NULL);
        mon.draw(renderer);
        scoreGame.draw(renderer);
        for (auto &cloud : clouds) {
            cloud.draw(renderer);
        }
        for (auto &bird : birds) {
            bird.draw(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    if (t == 1)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameover, NULL, NULL);
        Uint32 currentTime = SDL_GetTicks()/2000;
        string time_ = to_string(currentTime);
        Text game_over(renderer, SCREEN_WIDTH - 250, 250,100, 150, time_);
        game_over.draw(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //Mix_Quit();
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    return 0;
}
