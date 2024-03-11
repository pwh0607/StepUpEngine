#ifndef UI_H
#define UI_H

#include "GameEngine.h"
#include "GameObject.h"
#include "Vector.h"

class UI
{
private:
protected:
	GameEngine* gameEngine = GameEngine::getInstance();
public:
	virtual void Show() = 0;
};

class MainMenuBar : UI{
private:
public:
	void Show() override;
};

//팝업창
class PopUp : UI {
private:
public:
	PopUp();
	bool isClicked;
	void Show() override;
};

class ObjUI : UI {
private:
	//ui 크기
	const int OBJECTUI_WIDTH = 340;
	const int OBJECTUI_HEIGHT = 500;
	
	//오브젝트 이름
	GameObject *obj;

	//해당 오브젝트 Transition
	Position pos;
	Rotation rot;
	Scale scale;
	
public:
	ObjUI();
	void Show() override;
	void setObject(GameObject *obj);

	//프레임 단위로 개체가 이동할때마다 갱신하기 위해.
	void setName(string name);
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);
	void Reset();
	void setColor();
};

//오브젝트 계층 구조 및 구성
class Hierarchy : UI{
private:
	int HIERARCY_WIDTH;
	int HIERARCY_HEIGHT;

public:
	Hierarchy();
	void Show() override;
};

class TestingUI :UI {
private:
	int width;
	int height;
public:
	TestingUI();
	void Show() override;
};
#endif