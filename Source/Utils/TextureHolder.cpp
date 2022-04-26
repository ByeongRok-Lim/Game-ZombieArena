#include "TextureHolder.h"
#include <assert.h>
TextureHolder* TextureHolder::instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(instance == nullptr);
	instance = this;
}

Texture& TextureHolder::GetTexture(string fileName)
{
	//1. fileName(맵의키)를 key로 가지고 있는게 map에 있냐 없냐?
	//2-1. 있으면 맵애서 찾아서 반환
	//2-2. 없으면 만들어서 map insert

	//auto it = mapText
	auto& map = instance->mapTexture;
	auto it = map.find(fileName);
	if (it == map.end())	//맵에 없는경우
	{
		auto & texture = map[fileName];
		texture.loadFromFile(fileName);
	}
	return map[fileName];
}
