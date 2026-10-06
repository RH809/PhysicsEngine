#ifndef OBJECT_BUCKET_H
#define OBJECT_BUCKET_H

#include "object_node.h"

class ObjectBucket {
private:
	ObjectNode* head;
	ObjectNode* tail;
public:
	ObjectBucket();
	~ObjectBucket();
	void addObject(ObjectNode* object);
	void removeObject(ObjectNode* object);
};

#endif