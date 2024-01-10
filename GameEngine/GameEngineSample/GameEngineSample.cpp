#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("SDL UI Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void drawButton(int x, int y, int width, int height, SDL_Color color) {
    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
    SDL_Rect buttonRect = { x, y, width, height };
    SDL_RenderFillRect(gRenderer, &buttonRect);
}

int main(int argc, char* args[]) {
    if (!init()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    SDL_Color buttonColor = { 255, 0, 0, 255 }; // Red

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Check if the mouse click is inside the button area
                if (mouseX >= 100 && mouseX <= 200 && mouseY >= 100 && mouseY <= 150) {
                    // Change button color on click
                    buttonColor = { 0, 0, 255, 255 }; // Blue
                }
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); // White
        SDL_RenderClear(gRenderer);

        // Draw the button
        drawButton(100, 100, 100, 50, buttonColor);

        // Update the screen
        SDL_RenderPresent(gRenderer);
    }

    close();
    return 0;
}
