#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "GameObject.h"

class Scene
{
private:
	//���� ������Ʈ��
	vector<GameObject> sceneObj;
public:
	void add_Obj(GameObject obj);
	void delete_Obj(GameObject obj);
};

#endif