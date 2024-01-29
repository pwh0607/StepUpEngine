#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <SDL_ttf.h>
using namespace std;

//시스템
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Surface* surface;

//Scene 화면
SDL_Renderer* SceneRenderer;

extern const int WINDOW_WIDTH = 1440;
extern const int WINDOW_HEIGHT = 840;
extern const int SIDEBAR_WIDTH = 300;

void make_Text(SDL_Rect textBox, const char* text, int fontSize);

class ANCHOR {
public:
    int x;
    int y;
    ANCHOR(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class PANEL {
private:
    int x, y, w, h;
    SDL_Rect frame;
    SDL_Rect header;
public:
    PANEL(int x, int y, int w, int h) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        frame = { x,y,w,h };
        header = { x,y,w,35 };
    }
    //헤더는 선택 사항
    void drawPanel() {
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderFillRect(renderer, &frame);

        //테두리
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderDrawRect(renderer, &frame);

        SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
        SDL_RenderFillRect(renderer, &header);
    }

    void setTitle(const char* title) {
        SDL_Rect textBox = { x + 7, y, 100, 30 };
        make_Text(textBox, title, 50);
    }
};

class InputField {
private:
    TTF_Font* font_;
    int x_;
    int y_;
    int width_;
    int height_;
    string text_;
    int cursorPos_;
    bool isEditing_;

public:
    InputField(TTF_Font* font, int x, int y, int width, int height)
        : font_(font), x_(x), y_(y), width_(width), height_(height), isEditing_(false) {
        text_ = " ";
        cursorPos_ = 0;

        // 텍스트 박스 그리기
        SDL_Rect textBoxRect = { x_, y_, width_, height_ };
        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
        SDL_RenderFillRect(renderer, &textBoxRect);
    }
    void handleEvent(SDL_Event& e) {
        // 마우스 클릭으로 텍스트 박스 선택/해제
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;

            if (mouseX >= x_ && mouseX <= x_ + width_ && mouseY >= y_ && mouseY <= y_ + height_) {
                isEditing_ = true;
            }
            else {
                isEditing_ = false;
            }
        }

        // 키보드 입력 처리
        if (isEditing_ && e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_BACKSPACE && text_.length() > 0 && cursorPos_ > 0) {
                // Backspace 키를 누르면 문자 삭제
                text_.erase(cursorPos_ - 1, 1);
                cursorPos_--;
            }
            else if (e.key.keysym.sym == SDLK_LEFT && cursorPos_ > 0) {
                // 왼쪽 화살표 키를 누르면 커서 위치 이동
                cursorPos_--;
            }
            else if (e.key.keysym.sym == SDLK_RIGHT && cursorPos_ < static_cast<int>(text_.length())) {
                // 오른쪽 화살표 키를 누르면 커서 위치 이동
                cursorPos_++;
            }
        }

        // 유니코드 문자 입력 처리
        if (isEditing_ && e.type == SDL_TEXTINPUT) {
            text_.insert(cursorPos_, e.text.text);
            cursorPos_++;
        }
    }

    void render() {

        // 텍스트 렌더링
        SDL_Surface* textSurface = TTF_RenderText_Solid(font_, text_.c_str(), { 0, 0, 0, 255 });
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect renderQuad = { x_, y_ + (height_ - textSurface->h) / 2, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

        // 커서 그리기
        if (isEditing_) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawLine(renderer, x_ + renderQuad.w, y_ + renderQuad.y, x_ + renderQuad.w, y_ + renderQuad.y + renderQuad.h);
        }
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    string getText() {
        return text_;
    }
};

//이벤트 루프용 벡터
extern vector<InputField> ins;

void make_Text(SDL_Rect textBox, const char* text, int fontSize) {
    TTF_Font* font = TTF_OpenFont("D:\\Project\\GameEngine\\Font\\NotoSansKR\\NotoSansKR-Black.ttf", fontSize);
    if (font == NULL)
    {
        printf("폰트 가져오기 실패 : %s\n", TTF_GetError());
        return;
    }

    SDL_Color textColor = { 0,0,0 };        //검정색
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);

    if (textSurface == NULL) {
        printf("텍스트 렌더링 실패: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_RenderCopy(renderer, textTexture, NULL, &textBox);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

void make_InputField(int x, int y, int w, int h) {
    //inputfield 전용 폰트.
    TTF_Font* font = TTF_OpenFont("D:\\Project\\GameEngine\\Font\\NotoSansKR\\NotoSansKR-Black.ttf", 20);
    InputField in = InputField(font, x, y, w, h);
    ins.push_back(in);
}

//하위 계층 요소가 필요하므로 따로 만들기.
int make_TransformPanel(int x, int y, int w, int h) {

    PANEL p = PANEL(x, y, w, h);
    p.drawPanel();
    p.setTitle("Transform");

    //position part
    SDL_Rect textBox1 = { x + 10, y + 40, 60, 30 };
    make_Text(textBox1, "Position", 30);

    SDL_Rect boxX = { x + 92, y + 42.5, 15, 28 };
    make_Text(boxX, "X", 100);

    SDL_Rect boxY = { x + 162, y + 42.5, 15, 28 };
    make_Text(boxY, "Y", 100);

    SDL_Rect boxZ = { x + 250 - 18, y + 42.5, 15, 28 };
    make_Text(boxZ, "Z", 100);

    make_InputField(x + 110, y + 45, 40, 25);
    make_InputField(x + 180, y + 45, 40, 25);
    make_InputField(x + 250, y + 45, 40, 25);

    //rotation part
    SDL_Rect textBox2 = { x + 10, y + 40 + 45, 60, 30 };
    make_Text(textBox2, "Rotation", 30);

    SDL_Rect boxX2 = { x + 92, y + 42.5 + 45, 15, 28 };
    make_Text(boxX2, "X", 100);

    SDL_Rect boxY2 = { x + 162, y + 42.5 + 45, 15, 28 };
    make_Text(boxY2, "Y", 100);

    SDL_Rect boxZ2 = { x + 250 - 18, y + 42.5 + 45, 15, 28 };
    make_Text(boxZ2, "Z", 100);

    make_InputField(x + 110, y + 45 + 45, 40, 25);
    make_InputField(x + 180, y + 45 + 45, 40, 25);
    make_InputField(x + 250, y + 45 + 45, 40, 25);

    //scale part
    SDL_Rect textBox3 = { x + 10, y + 40 + 90, 50, 30 };
    make_Text(textBox3, "Scale", 30);

    SDL_Rect boxX3 = { x + 92, y + 42.5 + 90, 15, 28 };
    make_Text(boxX3, "X", 100);

    SDL_Rect boxY3 = { x + 162, y + 42.5 + 90, 15, 28 };
    make_Text(boxY3, "Y", 100);

    SDL_Rect boxZ3 = { x + 250 - 18, y + 42.5 + 90, 15, 28 };
    make_Text(boxZ3, "Z", 100);

    make_InputField(x + 110, y + 45 + 90, 40, 25);
    make_InputField(x + 180, y + 45 + 90, 40, 25);
    make_InputField(x + 250, y + 45 + 90, 40, 25);

    return 1;
}

int make_ControllerPanel(int x, int y, int w, int h) {
    PANEL p = PANEL(x, y, w, h);
    p.drawPanel();
    p.setTitle("Controller");
    return 1;
}

const int BOTTOMBAR_WIDTH = WINDOW_WIDTH - SIDEBAR_WIDTH;
const int BOTTOMBAR_HEIGHT = 270;

//하단 파일 띄우기 함수
void make_Bottombar() {
    SDL_Rect bottomBar = { 0, WINDOW_HEIGHT - BOTTOMBAR_HEIGHT, BOTTOMBAR_WIDTH, BOTTOMBAR_HEIGHT };
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    SDL_RenderFillRect(renderer, &bottomBar);
}

void make_Sidebar() {
    SDL_Rect sideBar = { WINDOW_WIDTH - SIDEBAR_WIDTH,0, SIDEBAR_WIDTH, WINDOW_HEIGHT };
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &sideBar);

    //사이드 바 상단
    //오브젝트 이름 태그
    const int TAGWIDTH = 185;
    const int TAGHEIGHT = 60;

    //우측 상단으로 앵커 세팅
    SDL_Rect objNameTag = { eastTOP.x - (TAGWIDTH * 1.15), eastTOP.y + (TAGHEIGHT / 1.9),TAGWIDTH, TAGHEIGHT };
    SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
    SDL_RenderFillRect(renderer, &objNameTag);

    //하위 프레임 만들기
    make_TransformPanel(WINDOW_WIDTH - SIDEBAR_WIDTH, 120, SIDEBAR_WIDTH, 170);
    make_ControllerPanel(WINDOW_WIDTH - SIDEBAR_WIDTH, 120 + 170, SIDEBAR_WIDTH, 170);
}

#endif