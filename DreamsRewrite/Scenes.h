#pragma once
#ifndef SCENE_START
#define SCENE_START

#ifndef LUA_STATE_START
#include "LuaState.h"
#endif LUA_STATE_START

#include "GameObject.h"

class Scene {
public:

private:
	std::string filename;
	std::string path;
	std::string identifier;
	std::vector<GameObject> gameobjects;
	


public:
	Scene(std::string path, std::string filename, std::string identifier) : path(path), filename(filename), identifier(identifier) {}

	~Scene() {
		deloadGameObjects();
	}

	GameObject getGameObject(int index) {
		if (index >= 0 && index < gameobjects.size()) {
			return gameobjects[index];
		}
	}

	void deloadGameObject(int index) {

	}

	void deloadGameObjects() {
		while (gameobjects.size()) {
			gameobjects.pop_back();
		}
	}

	void loadGameObjects() {
		lua.script_file(path + filename);

		sol::optional<sol::table> gameOjectTblOpt = lua["Scene"]["GameObjects"];
		if (gameOjectTblOpt == sol::nullopt) {
			printf("Error Loading config file");
			return;
		}
		else {
			sol::table gameObjectTbl = gameOjectTblOpt.value();
			if (gameObjectTbl.size() == 0) {
				printf("Not enough scenes\n");
				return;
			}
			
			for (int i = 1; i <= gameObjectTbl.size(); ++i) {
				
			}
			
		}
		
	}

private:


};

extern Scene *activeScene;

void deloadScene(Scene* scene);

void loadScene(Scene* scene);


#endif // !SCENE_START

