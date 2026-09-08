#include "object_manager.h"
#include "object.h"
#include "sphere.h"

ObjectManager::ObjectManager() {
	new Sphere(0.0f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	new Sphere(1.0f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	new Sphere(-1.0f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	new Sphere(0.0f, 1.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	new Sphere(0.0f, -1.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	new Sphere(0.0f, 0.0f, 5.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	new Sphere(0.0f, 0.0f, -5.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	new Sphere(9.5f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	new Sphere(-9.5f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
}

void ObjectManager::addObject(int id, ObjectNode* node) {
	if (bucketMap.find(id) == bucketMap.end()) {
		bucketMap[id] = new ObjectBucket();
	}
	bucketMap[id]->addObject(node);
	objects.push_back(node->object);
}

void ObjectManager::moveObject(int oldID, int newID, ObjectNode* node) {
	if (bucketMap.find(oldID) != bucketMap.end()) {
		bucketMap[oldID]->removeObject(node);
	}
	if (bucketMap.find(newID) == bucketMap.end()) {
		bucketMap[newID] = new ObjectBucket();
	}
	bucketMap[newID]->addObject(node);
}

const std::vector<std::shared_ptr<Object>>& ObjectManager::getObjects() const {
	return objects;
}