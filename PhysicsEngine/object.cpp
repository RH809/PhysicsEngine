#include "object.h"
#include "object_node.h"
#include "object_manager.h"

Object::Object(float _x, float _y, float _z, glm::quat _r, float _m, float _s, ObjectManager* _manager) : rotation(_r), mass(_m), scale(_s), manager(_manager) {
	position.x = _x;
	position.y = _y;
	position.z = _z;

	vertices = std::vector<float>();
	indices = std::vector<unsigned int>();
	bucketID = 0;
	node = NULL;
	manager = NULL;
}

glm::vec3 Object::getPos() const {
	return position;
}

glm::quat Object::getRotation() const {
	return rotation;
}

const std::vector<float>& Object::getVertices() const {
	return vertices;
}

const std::vector<unsigned int>& Object::getIndices() const {
	return indices;
}

ObjectNode* Object::getNode() const {
	return node;
}

void Object::setNode(ObjectNode* _node) {
	node = _node;
}

void Object::updateBucket() {
	int newID = manager->getBucketID(position);
	if (newID != bucketID) {
		manager->moveObject(bucketID, newID, node);
		bucketID = newID;
	}
}

void Object::setupBuffers() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	// set vertex data interpretation
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

unsigned int Object::getVAO() const {
	return VAO;
}