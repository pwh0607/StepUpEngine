#include <iostream>
#include <SDL.h>

class GameEngine {
public:
    GameEngine() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        window = SDL_CreateWindow("Simple Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

        if (!window) {
            std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (!renderer) {
            std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    ~GameEngine() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void run() {
        bool quit = false;
        SDL_Event e;

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            // 게임 로직 업데이트

            // 그래픽 렌더링
            SDL_RenderClear(renderer);
            // 여기에서 게임 객체를 그리는 로직을 추가할 수 있습니다.
            SDL_RenderPresent(renderer);

            // 프레임 속도 제어
            SDL_Delay(16); // 60fps로 설정
        }
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

int main(int argc, char* args[]) {
    GameEngine game;
    game.run();

    return 0;
}