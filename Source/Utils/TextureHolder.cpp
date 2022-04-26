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
	//1. fileName(����Ű)�� key�� ������ �ִ°� map�� �ֳ� ����?
	//2-1. ������ �ʾּ� ã�Ƽ� ��ȯ
	//2-2. ������ ���� map insert

	//auto it = mapText
	auto& map = instance->mapTexture;
	auto it = map.find(fileName);
	if (it == map.end())	//�ʿ� ���°��
	{
		auto & texture = map[fileName];
		texture.loadFromFile(fileName);
	}
	return map[fileName];
}
