#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <SDL.h>
#include <iostream>

using namespace std;

const int WINDOW_WIDTH = 1440;
const int WINDOW_HEIGHT = 740;

SDL_Window* window;
SDL_Renderer* renderer;

void init_SDL() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "SDL 초기화 실패: %s\n", SDL_GetError());
    }

    // SDL 윈도우 생성
    window = SDL_CreateWindow("ImGui SDL2 Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "SDL 창 생성 실패: %s\n", SDL_GetError());
    }

    // SDL Renderer 생성
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL Renderer 생성 실패: %s\n", SDL_GetError());
    }

    cout << "SDL 초기화 완료" << endl;
}

void init_IMGUI() {
    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();

    cout << "IMGUI 초기화 완료" << endl;
}

void set_ImGUI() {
    ImGui::NewFrame();
    ImGui::Begin("TEST");  
    ImGui::Text("Hello World!");
    ImGui::End();
}

int main(int argc, char** argv) {
    //초기화 세팅
    init_SDL();
    init_IMGUI();

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            
        }
        set_ImGUI();
        //Rendering
        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}