#pragma once
#include <string>
#include "Scenes.h"
#include <irrlicht.h>
#include "sol.hpp"

class Config {
public:
	std::string title;
	bool fullscreen;
	irr::s32 screenWidth;
	irr::s32 screenHeight;
	std::vector<std::string> scenes;
	std::string assetsFolder;

private:

public:
	Config() : title("Made with Dreams Of Magnus Irrlicht Lua Frontend"), fullscreen(false), screenWidth(512), screenHeight(384), assetsFolder("assets/") {}

	Config(std::string title, bool fullscreen, int screenWidth, int screnHeight, std::string assetsFolder = "assets/") : title(title), fullscreen(fullscreen), screenWidth(screenWidth), screenHeight(screenHeight), assetsFolder(assetsFolder) {}


private:

};