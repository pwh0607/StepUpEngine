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
	void Set_Object(GameObject *obj);

	//프레임 단위로 개체가 이동할때마다 갱신하기 위해.
	void Set_Name(string name);
	void Set_Position(float x, float y, float z);
	void Set_Rotation(float x, float y, float z);
	void Set_Scale(float x, float y, float z);
	void Reset();
};

#endif