#include "TextureCube.h"

TextureCube::TextureCube(const char *top, const char *bottom, const char *front, const char *back, const char *right, const char *left)
{
	this->position = position;

	this->right = right;
	this->left = left;
	this->top = top;
	this->bottom = bottom;
	this->front = front;
	this->back = back;
}

GLuint loadCube(const char *right, const char *left, const char *top,
				const char *bottom, const char *front, const char *back)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	std::vector<std::string> faces = {right, left, top, bottom, front, back};

	for (size_t i = 0; i < faces.size(); ++i)
	{
		cv::Mat image = cv::imread(faces[i]);
		if (!image.empty())
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
						 image.cols, image.rows, 0,
						 GL_BGR, GL_UNSIGNED_BYTE, image.data);
		}
		else
		{
			printf("OpenCV: Error loading image!");
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

void TextureCube::bind(bool rgb2bgr)
{
	glActiveTexture(GL_TEXTURE0 + position);

	printf("OpenGL/OpenCV: Loading texture %d\n", this->textureId);

	this->textureId = loadCube(this->right, this->left, this->top, this->bottom, this->front, this->back);

	printf("OpenGL/OpenCV: Loaded texture %d\n", this->textureId);

	if (this->textureId == 0)
	{
		printf("OpenGL/OpenCV: Error loading cube texture!\n");
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureId);
}
