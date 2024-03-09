#include "GameObject.h"

GameObject::GameObject() : pos( 0.0f,0.0f,0.0f ), rot( 0.0f,0.0f,0.0f ), scale( 1.0f,1.0f,1.0f ) {
	name = "Empty Name";
}

GameObject::GameObject(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz) : pos(px, py, pz), rot( rx, ry, rz ), scale( sx, sy, sz ), name("GameObject") {
}

Rect::Rect() {
	//기본값은 80인 정사각형.
	width = 80;
	height = 80;
}

Rect::Rect(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz) : GameObject(px, py, pz, rx, ry, rz, sx, sy, sz) {
	width = 80 * sx;
	height = 80 * sy;
}

void Rect::Render(SDL_Renderer* renderer) {
	width *= scale.x;
	height *= scale.y;
	SDL_Rect rect = { pos.x,pos.y, width, height };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 색상 설정 (빨간색)
	SDL_RenderFillRect(renderer, &rect); // 사각형 그리기
}

bool Rect::isClicked() {
	return false;
}
Triangle::Triangle(){
	v1 = { 10,10 };
	v2 = { 10,10 };
	v3 = { 10,10 };
}

Triangle::Triangle(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz):GameObject(px, py, pz, rx, ry, rz, sx, sy, sz) {
	v1 = { 10,10 };
	v2 = { 10,10 };
	v3 = { 10,10 };
}
void Triangle::Render(SDL_Renderer* renderer) {

}
bool Triangle::isClicked() {
		return false;
}