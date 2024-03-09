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

//������ UI
const int WINDOW_WIDTH = 1440;
const int WINDOW_HEIGHT = 740;

//���Ӻ� UI
const int GV_WIDTH = 1000;

void init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "SDL �ʱ�ȭ ����: %s\n", SDL_GetError());
    }

    // SDL ������ ����
    window = SDL_CreateWindow("ImGui SDL2 Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "SDL â ���� ����: %s\n", SDL_GetError());
    }

    // SDL Renderer ����
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL Renderer ���� ����: %s\n", SDL_GetError());
    }

    // SDL Image �ʱ�ȭ
    IMG_Init(IMG_INIT_PNG);

    cout << "SDL �ʱ�ȭ �Ϸ�" << endl;
}

void init_IMGUI() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    cout << "IMGUI �ʱ�ȭ �Ϸ�" << endl;
}
//Rect, Tri, Resource�� ��ĳ��Ʈ �Ǿ� ����ǹǷ� �����ͷ� �����ؾ��Ѵ�.
vector<GameObject *> GOS;

int main(int argc, char** argv) {
    //�ʱ�ȭ ����
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
                    printf("Ŭ�� ��ǥ : (%d, %d)\n", mouseX, mouseY);

                    for (const auto& obj : GOS) {
                        if (mouseX >= obj->pos.x && mouseX <= obj->pos.x + 100 &&
                            mouseY >= obj->pos.y && mouseY <= obj->pos.y + 100) {
                            // Ŭ���� ������Ʈ�� ������ ObjUI�� ����
                            cout << " �簢�� Ŭ��!!\n";
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
            case SDL_MOUSEMOTION:           //���콺 ������ ����.
                break;
            }
        }

        //������ ����
        ImGui_ImplSDLRenderer2_NewFrame();  // ImGui Renderer2�� ���� NewFrame ȣ��  
        ImGui_ImplSDL2_NewFrame();  // ImGui SDL2�� ���� NewFrame ȣ��
        ImGui::NewFrame();
        //objUI.Set_Position(mouseX, mouseY, 0.0f);
        //imGui ������ ��Ʈ
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