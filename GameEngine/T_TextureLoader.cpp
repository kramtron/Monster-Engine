#include "T_TextureLoader.h"




void TextureLoader::ImportTexture(std::string& filePath, uint size, char* buffer)
{

	//No se usa por el momento
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

uint TextureLoader::LoadTexture(const char* filePath)
{

	//Starting Devil buffers

	ILuint textureId;

	ilGenImages(1, &textureId);
	ilBindImage(textureId);


	bool loaded;

	loaded = ilLoadImage(filePath);

	if (!loaded) {
		LOG("Failed on loading texture %s, %s", filePath, ilGetError());
	}
	
	
	
	//ilLoadImage(filePath);


	//ILubyte* data = ilGetData();

	ILuint imgWidth, imgHeight;

	imgWidth = ilGetInteger(IL_IMAGE_WIDTH);
	imgHeight = ilGetInteger(IL_IMAGE_HEIGHT);


	//Aqui data se corrompe
	GLuint imageId = ilutGLBindTexImage();

	//glGenTextures(1, &imageId);

	glBindTexture(GL_TEXTURE_2D, imageId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);


	//Delete buffer
	ilDeleteImages(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, 0);

	return imageId;
}

void TextureLoader::Init()
{

	ilInit();
	iluInit();
	ilutInit();

}

void TextureLoader::Start()
{

	TextureLoader* tL = new TextureLoader;

	GLuint checkID;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			tL->checkImage[i][j][0] = (GLubyte)c;
			tL->checkImage[i][j][1] = (GLubyte)c;
			tL->checkImage[i][j][2] = (GLubyte)c;
			tL->checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &checkID);
	glBindTexture(GL_TEXTURE_2D, checkID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, tL->checkImage);


	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);


}

void TextureLoader::CleanUp()
{

}
