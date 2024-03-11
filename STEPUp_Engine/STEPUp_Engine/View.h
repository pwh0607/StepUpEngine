#ifndef VIEW_H
#define VIEW_H

#include <SDL.h>
#include "Vector.h"

class View
{
protected:
	
	SDL_Rect view;
public:
	View();
	View(int width, int height);
	void show(SDL_Renderer* renderer);
};

class GameView : public View {
public:
	GameView();
	GameView(int w, int h);
};

class DevelopmentView : public View{
public:
	DevelopmentView();
	DevelopmentView(int w, int h);
};

#endif