#include <SDL2/SDL.h>
#include <stdio.h>
#define ROWS 50
#define COLUMNS 70

int current[ROWS][COLUMNS];
int next[ROWS][COLUMNS];

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Game of Life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1400,
        1000,
        0
    );

    if (!window)
    {
        printf("Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);



    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // blend mode for transparent colors
    int running = 1;
    current[10][10] = 1;
    current[10][11] = 1;
    current[10][12] = 1;
    while (running) {
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Only sets the current drawing color to black
        SDL_RenderClear(renderer);

        

        int cell_size = 20;
        
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLUMNS; col++) {

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);

                // Creates a rectangle struct
                SDL_Rect cell = {
                    cell_size * col, // x position
                    cell_size * row, // y position
                    cell_size, // width
                    cell_size  // height
                };
                SDL_Rect inner = {
                    cell_size * col + 1,
                    cell_size * row + 1,
                    cell_size - 2,
                    cell_size - 2
                };

                SDL_RenderDrawRect(renderer, &cell);

                if (current[row][col] == 1) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &inner);
                }
            }
        }

        for (int row = 0; row <= ROWS; row++) {
            for (int col = 0; col <= COLUMNS; col++) {

                int alive = 0;
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        if (i == 0 && j == 0) {
                            continue;
                        }
                        if (current[row + i][col + j] == 1) {
                            alive++;
                        }
                    }
                }

                if (current[row][col] == 1) {
                    if (alive < 2 || alive > 3) {
                        next[row][col] = 0;
                    }
                    else next[row][col] = 1;
                }
                else {
                    if (alive == 3) {
                        next[row][col] = 1;
                    }
                    else next[row][col] = 0;
                }
            }
        }

        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLUMNS; col++) {
                current[row][col] = next[row][col]  ;
            }
        }


        // Delay
        SDL_Delay(150);
        // Everything happening before is on a hidden buffer, Renderpresent swaps the hidden buffer with the visible buffer
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}