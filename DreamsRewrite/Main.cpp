#include <irrlicht.h>
#include "EventReciever.h"
#include <vector>
#include <iostream>
#include "Config.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

core::vector2df position;
EventReceiver eventReciever;
Config config;


const wchar_t* convertToLPtr(std::string str) {
	std::wstring widestr = std::wstring(str.begin(), str.end());
	const wchar_t* widecstr = widestr.c_str();
	return widecstr;
}

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
	{
		lua.set_function("isKeyDown", &isKeyDown);

		lua.script_file("keycodeLuaTable.lua");

		lua.script_file("Config.lua");

		std::string title;
		bool fullscreen;
		irr::u32 screenWidth;
		irr::u32 screenHeight;
		std::string assetFolder;

		title = lua["Config"]["Title"].get_or<std::string>("Made with Dreams Of Magnus Irrlicht Lua Frontend");
		sol::optional<int> fullscreenOpt = lua["Config"]["Fullscreen"];
		if (fullscreenOpt == sol::nullopt) {
			fullscreen = false;
		}
		else {
			fullscreen = (fullscreenOpt.value() != 0);
		}
		sol::optional<irr::s32> screenWidthOpt = lua["Config"]["ScreenWidth"];
		if (screenWidthOpt == sol::nullopt) {
			screenWidth = 512;
		}
		else {
			screenWidth = (irr::u32) screenWidthOpt.value();
		}
		sol::optional<irr::s32> screenHeightOpt = lua["Config"]["ScreenHeight"];
		if (screenHeightOpt == sol::nullopt) {
			screenHeight = 384;
		}
		else {
			screenHeight = (irr::u32) screenHeightOpt.value();
		}
		assetFolder = lua["Config"]["AssetFolder"].get_or<std::string>("Assets/");
		sol::optional<sol::table> scenesTableOpt = lua["Config"]["Scenes"];
		if (scenesTableOpt == sol::nullopt) {
			printf("Error Loading config file");
			return 0;			
		}
		else {
			sol::table scenesTable = scenesTableOpt.value();
			if (scenesTable.size() == 0) {
				printf("Not enough scenes\n");
				return 0;
			}
			config = Config(title, fullscreen, screenWidth, screenHeight, assetFolder);

			device = createDevice(video::EDT_OPENGL,
				core::dimension2d<u32>(config.screenWidth, config.screenHeight), false, config.fullscreen, false, config.fullscreen, &eventReciever);

			if (device == 0)
				return 1; // could not create selected driver.

			std::wstring widestr = std::wstring(config.title.begin(), config.title.end());
			device->setWindowCaption(widestr.c_str());

			driver = device->getVideoDriver();


			for (int i = 1; i <= scenesTable.size(); ++i) {
				Scene scene = Scene(config.assetsFolder, scenesTable[i], "Temp");
				
				config.scenes.push_back(scene);
			}

		}


	}
	
	Scene firstScene = config.scenes[0];

	loadScene(&firstScene);
	

	/*GameObject obj1 = GameObject();
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

	obj1.setImage(images);
	obj2.setImage(images);
	*/

	//driver->makeColorKeyTexture(images, core::position2d<s32>(0, 0));
	gui::IGUIFont* defaultFont = device->getGUIEnvironment()->getBuiltInFont();

	core::rect<s32> redSquareRect(0, 0, 32, 32);

	//obj1.setImagePosition(redSquareRect);
	//obj2.setImagePosition(redSquareRect);

	//gameObjects.push_back(obj1);
	//gameObjects.push_back(obj2);


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

			for (int i = 0; i < activeScene->getNumGameObjects(); ++i) {
				GameObject obj = activeScene->getGameObject(i);
				setPosition(obj.getPosition());
				lua.set_function("getPosition", &getLuaPosition);

				lua.set_function("setPosition", &setLuaPosition);


				//obj.getUpdateFunction()();

				obj.setPosition(getPosition());
				activeScene->setGameObject(i, obj);
				drawGameObject(driver, &obj);
			}
			/*
			if (gameObjects[0].isColliding(gameObjects[1])) {
				core::vector2df collDIr = gameObjects[0].collisionDirectionNormalized(gameObjects[1]);
				std::cout << "(" << collDIr.X << ", " << collDIr.Y << ")" << std::endl;
			}*/

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
