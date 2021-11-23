//
// Created by xelada on 3/4/20.
//

#include "Sphere.h"

float Sphere::intersect(glm::vec3 &orig, glm::vec3 &direction) {
    glm::vec3 oc = orig - this->origin;
    float k1 = glm::dot(direction, direction);
    float k2 = 2 * glm::dot(oc, direction);
    float k3 = glm::dot(oc, oc) - this->radius * this->radius;
    float discriminant = k2 * k2 - 4 * k1 * k3;
    if (discriminant < 0) {
        return -1.0f;
    }
    float t1 = (-k2 - sqrt(discriminant)) / (2 * k1);
    float t2 = (-k2 + sqrt(discriminant)) / (2 * k1);
    if (t1 > 0.0001)return t1;
    if (t2 > 0.0001)return t2;
    return -1.0f;
}