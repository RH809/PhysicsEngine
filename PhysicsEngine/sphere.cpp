#include <memory>
#include <vector>

#include "sphere.h"
#include "object_node.h"
#include "object_manager.h"

Sphere::Sphere(float _x, float _y, float _z, glm::quat _r, float _m, float _s, ObjectManager *_manager) : Object(_x, _y, _z, _r, _m, _s, _manager) {
    radius = DEFAULT_RADIUS * _s;
    for (int i = 0; i <= NUM_STACKS; i++) {
        float phi = glm::pi<float>() * ((float)i / NUM_STACKS);
        for (int j = 0; j <= NUM_SLICES; j++) {
            float theta = 2 * glm::pi<float>() * ((float)j / NUM_SLICES);
            float x = radius * sin(phi) * cos(theta);
            float y = radius * cos(phi);
            float z = radius * sin(phi) * sin(theta);

            float r = 1.0f - (i / (float)NUM_STACKS);
            float g = (float)i / NUM_STACKS;
            float b = (float)j / NUM_SLICES;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            vertices.push_back(r);
            vertices.push_back(g);
            vertices.push_back(b);

            if (i != NUM_STACKS && j != NUM_SLICES) {
                int current = i * (NUM_SLICES + 1) + j;
                int next = (i + 1) * (NUM_SLICES + 1) + j;

                indices.push_back(current);
                indices.push_back(next);
                indices.push_back(current + 1);

                indices.push_back(current + 1);
                indices.push_back(next);
                indices.push_back(next + 1);
            }
        }
    }
    bucketID = manager->getBucketID(position);
    setupBuffers();
}