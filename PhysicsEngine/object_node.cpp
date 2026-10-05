#include "object_node.h"

ObjectNode::ObjectNode(ObjectNode* _prev, ObjectNode* _next, std::shared_ptr<Object> _object) {
	prev = _prev;
	next = _next;
	object = _object;
}