/** Example 006 2D Graphics

This Tutorial shows how to do 2d graphics with the Irrlicht Engine.
It shows how to draw images, keycolor based sprites,
transparent rectangles, and different fonts. You may consider
this useful if you want to make a 2d game with the engine, or if
you want to draw a cool interface or head up display for your 3d game.

As always, I include the header files, use the irr namespace,
and tell the linker to link with the .lib file.
*/
#include <irrlicht.h>
#include "sol.hpp"
#include "EventReciever.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

core::vector2df position;
sol::state lua;
EventReceiver eventReciever;

sol::table getPosition() {
	return lua.create_table_with("X", position.X, "Y", position.Y);
}

void setPosition(sol::table newPosition) {

	float newX = newPosition["X"].get_or<float>(position.X);
	float newY = newPosition["Y"].get_or<float>(position.Y);

	position.X = (f32) newX;
	position.Y = (f32) newY;
}

bool isKeyDown(int key) {
	return eventReciever.IsKeyDown((EKEY_CODE) key);
}

/*
At first, we let the user select the driver type, then start up the engine, set
a caption, and get a pointer to the video driver.
*/
int main()
{

	lua.open_libraries(sol::lib::base);

	lua.set_function("getPosition", &getPosition);

	lua.set_function("setPosition", &setPosition);

	lua.set_function("isKeyDown", &isKeyDown);

	lua.script_file("keycodeLuaTable.lua");

	lua.script_file("test.lua");

	sol::protected_function problematicwoof = lua["update"];

	IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
		core::dimension2d<u32>(512, 384), false, false, false, false, &eventReciever);

	if (device == 0)
		return 1; // could not create selected driver.

	device->setWindowCaption(L"Irrlicht Engine - 2D Graphics Demo");

	video::IVideoDriver* driver = device->getVideoDriver();

	video::ITexture* images = driver->getTexture("assets/RedSquare.png");
	//driver->makeColorKeyTexture(images, core::position2d<s32>(0, 0));
	gui::IGUIFont* defaultFont = device->getGUIEnvironment()->getBuiltInFont();

	core::rect<s32> redSquareRect(0, 0, 32, 32);


	driver->getMaterial2D().TextureLayer[0].BilinearFilter = true;
	driver->getMaterial2D().AntiAliasing = video::EAAM_FULL_BASIC;

	position.X = 150;
	position.Y = 150;


	while (device->run() && driver)
	{
		if (device->isWindowActive())
		{
			u32 time = device->getTimer()->getTime();

			driver->beginScene(true, true, video::SColor(255, 120, 102, 136));

			problematicwoof();

			driver->draw2DImage(images, core::position2d<s32>((s32) position.X, (s32) position.Y),
				redSquareRect, 0,
				video::SColor(255, 255, 255, 255), true);

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

/*
That's all. I hope it was not too difficult.
**/
