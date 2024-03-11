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

//�˾�â
class PopUp : UI {
private:
public:
	PopUp();
	bool isClicked;
	void Show() override;
};

class ObjUI : UI {
private:
	//ui ũ��
	const int OBJECTUI_WIDTH = 340;
	const int OBJECTUI_HEIGHT = 500;
	
	//������Ʈ �̸�
	GameObject *obj;

	//�ش� ������Ʈ Transition
	Position pos;
	Rotation rot;
	Scale scale;
	
public:
	ObjUI();
	void Show() override;
	void setObject(GameObject *obj);

	//������ ������ ��ü�� �̵��Ҷ����� �����ϱ� ����.
	void setName(string name);
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);
	void Reset();
	void setColor();
};

//������Ʈ ���� ���� �� ����
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