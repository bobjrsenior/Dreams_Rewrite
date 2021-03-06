#pragma once
#include <irrlicht.h>
#include <string>

#ifndef LUA_SOL
#include "sol.hpp"
#define LUA_SOL 1
#endif // !LUA_SOL


class GameObject {
public:
	bool isStatic = false;
	bool canCollide = true;
	bool hasUpdateScript = false;

private:
	// Where the object is in pixels (Upper left corner)
	irr::core::vector2df position;
	// The path/name of the script attached to this object
	std::string objectScript;
	// Update function associated with this script
	sol::protected_function updateFunction;
	// Image/Sprite this object uses
	irr::video::ITexture* image;
	// Where in the image the sprite is
	irr::core::rect<irr::s32> imagePosition;
	std::string tag;



public:
	GameObject() {}

	~GameObject() {
		
	}

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

	std::string getTag() {
		return tag;
	}

	void setTag(std::string newTag) {
		tag = newTag;
	}

	void setObjectScript(std::string filepath) {
		objectScript = filepath;
	}

	void setIsStatic(bool value) {
		isStatic = value;
	}

	void setIsCollidable(bool value) {
		canCollide = value;
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

	bool isColliding(GameObject other) {
		irr::f32 xDiff = (irr::f32) abs(other.getPosition().X - position.X);
		irr::f32 yDiff = (irr::f32) abs(other.getPosition().Y - position.Y);

		irr::f32 maxXDiff = (irr::f32) (0.5f * (imagePosition.getWidth() + other.getImagePosition().getWidth()));
		irr::f32 maxYDiff = (irr::f32) (0.5f * (imagePosition.getHeight() + other.getImagePosition().getHeight()));

		irr::f32 minXDiff = -maxXDiff;
		irr::f32 minYDiff = -maxYDiff;

		if (xDiff > minXDiff && xDiff < maxXDiff && yDiff > minYDiff && yDiff < maxYDiff) {
			return true;
		}
		return false;
	}

	irr::core::vector2df collisionDirection(GameObject other) {
		irr::core::vector2df dir;
		dir.X = other.getPosition().X - position.X;
		dir.Y = other.getPosition().Y - position.Y;
		return dir;
	}

	irr::core::vector2df collisionDirectionNormalized(GameObject other) {
		irr::core::vector2df dir;
		dir.X = other.getPosition().X - position.X;
		dir.Y = other.getPosition().Y - position.Y;
		dir.normalize();
		return dir;
	}



private:


};