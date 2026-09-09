#include "object.h"
#include "object_node.h"
#include "object_manager.h"

Object::Object(float _x, float _y, float _z, glm::quat _r, float _m, float _s, ObjectManager* _manager) : rotation(_r), mass(_m), scale(_s), manager(_manager) {
	position.x = _x;
	position.y = _y;
	position.z = _z;

	vertices = std::vector<float>();
	indices = std::vector<unsigned int>();
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

void Object::updateBucket() {
	int newID = manager->getBucketID(position);
	if (newID != bucketID) {
		manager->moveObject(bucketID, newID, node);
		bucketID = newID;
	}
}