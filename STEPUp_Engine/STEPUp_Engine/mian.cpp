#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

//객체 UI
const int OBJECTUI_WIDTH = 340;
const int OBJECTUI_HEIGHT = 500;

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

bool main_popup = false;

static void ShowExampleAppMainMenuBar()
{
    ImGui::ShowDemoWindow();
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("NewProject")){}
            if(ImGui::MenuItem("Open")){}
            if(ImGui::MenuItem("Option1")){}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void set_Main_PopUp() {
    if (main_popup) {
        ImGui::OpenPopup("Example Popup");
        main_popup = false;
    }
    
    // 팝업 윈도우 렌더링
    if (ImGui::BeginPopup("Example Popup")) {
        if (ImGui::BeginMenu("Create Object")) { 
            if (ImGui::MenuItem("Circle")) {
                cout << "원 생성\n";
            }
            if (ImGui::MenuItem("Triangle")) {
                cout << "삼각형 생성\n";
            }
            if (ImGui::MenuItem("Rectangle")) {
                cout << "사각형 생성\n";
            }
            if (ImGui::MenuItem("Resource")) {
                cout << "리소스 불러오기...\n";

            }
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Option 2")) {

        }
        if (ImGui::MenuItem("Option 3")) {

        }
        if (ImGui::MenuItem("Option 4")) {

        }



        ImGui::EndPopup();
    }
}

void set_GameView() {
    ImGui::NewFrame();  // ImGui에 대한 NewFrame 호출
    ImGui::SetNextWindowPos(ImVec2(WINDOW_WIDTH - GV_WIDTH, 0)); // 윈도우 위치를 지정
    ImGui::Begin("GameView", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::End();
    ImGui::Render();
}

void set_ImGUI() {
    ImGui::SetNextWindowSize(ImVec2(OBJECTUI_WIDTH, OBJECTUI_HEIGHT)); // 윈도우 크기를 지정
    //ui 헤더 이름
    ImGui::Begin("Obecjt-UI", nullptr);
    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        //inputFloat 상자 크기들 조정
        ImGui::PushItemWidth(47);
            //Translate
            ImGui::Text("Position \t");
            ImGui::SameLine();
            {
                static float pos[] = { 0.0f,0.0f,0.0f };    
                ImGui::PushID("TX");
                    ImGui::Text("X");
                    ImGui::SameLine();
                    ImGui::InputFloat(" ", &pos[0], NULL, NULL, "%.2f");
                ImGui::PopID();
                ImGui::SameLine();
                ImGui::PushID("TY");
                    ImGui::Text("Y");
                    ImGui::SameLine();
                    ImGui::InputFloat(" ", &pos[1], NULL, NULL, "%.2f");
                ImGui::PopID();       
                ImGui::SameLine();
                ImGui::PushID("TZ");
                    ImGui::Text("Z");
                    ImGui::SameLine();
                    ImGui::InputFloat(" ", &pos[2], NULL, NULL, "%.2f");
                ImGui::PopID();
            }

            //Rotation
            ImGui::Text("Rotation \t");
            static float rot[3] = { 0.0f,0.0f,0.0f };
            ImGui::SameLine();
            {
                ImGui::PushID("RX");
                    ImGui::Text("X");
                    ImGui::SameLine();
                    ImGui::InputFloat(" ", &rot[0], NULL, NULL, "%.2f");
                ImGui::PopID();
                ImGui::SameLine();
                ImGui::PushID("RY");
                    ImGui::Text("Y");
                    ImGui::SameLine();
                    ImGui::InputFloat(" ", &rot[1], NULL, NULL, "%.2f");
                ImGui::PopID();
                ImGui::SameLine();
                ImGui::PushID("RZ");
                    ImGui::Text("Z");
                    ImGui::SameLine();
                    ImGui::InputFloat(" ", &rot[2], NULL, NULL, "%.2f");
                ImGui::PopID();
            }

            //Scale
            ImGui::Text("Scale\t\t");
            static float scale[3] = { 0.0f,0.0f,0.0f };
            ImGui::SameLine();
            {                
            ImGui::PushID("SX");
                ImGui::Text("X");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &scale[0], NULL, NULL, "%.2f");
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID("SY");
                ImGui::Text("Y");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &scale[1], NULL, NULL, "%.2f");
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID("SZ");
                ImGui::Text("Z");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &scale[2], NULL, NULL, "%.2f");
            ImGui::PopID();
            }
        ImGui::PopItemWidth();
        ImGui::Separator();
    }

    if (ImGui::BeginPopup("MyPopup")) {
        ImGui::Text("This is a popup!");
        ImGui::EndPopup();
    }
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
            ImGui_ImplSDL2_ProcessEvent(&e);
            switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    main_popup = true;
                }
                break;
            }
        }

        //프레임 시작
        ImGui_ImplSDLRenderer2_NewFrame();  // ImGui Renderer2에 대한 NewFrame 호출
        ImGui_ImplSDL2_NewFrame();  // ImGui SDL2에 대한 NewFrame 호출
        ImGui::NewFrame();

        set_Main_PopUp();
        ShowExampleAppMainMenuBar();
        set_ImGUI();


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