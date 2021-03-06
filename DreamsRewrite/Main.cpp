#ifdef _WIN32
#include <Windows.h>
#include <mmsystem.h>
#undef PlaySound
#endif
#include <irrlicht.h>
#include "EventReciever.h"
#include <vector>
#include <map>
#include <iostream>
#include "Config.h"
#include "UIText.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

core::vector2df position;
video::SColor clearColor;
EventReceiver eventReciever;
Config config;
int curObjectIndex = -1;
u32 curTime;
u32 frameRate;
f32 millisecondsPerFrame;
bool continueGame = true;
std::vector<UIText> uiTextItems;
std::map<std::string, float> globalNumbers;

inline void quitGame() {
	continueGame = false;
}

inline u32 getTime() {
	return curTime;
}

inline float getMillisPerFrame() {
	return millisecondsPerFrame;
}

inline void loadSceneIndex(int index) {
	if (index >= 0 && index < config.scenes.size()) {
		loadScene(&config.scenes[index], index);
	}
}

inline sol::table getLuaMousePos() {
	core::position2d<s32> mPos = device->getCursorControl()->getPosition();
	return lua.create_table_with("X", mPos.X, "Y", mPos.Y);
}

void setLuaMousePos(sol::table newPosition) {
	core::position2d<s32> mPos = device->getCursorControl()->getPosition();
	float newX = newPosition["X"].get_or<float>(mPos.X);
	float newY = newPosition["Y"].get_or<float>(mPos.Y);

	mPos.X = (s32)newX;
	mPos.Y = (s32)newY;

	device->getCursorControl()->setPosition(mPos);
}

inline const wchar_t* convertToLPtr(std::string str) {
	std::wstring widestr = std::wstring(str.begin(), str.end());
	const wchar_t* widecstr = widestr.c_str();
	return widecstr;
}

inline sol::table getLuaPosition() {
	return lua.create_table_with("X", position.X, "Y", position.Y);
}

void setLuaPosition(sol::table newPosition) {

	float newX = newPosition["X"].get_or<float>(position.X);
	float newY = newPosition["Y"].get_or<float>(position.Y);

	position.X = (f32) newX;
	position.Y = (f32) newY;
}

inline void setPosition(core::vector2df newPosition) {
	position = newPosition;
}

inline sol::table getClearColor() {
	return lua.create_table_with("R", clearColor.getRed(), "G", clearColor.getGreen(), "B", clearColor.getBlue(), "A", clearColor.getAlpha());
}

inline void setClearColor(s32 red, s32 green, s32 blue, s32 alpha) {
	clearColor = video::SColor(alpha, red, green, blue);
}

inline core::vector2df getPosition() {
	return position;
}

inline int getScreenWidth(){
	return config.screenWidth;
}

inline int getScreenHeight() {
	return config.screenHeight;
}

inline int addUIText(std::string text, int xPos, int yPos) {
	std::wstring uiTextTest;
	uiTextTest.assign(text.begin(), text.end());
	core::rect<s32> position(xPos, yPos, xPos + 70, yPos + 40);

	UIText newText(uiTextTest, position);
	return activeScene->addUITextItem(newText);
}

inline void modifyUIText(int index, std::string newText) {
	std::wstring uiTextTest;
	uiTextTest.assign(newText.begin(), newText.end());

	activeScene->modifyUITextItem(index, uiTextTest);
}

inline int compareTag(int objectIndex, std::string tag) {
	if (curObjectIndex != -1 && objectIndex < activeScene->getNumGameObjects()) {
		if (tag == activeScene->getGameObject(objectIndex).getTag()) {
			return 1;
		}
		return 0;
	}
	return -1;
}

sol::table isColliding() {
	// Table to hold the index of every object we are colliding with
	sol::table collisions = lua.create_table_with();
	if (curObjectIndex != -1) {
		// CHeck collision against every object
		GameObject obj = activeScene->getGameObject(curObjectIndex);
		for (int i = 0; i < activeScene->getNumGameObjects(); ++i) {
			if (i != curObjectIndex) {
				if (obj.isColliding(activeScene->getGameObject(i))) {
					collisions.add(i);
				}
			}
		}
	}
	return collisions;
}

inline sol::table collisionDirection(int otherObjIndex) {

	f32 xPos = 0;
	f32 yPos = 0;
	if (curObjectIndex != -1 && otherObjIndex != curObjectIndex && otherObjIndex < activeScene->getNumGameObjects()) {
		core::vector2df dir = activeScene->getGameObject(curObjectIndex).collisionDirectionNormalized(activeScene->getGameObject(otherObjIndex));
		xPos = dir.X;
		yPos = dir.Y;
	}
	return lua.create_table_with("X", xPos, "Y", yPos);
}

inline bool isKeyDown(int key) {
	if (key < 0 || key >= eventReciever.numKeys()) {
		return false;
	}
	return eventReciever.IsKeyDown((EKEY_CODE) key);
}

inline void forceKeyUp(int key) {
	eventReciever.forceKeyUp((EKEY_CODE)key);
}

inline void playSound(std::string soundFile) {
#ifdef _WIN32
	PlaySoundA((config.assetsFolder + soundFile).c_str(), NULL, SND_ASYNC | SND_FILENAME);
#endif
}

inline void playSoundLoop(std::string soundFile) {
#ifdef _WIN32
	PlaySoundA((config.assetsFolder + soundFile).c_str(), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
#endif
}

inline int getSceneIndex() {
	return activeSceneIndex;
}

inline void addGlobalNumber(std::string key, float number) {
	globalNumbers[key] = number;
}

inline float getGlobalNumber(std::string key) {
	std::map<std::string, float>::iterator it;
	it = globalNumbers.find(key);
	if (it != globalNumbers.end()) {
		return it->second;
	}
	else {
		return NAN;
	}

}

inline void modifyGlobalNumber(std::string key, float newNumber) {
	globalNumbers[key] = newNumber;
}

inline void drawGameObject(video::IVideoDriver* driver, GameObject *obj) {
	irr::core::vector2df objPosition = obj->getPosition();
	irr::core::rect<irr::s32> imagePosition = obj->getImagePosition();

	driver->draw2DImage(obj->getImage(), core::position2d<s32>((s32)(objPosition.X - (0.5f * imagePosition.getWidth())), (s32)(objPosition.Y - (0.5f * imagePosition.getHeight()))),
		obj->getImagePosition(), 0,
		video::SColor(255, 255, 255, 255), true);
}

///
/// Lua Callbacks
///
void bindLuaCallbacks() {
	lua.set_function("isKeyDown", &isKeyDown);

	lua.set_function("forceKeyUp", &forceKeyUp);

	lua.set_function("getMousePos", &getLuaMousePos);

	lua.set_function("setMousePos", &setLuaMousePos);

	lua.set_function("getTime", &getTime);

	lua.set_function("quitGame", &quitGame);

	lua.set_function("getScreenWidth", &getScreenWidth);

	lua.set_function("getScreenHeight", &getScreenHeight);

	lua.set_function("getDeltaTime", &getMillisPerFrame);

	lua.set_function("isColliding", &isColliding);

	lua.set_function("collisionDirection", &collisionDirection);

	lua.set_function("compareTag", &compareTag);

	lua.set_function("getClearColor", &getClearColor);

	lua.set_function("setClearColor", &setClearColor);

	lua.set_function("getPosition", &getLuaPosition);

	lua.set_function("setPosition", &setLuaPosition);

	lua.set_function("playSound", &playSound);

	lua.set_function("playSoundLoop", &playSoundLoop);

	lua.set_function("getSceneIndex", &getSceneIndex);

	lua.set_function("addUIText", &addUIText);

	lua.set_function("modifyUIText", &modifyUIText);

	lua.set_function("addGlobalNumber", &addGlobalNumber);

	lua.set_function("getGlobalNumber", &getGlobalNumber);

	lua.set_function("modifyGlobalNumber", &modifyGlobalNumber);

	lua.script_file("keycodeLuaTable.lua");

	lua.script("function tableLength(T) local count = 0 for _ in pairs(T) do count = count + 1 end  return count  end");
}

/*
At first, we let the user select the driver type, then start up the engine, set
a caption, and get a pointer to the video driver.
*/
int main()
{
	std::vector<GameObject> gameObjects;
	clearColor = video::SColor(255, 120, 102, 136);
	frameRate = 60;
	millisecondsPerFrame = 1000.0f / frameRate;

	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);

	// Initialize the game (load config/scenes)
	{
		
		bindLuaCallbacks();

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
	
	lua["loadScene"] = &loadSceneIndex;
	Scene firstScene = config.scenes[0];

	loadScene(&firstScene, 0);

	//driver->makeColorKeyTexture(images, core::position2d<s32>(0, 0));
	gui::IGUIFont* defaultFont = device->getGUIEnvironment()->getBuiltInFont();

	// Game Font
	gui::IGUIEnvironment * irrGUI = device->getGUIEnvironment();
	gui::IGUIFont* mainFont = irrGUI->getFont("myfont.xml");
	irrGUI->getSkin()->setFont(mainFont);

	//driver->getMaterial2D().TextureLayer[0].BilinearFilter = true;
	//driver->getMaterial2D().AntiAliasing = video::EAAM_FULL_BASIC;
	
	u32 prevTime = device->getTimer()->getRealTime();
	// Main game loop
	while (device->run() && driver && continueGame)
	{
		if (device->isWindowActive() && continueGame)
		{
			curTime = device->getTimer()->getRealTime();

			driver->beginScene(true, true, clearColor);

			// Go through every gameobject in the current scene
			Scene *curScene = activeScene;
			for (int i = 0; i < curScene->getNumGameObjects() && continueGame; ++i) {
				
				// Grab the object and call its update script if it has one
				GameObject obj = curScene->getGameObject(i);
				curObjectIndex = i;
				if (obj.hasUpdateScript) {
					
					setPosition(obj.getPosition());


					obj.getUpdateFunction()();

					// CHeck to see if the script changed scenes
					if (curScene != activeScene) {
						break;
					}

					obj.setPosition(getPosition());
					curScene->setGameObject(i, obj);
				}
				// Draw the object
				drawGameObject(driver, &obj);
			}
	
			/*
			// draw some text
			if (defaultFont) {
				float curFrameRate = 0;
				if (curTime != 0) {
					curFrameRate = 1000.0f / (curTime - prevTime);
				}				
				std::wstring framerateStr = std::to_wstring(curFrameRate);
				mainFont->draw(framerateStr.c_str(),
					core::rect<s32>(600, 10, 300, 50),
					video::SColor(255, 255, 255, 255));
			}
			*/

			if (mainFont) {
				// Draw all UI text items
				curScene->drawAllUITextItems(mainFont);
			}

			// Makes a colorful box around the mouse
			core::position2d<s32> m = device->getCursorControl()->getPosition();
			driver->draw2DRectangle(video::SColor(100, (curTime % 255), (2 * curTime) % 255, (int) ((1.5f * curTime)) % 255),
				core::rect<s32>(m.X - 20, m.Y - 20, m.X + 20, m.Y + 20));


			// Finish the scene
			driver->endScene();
			prevTime = curTime;

			// If not in fullscreen (VSync ins't on), make sure the frame rate is consistent
			if (!config.fullscreen) {
				u32 cycleCheck = device->getTimer()->getRealTime();

				while (cycleCheck - curTime < millisecondsPerFrame) {
					cycleCheck = device->getTimer()->getRealTime();
				}
			}

		}

	}
	deloadScene(activeScene);
	device->drop();
	return 0;
}
