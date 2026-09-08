#include "object_bucket.h"

ObjectBucket::ObjectBucket() {
	head = nullptr;
	tail = nullptr;
}

void ObjectBucket::addObject(ObjectNode *object) {
	if (head == nullptr) {
		head = object;
		tail = object;
		object->prev = nullptr;
		object->next = nullptr;
	}
	else {
		tail->next = object;
		object->prev = tail;
		object->next = nullptr;
		tail = object;
	}
}

void ObjectBucket::removeObject(ObjectNode* object) {
	if (object == head) {
		head = object->next;
		if (head == nullptr) {
			tail = nullptr;
		}
		head->prev = nullptr;
	}
	else if (object == tail) {
		tail = object->prev;
		tail->next = nullptr;
	}
	else {
		object->prev->next = object->next;
		object->next->prev = object->prev;
	}
	object->next = nullptr;
	object->prev = nullptr;
}