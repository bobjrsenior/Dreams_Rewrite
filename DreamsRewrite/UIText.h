#pragma once
#include "IrrItems.h"
#include <vector>

class UIText {
public:

private:
	std::wstring text;

	irr::core::rect<irr::s32> position;
	irr::video::SColor color;

public:

	UIText(std::wstring text, irr::core::rect<irr::s32> position) : text(text), position(position) {
		color.setRed(255);
		color.setGreen(255);
		color.setBlue(255);
		color.setAlpha(255);
	}
	
	void setText(std::wstring newText) {
		text = newText;
	}


	void drawText(irr::gui::IGUIFont* font) {
		font->draw(text.c_str(), position, color);
	}
};