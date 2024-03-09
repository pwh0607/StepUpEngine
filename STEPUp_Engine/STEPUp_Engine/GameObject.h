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
	string name;			//오브젝트 이름
	
	//Transform
	Position pos;
	Rotation rot;
	Scale scale;

	bool clicked = false;

	//property
	virtual bool isClicked() { return false; }

	//method
	GameObject();
	GameObject(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
	virtual void Render(SDL_Renderer* renderer) { }
};

//사각형.
class Rect : public GameObject {
	int width, height;
public :
	Rect();
	Rect(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
	bool isClicked() override;
	void Render(SDL_Renderer* renderer) override;
};

struct vertex { int x; int y; };

//삼각형
class Triangle : public GameObject {
	vertex v1, v2, v3;
public:
	Triangle();
	Triangle(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
	bool isClicked() override;
	void Render(SDL_Renderer* renderer) override;
};

//이미지
/*
class Resource : public GameObject {
public:
	Resource();
	bool isClicked() override; 
	void Render(SDL_Renderer* renderer) override;
};*/
#endif