#include <iostream>
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
                //���콺 ���� ��������
                /*
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                //�ش� ������ ��ġ�� position ����
                Rect rect(mouseX, mouseY, 0.0f);
                */
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

ObjUI::ObjUI():pos({0.0f,0.0f,0.0f}), rot({ 0.0f,0.0f,0.0f }), scale({ 1.0f,1.0f,1.0f }) {

}

void ObjUI::Set_Object(GameObject *obj) {
    this->obj = obj;
}

void ObjUI::Set_Name(string name) {
    
}
void ObjUI::Set_Position(float x, float y, float z){
    pos.x = x;
    pos.y = y;
    pos.z = z;
}

void ObjUI::Set_Rotation(float x, float y, float z) {
    rot.x = x;
    rot.y = y;
    rot.z = z;
}

void ObjUI::Set_Scale(float x, float y, float z) {
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

void ObjUI::Show() {
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

    if (ImGui::BeginPopup("MyPopup")) {
        ImGui::Text("This is a popup!");
        ImGui::EndPopup();
    }
    ImGui::End();
}

void ObjUI::Reset() {
    pos = { 0.0,0.0,0.0 };
    rot = { 0.0,0.0,0.0 };
    scale = { 0.0,0.0,0.0 };
}