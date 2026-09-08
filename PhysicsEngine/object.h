#ifndef OBJECT_H
#define OBJECT_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "object_node.h"


class Object {

protected:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float mass;
	float scale;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	ObjectNode* node;

public:
	Object(float _x, float _y, float _z, glm::quat _r, float _m, float _s);

	glm::vec3 getPos() const;
	glm::quat getRotation() const;
	const std::vector<float>& getVertices() const;
	const std::vector<unsigned int>& getIndices() const;

};

#endif