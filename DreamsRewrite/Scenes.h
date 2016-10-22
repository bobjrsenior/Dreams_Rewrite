#pragma once
#ifndef SCENE_START
#define SCENE_START

#ifndef LUA_STATE_START
#include "LuaState.h"
#endif LUA_STATE_START

#include "GameObject.h"
#include "IrrItems.h"
#include <iostream>

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

	inline GameObject getGameObject(int index) {
		if (index >= 0 && index < gameobjects.size()) {
			return gameobjects[index];
		}
		return GameObject();
	}

	inline void setGameObject(int index, GameObject obj) {
		if (index >= 0 && index < gameobjects.size()) {
			gameobjects[index] = obj;
		}
	}

	inline int getNumGameObjects() {
		return (int) gameobjects.size();
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
			std::cout << gameObjectTbl.size() << std::endl;
			for (int i = 1; i <= gameObjectTbl.size(); ++i) {
				sol::table objTable = gameObjectTbl[i];

				irr::core::vector2df position;
				irr::core::rect<irr::s32> imagePosition;

				bool isStatic;
				bool isCollidable;
				std::string tag;
				std::string updateScript;
				std::string spritePath;

				position.X = objTable["PositionX"].get_or<float>(0);
				position.Y = objTable["PositionY"].get_or<float>(0);
				sol::optional<int> isStaticOpt = objTable["IsStatic"];
				if (isStaticOpt == sol::nullopt) {
					isStatic = false;
				}
				else {
					isStatic = (isStaticOpt.value() != 0);
				}

				sol::optional<int> isCollidableOpt = objTable["IsCollidable"];
				if (isCollidableOpt == sol::nullopt) {
					isCollidable = false;
				}
				else {
					isCollidable = (isCollidableOpt.value() != 0);
				}

				tag = objTable["Tag"].get_or<std::string>("");

				updateScript = objTable["Script"].get_or<std::string>("");

				spritePath = objTable["SpritePath"].get_or<std::string>("");

				sol::optional<int> spriteStartXOpt = objTable["SpriteStartX"];
				if (spriteStartXOpt == sol::nullopt) {
					imagePosition.UpperLeftCorner.X = 0;
				}
				else {
					imagePosition.UpperLeftCorner.X = spriteStartXOpt.value();
				}

				sol::optional<int> spriteStartYOpt = objTable["SpriteStartY"];
				if (spriteStartYOpt == sol::nullopt) {
					imagePosition.UpperLeftCorner.Y = 0;
				}
				else {
					imagePosition.UpperLeftCorner.Y = spriteStartYOpt.value();
				}

				sol::optional<int> spriteWidthOpt = objTable["SpriteWidth"];
				if (spriteWidthOpt == sol::nullopt) {
					imagePosition.LowerRightCorner.X = imagePosition.UpperLeftCorner.X + 0;
				}
				else {
					imagePosition.LowerRightCorner.X = imagePosition.UpperLeftCorner.X + spriteWidthOpt.value();
				}

				sol::optional<int> spriteHeightOpt = objTable["SpriteHeight"];
				if (spriteHeightOpt == sol::nullopt) {
					imagePosition.LowerRightCorner.Y = imagePosition.UpperLeftCorner.Y + 0;
				}
				else {
					imagePosition.LowerRightCorner.Y = imagePosition.UpperLeftCorner.Y + spriteHeightOpt.value();
				}

				GameObject obj = GameObject();
				obj.setPosition(position);
				obj.setImagePosition(imagePosition);
				obj.setObjectScript(path + updateScript);
				obj.setIsStatic(isStatic);
				obj.setIsCollidable(isCollidable);

				std::string fullImagePath = path + spritePath;

				irr::video::ITexture* images = driver->getTexture(fullImagePath.c_str());

				obj.setImage(images);
				/*
				if (updateScript != "") {
					lua.script_file(path + updateScript);

					sol::protected_function updateFunction = lua["update"];

					obj.setUpdateFunction(updateFunction);
				}
				*/
				gameobjects.push_back(obj);

			}
			
		}
		
	}

private:


};

extern Scene *activeScene;

void deloadScene(Scene* scene);

void loadScene(Scene* scene);


#endif // !SCENE_START
