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

	bool isColliding(GameObject other) {
		irr::f32 xDiff = (irr::f32) abs(other.getPosition().X - position.X);
		irr::f32 yDiff = (irr::f32) abs(other.getPosition().Y - position.Y);

		irr::f32 minXDiff = (irr::f32) (-other.getImagePosition().getWidth());
		irr::f32 minYDiff = (irr::f32) (-other.getImagePosition().getHeight());

		irr::f32 maxXDiff = (irr::f32) (imagePosition.getWidth());
		irr::f32 maxYDiff = (irr::f32) (imagePosition.getHeight());

		if (xDiff > minXDiff && xDiff < maxXDiff && yDiff > minYDiff && yDiff < maxYDiff) {
			return true;
		}
		return false;
	}

	irr::core::vector2df collisionDirection(GameObject other) {
		irr::core::vector2di center = getImagePosition().getCenter();
		irr::core::vector2di otherCenter = other.getImagePosition().getCenter();
		irr::core::vector2df dir;
		dir.X = (other.getPosition().X + otherCenter.X) - (position.X + center.X);
		dir.Y = (other.getPosition().Y + otherCenter.Y) - (position.Y + center.Y);
		return dir;
	}

	irr::core::vector2df collisionDirectionNormalized(GameObject other) {
		irr::core::vector2di center = getImagePosition().getCenter();
		irr::core::vector2di otherCenter = other.getImagePosition().getCenter();
		irr::core::vector2df dir;
		dir.X = (other.getPosition().X + otherCenter.X) - (position.X + center.X);
		dir.Y = (other.getPosition().Y + otherCenter.Y) - (position.Y + center.Y);
		dir.normalize();
		return dir;
	}



private:


};