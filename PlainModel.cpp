#include "PlainModel.h"

PlainModel::PlainModel()
{
	vbo = new VBO();
	vbo->generateVBO(plain, sizeof(plain));

	vao = new VAO();
	vao->generateVAO();

	vao->bind();
	vbo->bind();
	vao->setVertices(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	vao->setVertices(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	vbo->unbind();
	vao->unbind();
}

void PlainModel::draw()
{
	vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao->unbind();
}
