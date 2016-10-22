#pragma once
#include <irrlicht.h>


class Image {
	irr::video::ITexture* image;
	int dependencies;
};