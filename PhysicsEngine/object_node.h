#ifndef OBJECT_NODE_H
#define OBJECT_NODE_H

#include <iostream>

#include "object.h"

class ObjectNode {
public:
	ObjectNode* prev;
	ObjectNode* next;
	std::shared_ptr<Object> object;
	ObjectNode(ObjectNode* _prev, ObjectNode* _next, std::shared_ptr<Object> object);
};

#endif