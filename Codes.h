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

enum PlayerControl
{
	PLAYER_1,
	PLAYER_2,
};

extern std::map<TextureType, std::string> textureMap;