#pragma once

#include "glew.h"
#include "Globals.h"
#include "Application.h"



class CamBuffers
{
public:
	CamBuffers();
	~CamBuffers();

	void StartCamBuffers(int w, int h);


	void CleanUp();


public:

	int GetWidth() { return width; };

	int GetHeight() { return height; };

	GLuint GetFrameBuffer() { return frameBuffer; }

	GLuint GetTextureBuffer() { return textureColorBuffer; }


public:

	void SetWidth(int width) { this->width = width; }

	void SetHeight(int height) { this->height = height; }


protected:


	GLuint textureColorBuffer;
	GLuint frameBuffer;

	GLuint rbo;

	int width;
	int height;

};

