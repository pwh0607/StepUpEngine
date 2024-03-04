#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

//��ü UI
const int OBJECTUI_WIDTH = 340;
const int OBJECTUI_HEIGHT = 500;

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
    
    // �˾� ������ ������
    if (ImGui::BeginPopup("Example Popup")) {
        if (ImGui::BeginMenu("Create Object")) { 
            if (ImGui::MenuItem("Circle")) {
                cout << "�� ����\n";
            }
            if (ImGui::MenuItem("Triangle")) {
                cout << "�ﰢ�� ����\n";
            }
            if (ImGui::MenuItem("Rectangle")) {
                cout << "�簢�� ����\n";
            }
            if (ImGui::MenuItem("Resource")) {
                cout << "���ҽ� �ҷ�����...\n";

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
    ImGui::NewFrame();  // ImGui�� ���� NewFrame ȣ��
    ImGui::SetNextWindowPos(ImVec2(WINDOW_WIDTH - GV_WIDTH, 0)); // ������ ��ġ�� ����
    ImGui::Begin("GameView", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::End();
    ImGui::Render();
}

void set_ImGUI() {
    ImGui::SetNextWindowSize(ImVec2(OBJECTUI_WIDTH, OBJECTUI_HEIGHT)); // ������ ũ�⸦ ����
    //ui ��� �̸�
    ImGui::Begin("Obecjt-UI", nullptr);
    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        //inputFloat ���� ũ��� ����
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
    //�ʱ�ȭ ����
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

        //������ ����
        ImGui_ImplSDLRenderer2_NewFrame();  // ImGui Renderer2�� ���� NewFrame ȣ��
        ImGui_ImplSDL2_NewFrame();  // ImGui SDL2�� ���� NewFrame ȣ��
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