#include "Scene.h"

void Scene::add_Obj(GameObject obj) {
	sceneObj.push_back(obj);
	cout << "������Ʈ ����!!" << endl;
}

void Scene::delete_Obj(GameObject obj) {
	//ã��
	int idx = -1;
	for (int i = 0; i < sceneObj.size(); i++) {
		if (obj.name == sceneObj[i].name) {
			idx = i;
		}
	}
	//��ã���� ����...
	if (idx == -1) return;

	sceneObj.erase(sceneObj.begin() + idx);

	cout << "���ſϷ�!!" << endl;
}