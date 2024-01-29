#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SystemUI.h"

using namespace std;

class Metrix {
public:
    vector<vector<double>> metrix;

    Metrix(vector<vector<double>> metrix) {
        this->metrix = metrix;
    }
};

//앵커들
const ANCHOR eastTOP = ANCHOR(WINDOW_WIDTH, 0);
const ANCHOR eastBOTTOM = ANCHOR(WINDOW_WIDTH, WINDOW_HEIGHT);
const ANCHOR westTOP = ANCHOR(0, 0);
const ANCHOR westBOTTOM = ANCHOR(0, WINDOW_HEIGHT);


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

    //TTF 초기화
    if (TTF_Init() == -1) {
        printf("TTF 초기화 실패: %s\n", TTF_GetError());
        return false;
    }

    //렌더 세팅
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

            for (auto& in : ins) {
                in.handleEvent(e);
            }
        }
        
        // 화면 지우기
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // 보조 바 그리기
        make_Sidebar();
        make_Bottombar();

        for (auto& in : ins) {
            in.render();
        }

        // 화면 업데이트
        SDL_RenderPresent(renderer);

        SDL_Delay(8);
    }

    // 자원 해제
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}