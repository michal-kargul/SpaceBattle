#pragma once

#include <map>
#include <string>

enum TextureType
{
	BACKGROUND,
	SHIP_BLUE,
	SHIP_RED,
	SHIP_FLAME,
	SHIP_EXHAUST,
};

extern std::map<TextureType, std::string> textureMap;