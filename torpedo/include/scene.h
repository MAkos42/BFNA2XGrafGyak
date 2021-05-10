#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "torpedo.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    int t;
    double dt;
    Model h_fins;
    Model seafloor;
    Torpedo torpedo;
    Material material;
    GLuint torptex;
    GLuint sftex;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
