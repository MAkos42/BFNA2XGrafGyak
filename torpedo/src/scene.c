#include "scene.h"
#include "torpedo.h"
#include "utils.h"

#include <GL/glut.h>
#include <math.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->seafloor), "data/plane.obj");
    load_model(&(scene->surface), "data/plane1.obj");
    init_torpedo(&(scene->torpedo));
    load_model(&(scene->torpedo.model), "data/torp.obj");
    load_model(&(scene->torpedo.screw.model), "data/screw.obj");
    load_model(&(scene->torpedo.vfin.model), "data/v_fins.obj");
    load_model(&(scene->torpedo.hfin.model), "data/h_fins.obj");
    printf("models loaded\n");
    scene->torptex = load_texture("data/torptexture.png");
    scene->sftex = load_texture("data/seafloor.png");
    scene->surfacetex = load_texture("data/calm_sea1.png");
    printf("textures loaded\n");

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 10.0;

}

void set_lighting(const Scene* scene)
{
    float ambient_light[] = { 0.3f, 0.4f, 0.5f, 1.0f };
    float diffuse_light[] = { 0.3f, 0.8f, 1.0, 1.0f };
    float specular_light[] = { 0.4f, 0.4f, 1.0f, 1.0f };
    float position[] = { 5000.0f, 20000.0f, 10000.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(scene);

    //draw torpedo
    glBindTexture(GL_TEXTURE_2D, scene->torptex);
    draw_torpedo(&(scene->torpedo));

    //draw seafloor
    glBindTexture(GL_TEXTURE_2D, scene->sftex);
    draw_sea_floor(scene);

    //draw water surface
    glBindTexture(GL_TEXTURE_2D, scene->surfacetex);
    draw_water_surface(scene);

}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void draw_sea_floor(const Scene* scene)
{
    glRotatef(scene->torpedo.heading, 0, 1.0, 0);
    glTranslated(scene->torpedo.position.x, -scene->torpedo.position.y, scene->torpedo.position.z);
    draw_model(&(scene->seafloor));
    glTranslated(-scene->torpedo.position.x, scene->torpedo.position.y, -scene->torpedo.position.z);
    glRotatef(-scene->torpedo.heading, 0, 1.0, 0);
}

void draw_water_surface(const Scene* scene)
{
    glRotatef(scene->torpedo.heading, 0, 1.0, 0);
    glTranslated(scene->torpedo.position.x, -scene->torpedo.position.y, scene->torpedo.position.z);
    draw_model(&(scene->surface));
    glTranslated(-scene->torpedo.position.x, scene->torpedo.position.y, -scene->torpedo.position.z);
    glRotatef(-scene->torpedo.heading, 0, 1.0, 0);
}
