#include "object_bucket.h"

ObjectBucket::ObjectBucket() {
	head = nullptr;
	tail = nullptr;
}

void ObjectBucket::addObject(ObjectNode *object) {
	if (head == nullptr) {
		head = object;
		tail = object;
	}
	else {
		tail->next = object;
		object->prev = tail;
		object->next = nullptr;
		tail = object;
	}
}