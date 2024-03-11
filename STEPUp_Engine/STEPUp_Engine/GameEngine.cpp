#include "GameEngine.h"

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

GameEngine::GameEngine(){
    window = nullptr;
    renderer = nullptr;
    pressedAlt = false;
    gameView = new GameView(WINDOW_WIDTH, WINDOW_HEIGHT);
    developmentView = new DevelopmentView(WINDOW_WIDTH, WINDOW_HEIGHT);

    currentView = developmentView;
}

void GameEngine::init_SDL() {
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
    //sIMG_Init(IMG_INIT_PNG);

    cout << "SDL 초기화 완료" << endl;
}

void GameEngine::init_IMGUI() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    cout << "IMGUI 초기화 완료" << endl;
}

void GameEngine::Start() {
    bool quit = false;

    PopUp MP;                   //MainPopup
    MainMenuBar MMB;            //MainMenuBar
    ObjUI objUI;
    Hierarchy HIUI;

    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
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
                    //ui 클릭시 무시...
                    if (io.WantCaptureMouse) {
                        cout << "ui 클릭";
                        continue;
                    }
                    printf("클릭 좌표 : (%d, %d)\n", mouseX, mouseY);
                    for (const auto& obj : GOS) {
                        if (mouseX >= obj->pos.x && mouseX <= obj->pos.x + 100 &&
                            mouseY >= obj->pos.y && mouseY <= obj->pos.y + 100) {
                            // 클릭된 오브젝트의 정보를 ObjUI에 설정
                            cout << " 사각형 클릭!!\n";
                            objUI.setObject(obj);
                            objUI.setPosition(obj->pos.x, obj->pos.y, obj->pos.z);
                            obj->clicked = true;
                            obj->dragging = true;
                            break;
                        }
                        else {
                            objUI.setObject(NULL);
                            objUI.Reset();
                            obj->clicked = false;
                        }
                    }
                    break;
                }
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    for (const auto& obj : GOS) {
                        obj->dragging = false;
                    }
                }
                break;
            case SDL_MOUSEMOTION:           //마우스 움직임 감지.
                for (const auto& obj : GOS) {
                    if (obj->dragging) {
                        obj->pos.x += e.motion.xrel;
                        obj->pos.y += e.motion.yrel;
                        //바로바로 갱신하기.
                        objUI.setPosition(obj->pos.x, obj->pos.y, 0.0f);
                    }
                }
                //viewPort


                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_LALT) {
                    pressedAlt = true;
                }
                break;
            case SDL_KEYUP:
                if (e.key.keysym.sym == SDLK_LALT) {
                    pressedAlt = false;
                }
            }
        }

        //프레임 시작
        ImGui_ImplSDLRenderer2_NewFrame();  // ImGui Renderer2에 대한 NewFrame 호출  
        ImGui_ImplSDL2_NewFrame();          // ImGui SDL2에 대한 NewFrame 호출
        ImGui::NewFrame();

        //imGui 렌더링 파트
        MP.Show();
        MMB.Show();
        objUI.Show();
        HIUI.Show();

        //커서 세팅 부분.
        setCursor();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        //게임뷰 세팅
        setViewPort();

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
}

GameEngine* GameEngine::instance = nullptr;

GameEngine* GameEngine::getInstance() {
    if (!instance) {
        instance = new GameEngine();
    }
    return instance;
}

int GameEngine::getWidth() {
    return WINDOW_WIDTH;
}

int GameEngine::getHeight() {
    return WINDOW_HEIGHT;
}

void GameEngine::setViewPort() {
    SDL_Rect panel = { 250, 0, WINDOW_WIDTH-250, WINDOW_HEIGHT-18 };
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
    SDL_RenderFillRect(renderer, &panel);
}

void GameEngine::setCursor() {
    SDL_Cursor* hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor* arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

    if (pressedAlt) {
        SDL_SetCursor(hand);
    }
    else {
        SDL_SetCursor(arrow);
    }
}