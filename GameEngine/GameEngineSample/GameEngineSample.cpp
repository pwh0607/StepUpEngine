#include <stdio.h>
#include "SDL.h"
#include "SDL_ttf.h"

#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_ttf.lib")

SDL_Window* window;
SDL_Renderer* renderer;

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;
const int SIDEBAR_WIDTH = 300;

class Anchor {

};

void setAnchor() {

}

void make_sidebar() {
    // 사이드 바 만들기
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_Rect sideBar = { WINDOW_WIDTH - SIDEBAR_WIDTH,0,SIDEBAR_WIDTH, WINDOW_HEIGHT };
    SDL_RenderFillRect(renderer, &sideBar);

    //사이드 바 상단
    //오브젝트 이름 넣기
    const int TAGWIDTH = 50;
    const int TAGHEIGHT = 20;
    SDL_SetRenderDrawColor(renderer, 190, 190, 190, 255);
    SDL_Rect objNameTag = { WINDOW_WIDTH - SIDEBAR_WIDTH, 0, SIDEBAR_WIDTH, WINDOW_HEIGHT };
    SDL_RenderFillRect(renderer, &sideBar);

}

int SDL_main(int argc, char* argv[])
{
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
            

        // 화면 업데이트
        SDL_RenderPresent(renderer);
    }

    // 자원 해제
    SDL_DestroyWindow(window);
    SDL_Quit();
}