#pragma once
#include <SFML/graphics.hpp>
#include <map>

using namespace sf;
using namespace std;
class TextureHolder
{
public:
	TextureHolder();

	static Texture& GetTexture(string fileName);
private:
	map<string, Texture> mapTexture;

	static TextureHolder* instance;
};

