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
	string name;			//������Ʈ �̸�

	Position pos;
	Rotation rot;
	Scale scale;

	//�� ������Ʈ �׽�Ʈ��.
	int radius;
	GameObject();

	void Render(SDL_Renderer* renderer);
};
#endif