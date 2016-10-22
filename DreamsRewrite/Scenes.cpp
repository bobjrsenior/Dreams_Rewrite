#include "Scenes.h"

Scene* activeScene = NULL;

void deloadScene(Scene* scene) {
	scene->deloadGameObjects();
}

void loadScene(Scene* scene) {
	if (activeScene != NULL) {
		deloadScene(activeScene);
	}

	scene->loadGameObjects();
	activeScene = scene;
}

void luaErrorHandler(std::string message) {
	return;
}