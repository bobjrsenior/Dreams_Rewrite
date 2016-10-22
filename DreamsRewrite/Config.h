#pragma once
#include <string>
#include "Scenes.h"
#include <irrlicht.h>

class Config {
public:
	std::string title;
	bool fullscreen;
	irr::u32 screenWidth;
	irr::u32 screenHeight;
	std::vector<Scene> scenes;
	std::string assetsFolder;

private:

public:
	Config() : title("Made with Dreams Of Magnus Irrlicht Lua Frontend"), fullscreen(false), screenWidth(512), screenHeight(384), assetsFolder("assets/") {}

	Config(std::string title, bool fullscreen, int screenWidth, int screenHeight, std::string assetsFolder = "assets/") : title(title), fullscreen(fullscreen), screenWidth(screenWidth), screenHeight(screenHeight), assetsFolder(assetsFolder) {}


private:

};