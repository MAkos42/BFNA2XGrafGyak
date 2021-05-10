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
    Model seafloor;
    Model surface;
    Torpedo torpedo;
    Material material;
    GLuint torptex;
    GLuint sftex;
    GLuint surfacetex;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene* scene);

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

void draw_sea_floor(const Scene* scene);

void draw_water_surface(const Scene* scene);

#endif /* SCENE_H */
