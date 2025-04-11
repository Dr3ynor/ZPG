#include "CrossHairModel.h"

CrossHairModel::CrossHairModel()
{
	vbo = new VBO();
	vbo->generateVBO(crossHair, sizeof(crossHair));

	vao = new VAO();
	vao->generateVAO();

	vao->bind();
	vbo->bind();
	vao->setVertices(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	vbo->unbind();
	vao->unbind();
}

void CrossHairModel::draw()
{
	vao->bind();
	glDrawArrays(GL_LINES, 0, 4);
	vao->unbind();
}
