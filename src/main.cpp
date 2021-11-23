#include <iostream>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <png++/png.hpp>

#include "Util.h"
#include "Material.h"
#include "Sphere.h"

struct PointLight {
    glm::vec3 origin;
    int intensity;
};

struct Scene {
    std::vector<Sphere> spheres;
    std::vector<PointLight> point_lights;
};

struct IntersectionData {
    float closest_dist;
    int closest_index;
};

void setUpScene(Scene &scene) {
    scene.spheres.emplace_back(Sphere(glm::vec3(0, 0, 5), 1, glm::vec3(255, 0, 0)));
    scene.spheres.emplace_back(Sphere(glm::vec3(0, -1001, 5), 1000, glm::vec3(255, 255, 0)));

    scene.spheres.emplace_back(Sphere(glm::vec3(-2, 10, 5), 5, glm::vec3(255, 255, 255), Material(0, 5)));

    scene.point_lights.emplace_back(PointLight({glm::vec3(-2, 5, 5), 1}));
}
glm::vec3 random_in_unit_sphere() {
    glm::vec3 randomDirection = glm::normalize(glm::vec3({
         randomDouble() * 2 - 1,
         randomDouble() * 2 - 1,
         randomDouble() * 2 - 1,
     }));
    return randomDirection;
}
glm::vec3 diffuse(glm::vec3 normal) {
    glm::vec3 dir = random_in_unit_sphere();
    if (glm::dot(normal, dir) <= 0) {
        return dir * -1.0f;
    }
    return dir;
}
IntersectionData closestIntersection(glm::vec3 &origin, glm::vec3 &direction, Scene &scene) {
    float closest_t = -1;
    int closest_i = -1;
    for(int i=0; i < scene.spheres.size(); i++) {
        float t = scene.spheres[i].intersect(origin, direction);
        if(t != -1) {
            if(t < closest_t || closest_t == -1) {
                closest_t = t;
                closest_i = i;
            }
        }
    }
    return IntersectionData({closest_t, closest_i});
}

glm::vec3 traceRay(glm::vec3 &origin, glm::vec3 &direction, Scene &scene, int depth=1) {
    IntersectionData intd = closestIntersection(origin, direction, scene);
    if(intd.closest_dist != -1.0f) { // if hit something
        if(scene.spheres[intd.closest_index].material.emissive > 0)return glm::vec3(255)*scene.spheres[intd.closest_index].material.emissive;
        glm::vec3 point = origin+(direction*intd.closest_dist);
        glm::vec3 normal = point - scene.spheres[intd.closest_index].origin;
        glm::vec3 ddir = diffuse(normal);
        return traceRay(point, ddir, scene, depth+1)*0.5f;
    }
    return glm::vec3(0, 0, 0);
}

int main() {
    int width = 600;
    int height = 600;
    float aspectRatio = height/width;
    int fov = 180;
    int samples = 100;

    Scene scene;
    setUpScene(scene);

    png::image< png::rgb_pixel > image(width, height);
    for(int y=0; y < height; y++) {
        for(int x=0; x < width; x++) {
            glm::vec3 tcolor;
            for(int s=0; s < samples; s++) {
                float nx = (x + randomDouble()) / width;
                float ny = (y + randomDouble()) / height;
                glm::vec3 direction((nx - 0.5) * (fov / 180), (ny - 0.5) * (fov / 180) * aspectRatio,
                                    1); // viewport coordinate
                direction = glm::normalize(direction);
                glm::vec3 origin = glm::vec3(0, 0, 0);
                tcolor += traceRay(origin, direction, scene);
            }
            tcolor /= samples;
            image.set_pixel(x, width-y-1, png::rgb_pixel(tcolor[0], tcolor[1], tcolor[2]));
        }
    }
    std::cout << "Writing to image..." << std::endl;
    image.write("rgb.png");
}
