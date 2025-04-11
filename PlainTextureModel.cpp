#include "PlainTextureModel.h"

PlainTextureModel::PlainTextureModel()
{
	vbo = new VBO();
	vbo->generateVBO(plainTexture, sizeof(plainTexture));

	vao = new VAO();
	vao->generateVAO();

	vao->bind();
	vbo->bind();
	vao->setVertices(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	vao->setVertices(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	vao->setVertices(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	vbo->unbind();
	vao->unbind();
}

void PlainTextureModel::draw()
{
	vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao->unbind();
}
