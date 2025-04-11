#include "SkycubeModel.h"

SkycubeModel::SkycubeModel()
{
	vbo = new VBO();
	vbo->generateVBO(skycube, sizeof(skycube));

	vao = new VAO();
	vao->generateVAO();

	vao->bind();
	vbo->bind();
	vao->setVertices(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	vbo->unbind();
	vao->unbind();
}

void SkycubeModel::draw()
{
	vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, 108);
	vao->unbind();
}
