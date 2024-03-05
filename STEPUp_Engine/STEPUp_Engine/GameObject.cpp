#include "GameObject.h"

GameObject::GameObject() : pos(0.0, 0.0, 0.0), rot(0.0, 0.0, 0.0), scale(1.0, 1.0, 1.0){
	name = "Empty Name";
	radius = 20;
}

void GameObject::Render(SDL_Renderer* renderer) {
	//원 오브젝트 테스트용.
	SDL_SetRenderDrawColor(renderer, 1, 1, 1, 255);
	for (int x = -radius; x <= radius; x++) {
		int height = (int)sqrt(radius * radius - x * x);
		SDL_RenderDrawLine(renderer, pos.x + radius + x, pos.y + radius - height, pos.x + radius + x, pos.y + radius + height);
	}
}