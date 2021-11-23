//
// Created by xelada on 3/4/20.
//

#ifndef DAYTRACER_SPHERE_H
#define DAYTRACER_SPHERE_H

#include <glm/glm.hpp>
#include "Material.h"

class Sphere {
public:
    glm::vec3 origin;
    int radius;
    glm::vec3 color;
    Material material;

    float intersect(glm::vec3 &origin, glm::vec3 &direction);

    Sphere(glm::vec3 origin, int radius, glm::vec3 color) : origin(origin), radius(radius), color(color), material(Material(1, 0)){};
    Sphere(glm::vec3 origin, int radius, glm::vec3 color, Material material) : origin(origin), radius(radius), color(color), material(material){}
};


#endif //DAYTRACER_SPHERE_H
