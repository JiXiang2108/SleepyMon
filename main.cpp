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
#include"dorayaki.h"
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
    Mix_Chunk *gSound = NULL;
    gMusic = Mix_LoadMUS( "BG.wav" );
    gSound = Mix_LoadWAV("Sound.mp3");
    Mix_PlayMusic(gMusic, -1);
    bool quit = false;
    bool start = false;
    bool tutor = false;
    bool mute = false;
    SDL_Texture* background1 = loadTexture("SleepyMon.png", renderer);
    SDL_Texture* background2 = loadTexture("SleepyMonPlay.png", renderer);
    SDL_Texture* background3 = loadTexture("SleepyMonExit.png", renderer);
    SDL_Texture* background4 = loadTexture("SleepyMonTutorial.png", renderer);
    SDL_Texture* background5 = loadTexture("SleepyMonBack1.png", renderer);
    SDL_Texture* background6 = loadTexture("SleepyMonBack2.png", renderer);
    SDL_Texture* gameover1 = loadTexture("Game over (1).png", renderer);
    SDL_Texture* gameover2 = loadTexture("Game over (2).png", renderer);
    SDL_Texture* gameover3 = loadTexture("Game over (3).png", renderer);
    SDL_Texture* xicon = loadTexture("X.png", renderer);
    SDL_Texture* soundicon = loadTexture("Soundicon.png", renderer);
    int a = 4;
    int b = 3;
    int c = 0;
    int t = 0;
    int highscore = 0;
    int birdx;
    int dora = 0;
    string score, hscore, score_,highscore_;
    //Vị trí các button
    SDL_Rect play_button = {460,478,280,106};
    SDL_Rect exit_button = {460,613,280,106};
    SDL_Rect replay_button = {553,392,260,103};
    SDL_Rect exit2_button = {874,392,260,103};
    SDL_Rect tutorial = {460,343,280,106};
    SDL_Rect back_button = {481,630,245,70};
    SDL_Rect sound = {SCREEN_WIDTH - 120, 70, 60, 54};
    SDL_Rect x_button = {SCREEN_WIDTH - 120, 70, 60, 60};
    while (!start)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background1, NULL, NULL);
        while (SDL_PollEvent(&e))
        {
            if (SDL_MOUSEMOTION == e.type)
            {
                SDL_Point mouse;
                SDL_GetMouseState(&mouse.x, &mouse.y);
                if (SDL_PointInRect(&mouse, &play_button)) a = 1;
                else if (SDL_PointInRect(&mouse, &exit_button)) a = 2;
                else if (SDL_PointInRect(&mouse, &tutorial)) a = 3;
                else if (SDL_PointInRect(&mouse, &sound)) a = 8;
                else a = 4;
            }
            if (SDL_MOUSEBUTTONDOWN == e.type && a == 1) a = 5;
            if (SDL_MOUSEBUTTONDOWN == e.type && a == 2) a = 6;
            if (SDL_MOUSEBUTTONDOWN == e.type && a == 3) a = 7;
            if (SDL_MOUSEBUTTONDOWN == e.type && a == 8)
            {
                if (mute == true)
                {
                    mute = false;
                    Mix_ResumeMusic();
                }
                else
                {
                    mute = true;
                    Mix_PauseMusic();
                }
            }
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
            SDL_RenderCopy(renderer, background4, NULL, NULL);
        }
        else if (a == 4)
        {
            SDL_RenderCopy(renderer, background1, NULL, NULL);
        }
        else if (a == 5)
        {
            start = true;
        }
        else if (a == 6)
        {
            start = true;
            t = 2;
        }
        else if (a == 7)
        {
            c = 0;
            tutor = true;
            while (tutor)
            {
                SDL_RenderClear(renderer);
                while (SDL_PollEvent(&e))
                {
                    if (SDL_MOUSEMOTION == e.type)
                    {
                        SDL_Point mouse;
                        SDL_GetMouseState(&mouse.x, &mouse.y);
                        if (SDL_PointInRect(&mouse, &back_button))
                        {
                            c = 1;
                        }
                        else c = 0;
                    }
                    if (SDL_MOUSEBUTTONDOWN == e.type && c == 1) tutor = false;
                }
                if (c == 1)
                {
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, background6, NULL, NULL);
                }
                else
                {
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, background5, NULL, NULL);
                }
                SDL_RenderPresent(renderer);
            }
            a = 4;
        }
        SDL_RenderCopy(renderer, soundicon, NULL, &sound);
        if (mute == true) SDL_RenderCopy(renderer, xicon, NULL, &x_button);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    while (t != 2)
    {
        dora = 0;
        b = 3;
        //đồng hồ và biến đếm thời gian
        Uint32 start_time = SDL_GetTicks();
        Uint32 obstacle_timer = 0;
        Uint32 obstacle_timer2 = 0;
        SDL_Texture* background = loadTexture("164546.jpg", renderer);
        SDL_RenderCopy(renderer,background, NULL, NULL);
        //Khởi tạo dora
        Mon mon(renderer, 580, 320);
        Dorayaki dorayaki(renderer);
        dorayaki.x = 300;
        vector<Cloud> clouds;
        vector<Bird> birds;

        int tocdo = 0;

        while (t == 0)
        {
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
                birdx = rand() % 600 + 200;
                Bird bird(renderer, birdx, 850);
                birds.push_back(bird);
                Bird bird2(renderer, birdx - 200 - rand() % 300, 850);
                birds.push_back(bird2);
                obstacle_timer2 = elapsed_time / 1000;
            }
            score = to_string(dora);
            if (highscore < dora) highscore = dora;
            hscore = to_string(highscore);
            score_ = "Score: " + score;
            highscore_ = "High score: " + hscore;
            Text scoreGame(renderer, SCREEN_WIDTH - 170, 60,100, 30, score_);
            Text high_score(renderer, SCREEN_WIDTH - 170, 30, 160, 30, highscore_);
            //Kiểm tra xem vật cản nào ra ngoài màn hình thì xóa
            for (auto &cloud : clouds) {
                cloud.move();
                if (cloud.x - 80 <= mon.x && mon.x <= cloud.x + 200 && cloud.y - 80 <= mon.y && mon.y <= cloud.y + 140) {
                    t = 1; // Nếu nhân vật chính chạm vào vật cản thì kết thúc game
                    break;
                }
                while(clouds.size() >= 5) clouds.erase(clouds.begin() + 0);
            }
            for (auto &bird : birds) {
                bird.move();

                if (bird.y + 70 > mon.y && bird.y < mon.y + 70 && bird.x + 70 > mon.x && bird.x < mon.x + 70) {
                    t = 1; // Nếu nhân vật chính chạm vào vật cản thì kết thúc game
                    break;
                }
                while(birds.size() >= 5) birds.erase(birds.begin() + 0);

            }
            if (dorayaki.x >= mon.x - 40 && dorayaki.x <= mon.x + 100)
            {
                Mix_PlayChannel(-1, gSound, 0);
                dora ++;
                dorayaki.eat();
            }
            SDL_RenderCopy(renderer,background, NULL, NULL);
            mon.draw(renderer);
            dorayaki.draw(renderer);
            scoreGame.draw(renderer);
            high_score.draw(renderer);

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
            SDL_RenderCopy(renderer, gameover1, NULL, NULL);
            score = to_string(dora);
            Text game_over(renderer, SCREEN_WIDTH - 220, 210,60, 90, score);
            Text game_over2(renderer, SCREEN_WIDTH - 220, 288, 60, 90, hscore);
            while (t == 1)
            {
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, gameover1, NULL, NULL);
                while (SDL_PollEvent(&e))
                {
                    if (SDL_MOUSEMOTION == e.type)
                    {
                        SDL_Point mouse;
                        SDL_GetMouseState(&mouse.x, &mouse.y);
                        if (SDL_PointInRect(&mouse, &replay_button)) b = 1;
                        else if (SDL_PointInRect(&mouse, &exit2_button)) b = 2;
                        else b = 3;
                    }
                    if (SDL_MOUSEBUTTONDOWN == e.type && b == 1) b = 4;
                    if (SDL_MOUSEBUTTONDOWN == e.type && b == 2) b = 5;
                }
                if (b == 1)
                {
                    SDL_RenderCopy(renderer, gameover2, NULL, NULL);
                }
                else if (b == 2)
                {
                    SDL_RenderCopy(renderer, gameover3, NULL, NULL);
                }
                else if (b == 3)
                {
                    SDL_RenderCopy(renderer, gameover1, NULL, NULL);
                }
                else if (b == 4)
                {
                    t = 0;
                }
                else
                {
                    t = 2;
                }
                game_over.draw(renderer);
                game_over2.draw(renderer);
                SDL_RenderPresent(renderer);
                SDL_Delay(10);
            }
        }
    }
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk(gSound);
    gMusic = NULL;
    gSound = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    return 0;
}
