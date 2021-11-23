//
// Created by xelada on 3/4/20.
//

#ifndef PATHTRACER_MATERIAL_H
#define PATHTRACER_MATERIAL_H


class Material {
public:
    float diffuse;
    float emissive;

    Material(float diffuse, float emissive) : diffuse(diffuse), emissive(emissive){};
};


#endif //PATHTRACER_MATERIAL_H
