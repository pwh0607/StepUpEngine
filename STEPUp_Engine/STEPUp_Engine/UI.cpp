#include <iostream>
#include <vector>
#include "Vector.h"
#include "imgui.h"
#include "UI.h"

using namespace std;

void MainMenuBar::Show() {
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("NewProject")) {}
            if (ImGui::MenuItem("Open")) {}
            if (ImGui::MenuItem("Option1")) {}
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

PopUp::PopUp() {
    isClicked = false;
}

void PopUp::Show() {
    if (isClicked) {    
        ImGui::OpenPopup("Example Popup");
        isClicked = false;
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
                //마우스 정보 가져오기
                
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                //해당 포인터 위치로 position 세팅
                Rect *rect = new Rect(mouseX, mouseY, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
                try
                {   
                    cout << "생성 및 추가" << endl;
                    gameEngine->GOS.push_back(rect);
                    cout << ":::::" << gameEngine->GOS.size() << endl;
                }   
                catch (const std::exception&)
                {
                    cout << "오류발생." << endl;
                    delete rect;
                }

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

ObjUI::ObjUI() :pos({ 0.0f,0.0f,0.0f }), rot({ 0.0f,0.0f,0.0f }), scale({ 1.0f,1.0f,1.0f }){
    obj = nullptr;
}

void ObjUI::setObject(GameObject *obj) {
    this->obj = obj;
}

void ObjUI::setName(string name) {
    
}
void ObjUI::setPosition(float x, float y, float z){
    pos.x = x;
    pos.y = y;
    pos.z = z;
}

void ObjUI::setRotation(float x, float y, float z) {
    rot.x = x;
    rot.y = y;
    rot.z = z;
}

void ObjUI::setScale(float x, float y, float z) {
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

void ObjUI::setColor() {
    ImVec4 vec;
    if (obj != nullptr) {
        vec = ImVec4(obj->rgba.x, obj->rgba.y, obj->rgba.z, obj->rgba.w);
    }
    else {
        vec = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // 기본값 설정
    }

    if (ImGui::ColorEdit4("RGBA Color", (float*)&vec)) {
        // UI에서 값이 변경되면 객체에 저장
        if (obj != nullptr) {
            obj->rgba = ImVec4(vec.x, vec.y, vec.z, vec.w);
        }
    }
}

void ObjUI::Show() {
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
            ImGui::PushID("TX");
                ImGui::Text("X");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &pos.x, NULL, NULL, "%.2f");
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID("TY");
                ImGui::Text("Y");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &pos.y, NULL, NULL, "%.2f");
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID("TZ");
                ImGui::Text("Z");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &pos.z, NULL, NULL, "%.2f");
            ImGui::PopID();
        }

        //Rotation
        ImGui::Text("Rotation \t");

        ImGui::SameLine();
        {
            ImGui::PushID("RX");
                ImGui::Text("X");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &rot.x, NULL, NULL, "%.2f");
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID("RY");
                ImGui::Text("Y");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &rot.y, NULL, NULL, "%.2f");
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID("RZ");
                ImGui::Text("Z");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &rot.z, NULL, NULL, "%.2f");
            ImGui::PopID();
        }

        //Scale
        ImGui::Text("Scale\t\t");
        ImGui::SameLine();
        {
            ImGui::PushID("SX");
                ImGui::Text("X");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &scale.x, NULL, NULL, "%.2f");
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID("SY");
                ImGui::Text("Y");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &scale.y, NULL, NULL, "%.2f");
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::PushID("SZ");
                ImGui::Text("Z");
                ImGui::SameLine();
                ImGui::InputFloat(" ", &scale.z, NULL, NULL, "%.2f");
            ImGui::PopID();
        }
        ImGui::PopItemWidth();
        ImGui::Separator();
    }

    if (ImGui::CollapsingHeader("Color", ImGuiTreeNodeFlags_DefaultOpen)) {
        setColor();
    }
    ImGui::End();
}

void ObjUI::Reset() {
    pos = { 0.0,0.0,0.0 };
    rot = { 0.0,0.0,0.0 };
    scale = { 0.0,0.0,0.0 };
}

Hierarchy::Hierarchy() {
    HIERARCY_WIDTH = 250;
    HIERARCY_HEIGHT = gameEngine->getHeight();
}

void Hierarchy::Show() {
    ImGui::SetNextWindowPos(ImVec2(0, 18));
    ImGui::SetNextWindowSize(ImVec2(HIERARCY_WIDTH, HIERARCY_HEIGHT), ImGuiCond_FirstUseEver);
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    for (auto& obj : gameEngine->GOS) {
        if (ImGui::MenuItem(obj->name.c_str())) {

        }
    }
    
    ImGui::End();
}