#include "T_TextureLoader.h"






void TextureLoader::ImportTexture(std::string& filePath, uint size, char* buffer)
{
	uint textureId = 0;

	ilGenImages(1, &textureId);
	ilBindImage(textureId);

	uint textureSize;
	ILubyte* data;

	ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);
	textureSize = ilSaveL(IL_DDS, nullptr, 0);


	//Check si hay error cargando la textura
	if (!ilLoadL(IL_TYPE_UNKNOWN, buffer, size)) {
		LOG("Error loading the texture: %s \n", iluGetString(ilGetError()));
	}

	if (textureSize > 0) {
		data = new ILubyte[textureSize];
		ilSaveL(IL_DDS, data, textureSize);
		RELEASE_ARRAY(data);
	}


}

uint TextureLoader::LoadTexture(std::string&& filePath, uint size, uint* w, uint* h)
{
	return uint();
}
