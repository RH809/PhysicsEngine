#include "object_manager.h"
#include "object.h"
#include "sphere.h"

#include <memory>

ObjectManager::ObjectManager() {
	//new Sphere(0.0f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	//new Sphere(1.0f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	//new Sphere(-1.0f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	//new Sphere(0.0f, 1.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	//new Sphere(0.0f, -1.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	//new Sphere(0.0f, 0.0f, 5.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	//new Sphere(0.0f, 0.0f, -5.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	//new Sphere(9.5f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);
	//new Sphere(-9.5f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f, this);

	createSphere(0.0f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
	createSphere(1.0f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
	createSphere(-1.0f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
	createSphere(0.0f, 1.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
	createSphere(0.0f, -1.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
	createSphere(0.0f, 0.0f, 5.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
	createSphere(0.0f, 0.0f, -5.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
	createSphere(9.5f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
	createSphere(-9.5f, 0.0f, 0.0f, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
}

void ObjectManager::createSphere(float x, float y, float z, glm::quat r, float m, float s) {
	auto newSphere = std::make_shared<Sphere>(x, y, z, r, m, s, this);
	ObjectNode* node = new ObjectNode(nullptr, nullptr, newSphere);
	newSphere->setNode(node);
	int bucketID = getBucketID(newSphere->getPos());
	addObject(bucketID, node);
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