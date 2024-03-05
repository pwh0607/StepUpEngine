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
/*
class ObjUI : UI {
private:
	//ui 크기
	const int OBJECTUI_WIDTH = 340;
	const int OBJECTUI_HEIGHT = 500;
	//오브젝트 이름
	string objName;

	//해당 오브젝트 Transition
	static Position pos;
	static Rotation rot;
	static Scale scale;
public:
	ObjUI(GameObject obj);
	void Show() override;
	void Set_Position(float x, float y, float z);
	void Set_Rotation(float x, float y, float z);
	void Set_Scale(float x, float y, float z);
	void Set_Name(const string& name);
};
*/
#endif