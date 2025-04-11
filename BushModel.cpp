#include "BushModel.h"

BushModel::BushModel()
{
	vbo = new VBO();
	vbo->generateVBO(bushes, sizeof(bushes));

	vao = new VAO();
	vao->generateVAO();

	vao->bind();
	vbo->bind();
	vao->setVertices(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	vao->setVertices(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	vbo->unbind();
	vao->unbind();
}

void BushModel::draw()
{
	vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, 8730);
	vao->unbind();
}
