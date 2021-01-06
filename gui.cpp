#include "YLWSUN.h"
#include <SDL.h>

using namespace std;

SDL_Window* gui_window = NULL;
SDL_Surface* gui_screen = NULL;
SDL_Renderer* gui_renderer = NULL;
SDL_RendererFlip f = SDL_FLIP_NONE;
SDL_Event e;

SDL_Rect player;
SDL_Rect enemy;

static char keyGrab[4] = {0,0,0,0};

//Sprites
SDL_Surface *bitmapSurface = NULL;
SDL_Texture *SHIPTEX = NULL;

int initGUI(int screen_size_w, int screen_size_h)
{
    printf("Initializing GUI...\n");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("\nSDL Error that I don't know how to print!\n");
    } else {
        gui_window = SDL_CreateWindow("GOOF-GUI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_size_w, screen_size_h, SDL_WINDOW_SHOWN);
        if (gui_window == NULL ) {
           printf("\nWindow could not be created!\n");
        } else {

            printf("Loading Textures...\n");
            gui_screen = SDL_GetWindowSurface(gui_window);
            SDL_FillRect(gui_screen, NULL, SDL_MapRGB(gui_screen->format, 0x00, 0x00, 0x00));
            SDL_UpdateWindowSurface(gui_window);

            gui_renderer = SDL_CreateRenderer(gui_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(gui_renderer, 0, 0, 0, 255);
            //SDL_RenderSetScale(gui_renderer, 2, 2);

            bitmapSurface = SDL_LoadBMP("img/ship.bmp");
            SHIPTEX = SDL_CreateTextureFromSurface(gui_renderer, bitmapSurface);
            SDL_FreeSurface(bitmapSurface);

            player.x = 0;
            player.y = 0;
            player.h = 16;
            player.w = 16;

            enemy.x = 0;
            enemy.y = 0;
            enemy.h = 16;
            enemy.w = 16;

            }
        }
        printf("Finished\n.");
        return 0;
}

char * refreshGUI(int px, int py, int pr, int ex, int ey, int er)
{
    SDL_RenderClear(gui_renderer);

    player.x = px;
    player.y = py;

    enemy.x = ex;
    enemy.y = ey;

    SDL_RenderCopyEx(gui_renderer, SHIPTEX, NULL, &player, pr, NULL, f);
    SDL_RenderCopyEx(gui_renderer, SHIPTEX, NULL, &enemy, er, NULL, f);

    SDL_RenderPresent(gui_renderer);

    keyGrab[0] = 0;
    keyGrab[1] = 0;
    keyGrab[2] = 0;

    for (int i = 4; i != 0; i--) { //Poll an arbitrary number of times because why not
        SDL_PollEvent(&e); // *laughs in terrible programming*

        if (e.key.type == SDL_KEYDOWN) {

            if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                keyGrab[0] = 1;
                //printf("Left \n");
            }

            if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                keyGrab[1] = 1;
                //printf("Right \n");
            }

            if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
                keyGrab[2] = 1;
                //printf("Up \n");
            }

            if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                keyGrab[3] = 1;
                //printf("Down \n");
            }
        }
    }

    return keyGrab;
}
