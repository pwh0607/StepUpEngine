#include "Scene.h"

void Scene::add_Obj(GameObject obj) {
	sceneObj.push_back(obj);
	cout << "오브젝트 생성!!" << endl;
}

void Scene::delete_Obj(GameObject obj) {
	//찾기
	int idx = -1;
	for (int i = 0; i < sceneObj.size(); i++) {
		if (obj.name == sceneObj[i].name) {
			idx = i;
		}
	}
	//못찾으면 무시...
	if (idx == -1) return;

	sceneObj.erase(sceneObj.begin() + idx);

	cout << "제거완료!!" << endl;
}