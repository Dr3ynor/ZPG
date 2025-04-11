#include "Texture2D.h"

Texture2D::Texture2D(const char *filePath)
{
    this->filePath = filePath;
    this->position = position;
}

GLuint loadTexture(const char *filePath, bool rgb2bgr)
{
    cv::Mat imagergb = cv::imread(filePath, cv::IMREAD_UNCHANGED);
    cv::Mat image = imagergb;

    if (rgb2bgr)
    {
        cv::cvtColor(imagergb, image, cv::COLOR_RGB2BGR);
    }

    if (image.empty())
    {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return 0; // Return 0 or some default texture ID indicating an error
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cv::flip(image, image, 0);

    int format = (image.channels() == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, image.cols, image.rows, 0, format, GL_UNSIGNED_BYTE, image.data);

    return textureID;
}

void Texture2D::bind(bool rgb2bgr)
{
    glActiveTexture(GL_TEXTURE0 + position);

    printf("OpenGL/OpenCV: Loading texture %d\n", this->textureId);

    this->textureId = loadTexture(filePath, rgb2bgr);

    printf("OpenGL/OpenCV: Loaded texture %d\n", this->textureId);

    if (this->textureId == 0)
    {
        printf("OpenGL/OpenCV: Error loading texture!\n");
    }

    glBindTexture(GL_TEXTURE_2D, this->textureId);
}