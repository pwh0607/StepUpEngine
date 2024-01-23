#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

//시스템
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surface;

//Scene 화면
SDL_Renderer* SceneRenderer;

const int WINDOW_WIDTH = 1440;
const int WINDOW_HEIGHT = 840;
const int SIDEBAR_WIDTH = 300;

typedef struct ANCHOR {
    int x;
    int y;
} ANCHOR;

class TextBox {
    int x, y;
    int w, h;
    bool isEdit;
    TTF_Font* font;

public:
    TextBox() {
         
    }

    TextBox(TTF_Font* font, int x, int y, int w, int h) {
        this->font = font;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    //텍스트 박스 클릭시...
    void onClickEvent(SDL_Event& e) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            //클릭 지점
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            
        }
    }
};

//앵커들
ANCHOR eastTOP = { WINDOW_WIDTH, 0 };
ANCHOR eastBOTTOM = { WINDOW_WIDTH, WINDOW_HEIGHT };
ANCHOR westTOP = { 0, 0 };
ANCHOR westBOTTOM = { 0, WINDOW_HEIGHT };

int init_System(void) {
    //환경 설정
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 초기화 실패 : %s\n", SDL_GetError());
        return 1;
    }

    //윈도우 창 세팅
    window = SDL_CreateWindow("StepUpEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == nullptr) {
        printf("SDL 창 생성 실패: %s\n", SDL_GetError());
        return 1;
    }
    //렌더 세팅
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void init_SceneSystem(void) {
    //Scene 화면용 렌더러
    SceneRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Scene 화면 크기
    //width : window_Width - SidebarWidth
}

void make_Text(SDL_Rect textBox, const char *text, int fontSize) {
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

//계층 패널 만들기
void make_panel(int x, int y, int w, int h, const char * headerText) {
    SDL_Rect frame;         //프레임 틀 (헤더와 동일)
    SDL_Rect header;        //프레임 헤더

    //frame
    frame = { x, y, w, h };

    //채우기
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
    SDL_RenderFillRect(renderer, &frame);

    //테두리
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderDrawRect(renderer, &frame);

    //header
    header = { frame.x, frame.y, SIDEBAR_WIDTH, 35 };
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
    SDL_RenderFillRect(renderer, &header);

    SDL_Rect textBox = { x + 7, y, 100, 30 };
    
    make_Text(textBox, headerText, 50);
}

int make_TransformPanel(int x, int y, int w, int h) {
    make_panel(x, y, w, h, "Transform");

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

void make_sidebar() {
    // 사이드 바 만들기
    const int SIDEBAR_WIDTH = 300;
int make_ControllerPanel(int x, int y, int w, int h) {
    make_panel(x, y, w, h, "Controller");

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
    SDL_Rect sideBar = { WINDOW_WIDTH - SIDEBAR_WIDTH,0, SIDEBAR_WIDTH, WINDOW_HEIGHT };
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &sideBar);

    //사이드 바 상단
    //오브젝트 이름 태그
    const int TAGWIDTH = 185;
    const int TAGHEIGHT = 60;

    //우측 상단으로 앵커 세팅
    SDL_Rect objNameTag = { eastTOP.x - (TAGWIDTH * 1.15), eastTOP.y + (TAGHEIGHT / 1.9),TAGWIDTH, TAGHEIGHT};
    SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
    SDL_RenderFillRect(renderer, &objNameTag);

    //하위 프레임 만들기
    make_panel();

}

int SDL_main(int argc, char* argv[])
{
    init_System();
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        // 이벤트 처리
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // 화면 지우기
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // 화면 그리기
        make_sidebar();

        // 화면 업데이트
        SDL_RenderPresent(renderer);
    }

    // 자원 해제
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}