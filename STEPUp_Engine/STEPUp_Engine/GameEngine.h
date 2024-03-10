#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include<vector>
#include "GameObject.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL.h>
using namespace std;

class GameEngine
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	static GameEngine* instance;

	//윈도우 UI
	const int WINDOW_WIDTH = 1440;
	const int WINDOW_HEIGHT = 740;
	
	//생성자.
	GameEngine();
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator=(const GameEngine&) = delete;
public:
	//하위 클래스 업캐스팅으로 포인터로 추가하기.
	static GameEngine* getInstance();

	vector<GameObject*> GOS;

	void init_SDL();
	void init_IMGUI();
	void Start();

	void setViewPort();

	int getWidth();
	int getHeight();

	//SDL_RenderSetViewport
};

#endif