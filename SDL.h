#pragma once

#include<SDL.h>
#include<iostream>
#include<stdio.h>
#include<SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 750;
const int TOC_DO = 10;
const string WINDOW_TITLE = "晚安，哆啦A梦！SleepyMon";
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
SDL_Texture* loadTexture( string path, SDL_Renderer * renderer );

