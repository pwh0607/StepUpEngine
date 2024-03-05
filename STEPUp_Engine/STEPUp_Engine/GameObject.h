#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include "imgui.h"
#include "Vector.h"

#include <iostream>

using namespace std;

class GameObject
{
public:	
	//ObjUI ui;
	string name;			//오브젝트 이름

	Position pos;
	Rotation rot;
	Scale scale;

	//원 오브젝트 테스트용.
	int radius;
	GameObject();

	void Render(SDL_Renderer* renderer);
};
#endif