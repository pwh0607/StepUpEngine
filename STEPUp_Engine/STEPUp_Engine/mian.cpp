#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL.h>
#include <SDL_image.h>

#include "UI.h"
#include "GameObject.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

//윈도우 UI
const int WINDOW_WIDTH = 1440;
const int WINDOW_HEIGHT = 740;

//게임뷰 UI
const int GV_WIDTH = 1000;

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

    // SDL Image 초기화
    IMG_Init(IMG_INIT_PNG);

    cout << "SDL 초기화 완료" << endl;
}

void init_IMGUI() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    cout << "IMGUI 초기화 완료" << endl;
}

void draw() {
    int centerX = WINDOW_WIDTH / 2;
    int centerY = WINDOW_HEIGHT / 2;
    int radius = 100;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
    for (int w = 0; w < radius * 2; ++w) {
        for (int h = 0; h < radius * 2; ++h) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }

}

int main(int argc, char** argv) {
    //초기화 세팅
    init_SDL();
    init_IMGUI();

    bool quit = false;
    PopUp MP;                   //MainPopup
    MainMenuBar MMB;            //MainMenuBar
    //GameObject obj;
    
    //test
    
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL2_ProcessEvent(&e);
            switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    MP.isClicked = true;
                }
                else if (e.button.button == SDL_BUTTON_LEFT) {
                    
                }
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    cout << "마우스 버튼 업\n";
                }
            case SDL_MOUSEMOTION:
                
            }
            break;
        }

        //프레임 시작
        ImGui_ImplSDLRenderer2_NewFrame();  // ImGui Renderer2에 대한 NewFrame 호출
        ImGui_ImplSDL2_NewFrame();  // ImGui SDL2에 대한 NewFrame 호출
        ImGui::NewFrame();

        MP.Show();
        MMB.Show();
        //obj.Render(renderer);
        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}