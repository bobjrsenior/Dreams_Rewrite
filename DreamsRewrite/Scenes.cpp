#include "Scenes.h"
#include "Config.h"

Scene* activeScene = NULL;
int activeSceneIndex = -1;

void deloadScene(Scene* scene) {
	scene->deloadGameObjects();
	scene->deloadUITextItems();
}

void loadScene(Scene* scene, int sceneIndex) {
	if (activeScene != NULL) {
		deloadScene(activeScene);
	}

	scene->loadGameObjects();
	activeScene = scene;
	activeSceneIndex = sceneIndex;
}

void luaErrorHandler(std::string message) {
	return;
}