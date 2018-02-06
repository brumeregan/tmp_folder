//ρ = a * sin (5 φ) або ρ = a * cos (5 φ)

#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

void render_text(SDL_Renderer *renderer, int x, int y, const char *text, TTF_Font *font, SDL_Rect *rect, SDL_Color *color);

int main(int argc, char* argv[]) {
    double g = 0.75;
    double k = log (g / 2 * M_PI);
    double a = 0.001;
    int MAX = 360;

    double width = 1024;
    double height = 768;
    double x_offset = width/2;
    double y_offset = height/2;

    time_t raw_time;
    struct tm *timeinfo;
    char buffer[80];

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        TTF_Init();
        window = SDL_CreateWindow( "Lab 10", 0, 0, width, height, 0);
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

        SDL_Color White = {255, 255, 255, 255};
        TTF_Font *font = TTF_OpenFont("arial.ttf", 25);

        int w, h;
        TTF_SizeText(font, "99:99:99", &w, &h);
        SDL_Rect time_rect;

        bool whirl = true;
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);

        if (window != nullptr && renderer != nullptr) {
            SDL_bool done = SDL_FALSE;
            while (!done) {
                SDL_Event event;
                time(&raw_time);
                timeinfo = localtime(&raw_time);
                strftime (buffer,80,"%I:%M:%S",timeinfo);

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);

                double dX_p = (a * pow(M_E, k*0)) * cos(0) + x_offset;
                double dY_p = (a * pow(M_E, k*0)) * sin(0) + y_offset;

                for (int i = 1; i < MAX*100; i++) {
                    double theta = i * 2 * M_PI / MAX;
                    double dX = (a * pow(M_E, k*theta)) * cos(theta) + x_offset;
                    double dY = (a * pow(M_E, k*theta)) * sin(theta) + y_offset;

                    SDL_RenderDrawLine(renderer, dX_p, dY_p, dX, dY);
                    dX_p = dX;
                    dY_p = dY;
                }

                // SPINNER
                if (k > 0.1 && whirl) {
                    k *= 0.999;
                }
                else {
                    k *= 1.001;
                    whirl = false;
                }

                if (k > 0.5)
                    whirl = true;

                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 30);
                SDL_RenderDrawLine(renderer, 0, y_offset, width, y_offset);
                SDL_RenderDrawLine(renderer, x_offset, 0, x_offset, height);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                render_text(renderer, 0, 0, "Oksana Boiarko", font, &time_rect, &White);
                render_text(renderer, width - w, 0, buffer, font, &time_rect, &White);
                render_text(renderer, 0, height - h, "Press ESC to exit.", font, &time_rect, &White);
                SDL_RenderPresent(renderer);


                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }

        if (window) {
            SDL_DestroyWindow(window);
        }

        TTF_CloseFont(font);
        TTF_Quit();
    }

    SDL_Quit();
    return 0;
}


void render_text(SDL_Renderer *renderer,
        int x,
        int y,
        const char *text,
        TTF_Font *font,
        SDL_Rect *rect,
        SDL_Color *color) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = TTF_RenderText_Solid(font, text, *color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->x = x;
    rect->y = y;
    rect->w = surface->w;
    rect->h = surface->h;

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}
