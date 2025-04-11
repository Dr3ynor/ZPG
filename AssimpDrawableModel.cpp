#include "AssimpDrawableModel.h"

AssimpDrawableModel::AssimpDrawableModel(char *filePath)
{
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_OptimizeMeshes |
								 aiProcess_JoinIdenticalVertices |
								 aiProcess_Triangulate;

	const aiScene *scene = importer.ReadFile(filePath, importOptions);

	std::vector<float> data;
	if (scene && scene->HasMeshes())
	{
		aiMesh *mesh = scene->mMeshes[0];
		this->count = mesh->mNumFaces * 3;

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				aiVector3D vertex = mesh->mVertices[mesh->mFaces[i].mIndices[j]];
				aiVector3D normal = mesh->mNormals[mesh->mFaces[i].mIndices[j]];
				aiVector3D texCoord = mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]];

				data.push_back(vertex.x);
				data.push_back(vertex.y);
				data.push_back(vertex.z);
				data.push_back(normal.x);
				data.push_back(normal.y);
				data.push_back(normal.z);
				data.push_back(texCoord.x);
				data.push_back(texCoord.y);
			}
		}
	}

	// Debug: Print the first few vertices to check their values
	for (int i = 0; i < 15; i += 3)
	{
		printf("Vertex %d: (%f, %f, %f)\n", i / 3, data[i], data[i + 1], data[i + 2]);
	}

	vbo = new VBO();
	vbo->generateVBO(&data[0], data.size() * sizeof(float));

	vao = new VAO();
	vao->generateVAO();

	vao->bind();
	vbo->bind();
	vao->setVertices(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)0);
	vao->setVertices(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)(sizeof(float) * 3));
	vao->setVertices(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)(sizeof(float) * 6));
	vbo->unbind();
	vao->unbind();
}

void AssimpDrawableModel::draw()
{
	vao->bind();

	// Debug: Add an OpenGL error check before drawing
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		fprintf(stderr, "OpenGL Error (before drawing): %d\n", error);
	}

	glDrawArrays(GL_TRIANGLES, 0, count);

	// Debug: Add an OpenGL error check after drawing
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		fprintf(stderr, "OpenGL Error (after drawing): %d\n", error);
	}

	vao->unbind();
}