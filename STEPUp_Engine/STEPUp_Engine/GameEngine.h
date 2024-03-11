#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <vector>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL.h>

#include "GameObject.h"
#include "View.h"

using namespace std;

class GameEngine
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	//singleton
	static GameEngine* instance;

	//������ UI
	const int WINDOW_WIDTH = 1440;
	const int WINDOW_HEIGHT = 740;
	
	GameView *gameView;
	DevelopmentView *developmentView;

	View *currentView;

	//���콺 Ŀ�� �̹��� �����.
	bool pressedAlt;

	//������.
	GameEngine();
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator=(const GameEngine&) = delete;
public:
	//���� Ŭ���� ��ĳ�������� �����ͷ� �߰��ϱ�.
	static GameEngine* getInstance();

	vector<GameObject*> GOS;

	void init_SDL();
	void init_IMGUI();
	void Start();

	void setViewPort();
	void setCursor();

	int getWidth();
	int getHeight();

	//SDL_RenderSetViewport
};

#endif