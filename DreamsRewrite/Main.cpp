#include <irrlicht.h>
#include "sol.hpp"
#include "EventReciever.h"
#include <vector>
#include "GameObject.h"
#include <iostream>
#include "Config.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

core::vector2df position;
sol::state lua;
EventReceiver eventReciever;

Config config;

sol::table getLuaPosition() {
	return lua.create_table_with("X", position.X, "Y", position.Y);
}

void setLuaPosition(sol::table newPosition) {

	float newX = newPosition["X"].get_or<float>(position.X);
	float newY = newPosition["Y"].get_or<float>(position.Y);

	position.X = (f32) newX;
	position.Y = (f32) newY;
}

void setPosition(core::vector2df newPosition) {
	position = newPosition;
}

core::vector2df getPosition() {
	return position;
}

inline bool isKeyDown(int key) {
	return eventReciever.IsKeyDown((EKEY_CODE) key);
}

inline void drawGameObject(video::IVideoDriver* driver, GameObject *obj) {
	irr::core::vector2df position = obj->getPosition();

	driver->draw2DImage(obj->getImage(), core::position2d<s32>((s32)position.X, (s32)position.Y),
		obj->getImagePosition(), 0,
		video::SColor(255, 255, 255, 255), true);
}

/*
At first, we let the user select the driver type, then start up the engine, set
a caption, and get a pointer to the video driver.
*/
int main()
{
	std::vector<GameObject> gameObjects;
	lua.open_libraries(sol::lib::base);

	lua.set_function("isKeyDown", &isKeyDown);

	lua.script_file("keycodeLuaTable.lua");

	GameObject obj1 = GameObject();
	GameObject obj2 = GameObject();
	obj1.setPosition(150, 150);


	lua.script_file("test.lua");
	
	sol::protected_function updateFunction = lua["update"];
	
	obj1.setUpdateFunction(updateFunction);

	lua.script_file("test2.lua");

	updateFunction = lua["update"];

	obj2.setUpdateFunction(updateFunction);
	
	obj1.setObjectScript("test.lua");
	obj2.setObjectScript("test2.lua");

	IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
		core::dimension2d<u32>(512, 384), false, false, false, false, &eventReciever);

	if (device == 0)
		return 1; // could not create selected driver.

	device->setWindowCaption(L"Irrlicht Engine - 2D Graphics Demo");

	video::IVideoDriver* driver = device->getVideoDriver();

	video::ITexture* images = driver->getTexture("assets/RedSquare.png");

	obj1.setImage(images);
	obj2.setImage(images);

	//driver->makeColorKeyTexture(images, core::position2d<s32>(0, 0));
	gui::IGUIFont* defaultFont = device->getGUIEnvironment()->getBuiltInFont();

	core::rect<s32> redSquareRect(0, 0, 32, 32);

	obj1.setImagePosition(redSquareRect);
	obj2.setImagePosition(redSquareRect);

	gameObjects.push_back(obj1);
	gameObjects.push_back(obj2);


	driver->getMaterial2D().TextureLayer[0].BilinearFilter = true;
	driver->getMaterial2D().AntiAliasing = video::EAAM_FULL_BASIC;

	position.X = 150;
	position.Y = 150;


	while (device->run() && driver)
	{
		if (device->isWindowActive() || 1)
		{
			u32 time = device->getTimer()->getTime();

			driver->beginScene(true, true, video::SColor(255, 120, 102, 136));

			for (int i = 0; i < gameObjects.size(); ++i) {
				GameObject obj = gameObjects[i];
				setPosition(obj.getPosition());
				lua.set_function("getPosition", &getLuaPosition);

				lua.set_function("setPosition", &setLuaPosition);


				obj.getUpdateFunction()();

				obj.setPosition(getPosition());
				gameObjects[i] = obj;
				drawGameObject(driver, &obj);
			}

			if (gameObjects[0].isColliding(gameObjects[1])) {
				core::vector2df collDIr = gameObjects[0].collisionDirectionNormalized(gameObjects[1]);
				std::cout << "(" << collDIr.X << ", " << collDIr.Y << ")" << std::endl;
			}

			//driver->draw2DImage(images, core::position2d<s32>((s32) position.X, (s32) position.Y),
			//	redSquareRect, 0,
			//	video::SColor(255, 255, 255, 255), true);

			// draw some text
			if (defaultFont) {
				defaultFont->draw(L"Text",
					core::rect<s32>(130, 10, 300, 50),
					video::SColor(255, 0, 255, 255));
			}

			core::position2d<s32> m = device->getCursorControl()->getPosition();
			driver->draw2DRectangle(video::SColor(100, 255, 255, 255),
				core::rect<s32>(m.X - 20, m.Y - 20, m.X + 20, m.Y + 20));

			driver->endScene();

		}

	}

	device->drop();
	return 0;
}
