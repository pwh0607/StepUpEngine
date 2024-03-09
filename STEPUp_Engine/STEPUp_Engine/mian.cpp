#include <iostream>
#include <vector>

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
//Rect, Tri, Resource가 업캐스트 되어 저장되므로 포인터로 선언해야한다.
vector<GameObject *> GOS;

int main(int argc, char** argv) {
    //초기화 세팅
    init_SDL();
    init_IMGUI();

    bool quit = false;
    PopUp MP;                   //MainPopup
    MainMenuBar MMB;            //MainMenuBar

    ObjUI objUI;
    Rect r(10.0f, 10.0f, 0.0f, 10.0f, 10.0f, 10.0f, 1.0f, 1.0f, 1.0f);

    Rect r2(100.0f, 100.0f, 0.0f, 10.0f, 10.0f, 10.0f, 1.0f, 1.0f, 1.0f);
    GOS.push_back(&r);
    GOS.push_back(&r2);
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
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    printf("클릭 좌표 : (%d, %d)\n", mouseX, mouseY);

                    for (const auto& obj : GOS) {
                        if (mouseX >= obj->pos.x && mouseX <= obj->pos.x + 100 &&
                            mouseY >= obj->pos.y && mouseY <= obj->pos.y + 100) {
                            // 클릭된 오브젝트의 정보를 ObjUI에 설정
                            cout << " 사각형 클릭!!\n";
                            objUI.Set_Object(obj);
                            objUI.Set_Position(obj->pos.x, obj->pos.y, obj->pos.z);
                            obj->clicked = true;
                            /*
                            printf("%f,%f,%f\n", obj->pos.x, obj->pos.y, obj->pos.z);
                            printf("%f,%f,%f\n", obj.rot.x, obj.rot.y, obj.rot.z);
                            printf("%f,%f,%f\n", obj.scale.x, obj.scale.y, obj.scale.z);
                            */
                            break;
                        }
                        else {
                            objUI.Set_Object(NULL);
                            objUI.Reset();
                        }
                    }

                    break;
                }
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {

                }
                break;
            case SDL_MOUSEMOTION:           //마우스 움직임 감지.
                break;
            }
        }

        //프레임 시작
        ImGui_ImplSDLRenderer2_NewFrame();  // ImGui Renderer2에 대한 NewFrame 호출  
        ImGui_ImplSDL2_NewFrame();  // ImGui SDL2에 대한 NewFrame 호출
        ImGui::NewFrame();
        //objUI.Set_Position(mouseX, mouseY, 0.0f);
        //imGui 렌더링 파트
        MP.Show();
        MMB.Show();
        objUI.Show();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (auto& obj : GOS) {
            obj->Render(renderer);
        }
        ImGui::Render();
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