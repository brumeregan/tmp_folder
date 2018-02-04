/*
У якості індивідуального завдання необхідно написати програму, що
виконує розрахунок за певним рівнянням та будує графік функції.
Додатково необхідно у правому верхньому кутку екрана відобразити
«числовий» годинник, у лівому верхньому кутку надати текстову
інформацію про автора програми, а в нижній частині екрана вивести рядок
з підказкою про активні клавіші для управління роботою програми. При
виконанні роботи використати відповідний варіант завдання з Додатку Г.

 ρ = a * sin (5 φ) або ρ = a * cos (5 φ)
 */

#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <ctime>

#define A 5

using namespace std;

void render_text(SDL_Renderer *renderer, int x, int y, const char *text, TTF_Font *font, SDL_Rect *rect, SDL_Color *color);

int main(int argc, char* argv[]) {
    double g = 0.75;
    double k = log (g / 2 * M_PI);
    double a = 0.001;
    int MAX = 360;
    double x_offset = 400;
    double y_offset = 300;
    time_t raw_time;
    struct tm * timeinfo;
    char buffer [80];

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        TTF_Init();
        window = SDL_CreateWindow( "Lab 10", 0, 0, 800, 600, 0 );
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_SOFTWARE );
//        SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

        SDL_Color White = {255, 255, 255, 255};
        TTF_Font * font = TTF_OpenFont("arial.ttf", 25);
        int w, h;
        TTF_SizeText(font, "99:99:99" ,&w,&h);
        SDL_Rect time_rect;
        bool whirl = true;
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
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
//                    SDL_RenderDrawPoint(renderer, dX, dY);
                    dX_p = dX;
                    dY_p = dY;

                }
//                if (k > 0.1 && whirl)
//                    k *= 0.999;
//                else
//                {
//                    k *= 1.001;
//                    whirl = false;
//                }
//                if (k > 0.5)
//                    whirl = true;

//                std::cout << k;
                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 50);
                SDL_RenderDrawLine(renderer, 0, y_offset, 800, y_offset);
                SDL_RenderDrawLine(renderer, x_offset, 0, x_offset, 600);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                render_text(renderer, 0, 0, "Oksana Boyarko", font, &time_rect, &White);
                render_text(renderer, 800 - w, 0, buffer, font, &time_rect, &White);
                render_text(renderer, 0, 600-h, "Press ESC to exit.", font, &time_rect, &White);
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


/*
- x, y: upper left corner of string
- rect output Width and height contain rendered dimensions.
*/
void render_text(
        SDL_Renderer *renderer,
        int x,
        int y,
        const char *text,
        TTF_Font *font,
        SDL_Rect *rect,
        SDL_Color *color
) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = TTF_RenderText_Solid(font, text, *color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->x = x;
    rect->y = y;
    rect->w = surface->w;
    rect->h = surface->h;
    /* This is wasteful for textures that stay the same.
     * But makes things less stateful and easier to use.
     * Not going to code an atlas solution here... are we? */
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}
//
//void PolarToCartessian() {
//    int g = 5;
//    double k = log(g / 2 * M_PI);
//    double phi, x, y, ro, phiMin = 0., phiMax = 2*M_PI, h = 0.001;
//
//    for ( phi = phiMin; phi <= phiMax; phi += h )
//        //ρ = ρ0 * e**k φ
//        ro = pow(M_E, (k * phi));
//        x = ro*cos(phi);
//        y = ro*sin(phi);
//}