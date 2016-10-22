#pragma once
#include <irrlicht.h>
#include <string>
#include "sol.hpp"

class GameObject {
public:

private:
	irr::core::vector2df position;
	std::string objectScript;
	sol::protected_function updateFunction;
	irr::video::ITexture* image;
	irr::core::rect<irr::s32> imagePosition;



public:
	GameObject() {}

	irr::core::vector2df getPosition() {
		return position;
	}

	void setPosition(irr::core::vector2df newPosition) {
		position.X = newPosition.X;
		position.Y = newPosition.Y;
	}

	void setPosition(float x, float y) {
		position.X = x;
		position.Y = y;
	}

	void setObjectScript(std::string filepath) {
		objectScript = filepath;
	}

	std::string getObjectScript() {
		return objectScript;
	}

	void setUpdateFunction(sol::protected_function function) {
		updateFunction = function;
	}

	sol::protected_function getUpdateFunction() {
		return updateFunction;
	}

	void setImage(irr::video::ITexture* imagePtr) {
		image = imagePtr;
	}

	irr::video::ITexture* getImage() {
		return image;
	}

	void setImagePosition(irr::core::rect<irr::s32> imagePos) {
		imagePosition = imagePos;
	}

	irr::core::rect<irr::s32> getImagePosition() {
		return imagePosition;
	}


private:


};