#ifndef UI_H
#define UI_H

#include "GameObject.h"
#include "Vector.h"

class UI
{
private:

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
	void Set_Object(GameObject *obj);

	//������ ������ ��ü�� �̵��Ҷ����� �����ϱ� ����.
	void Set_Name(string name);
	void Set_Position(float x, float y, float z);
	void Set_Rotation(float x, float y, float z);
	void Set_Scale(float x, float y, float z);
	void Reset();
};

#endif