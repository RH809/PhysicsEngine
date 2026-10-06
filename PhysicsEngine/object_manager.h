#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <unordered_map>
#include <memory>
#include <vector>

#include "object_bucket.h"

#define BOX_SIZE (10) // half the size of the box in each dimension

class ObjectManager {
private:
	std::unordered_map<int, ObjectBucket*> bucketMap;
	std::vector<std::shared_ptr<Object>> objects;
public:
	ObjectManager();
	~ObjectManager();
	static int getBucketID(glm::vec3 pos) {
		return ((int)(pos.x) + BOX_SIZE) + ((int)(pos.y) + BOX_SIZE) * 100 + ((int)(pos.z) + BOX_SIZE) * 10000;
	}

	void createSphere(float x, float y, float z, glm::quat r, float m, float s);

	void addObject(int id, ObjectNode* node);
	void moveObject(int oldID, int newID, ObjectNode* node);

	const std::vector<std::shared_ptr<Object>>& getObjects() const;
};

#endif