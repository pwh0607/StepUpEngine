#include "View.h"
#include <SDL.h>

View::View() {
	view = { 250,0,100,100 };
}

View :: View(int w, int h){
	view = { 250,0,w-250,h };
}

void View::show(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
	SDL_RenderFillRect(renderer, &view);
}

GameView::GameView() {

}

GameView::GameView(int w, int h) :View(w, h){ }

DevelopmentView::DevelopmentView() { }

DevelopmentView::DevelopmentView(int w, int h) :View(w, h) { }