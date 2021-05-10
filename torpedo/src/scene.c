#include "scene.h"
#include "torpedo.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->seafloor), "data/plane.obj");
    init_torpedo(&(scene->torpedo));
    load_model(&(scene->torpedo.model), "data/torp.obj");
    load_model(&(scene->torpedo.screw.model), "data/screw.obj");
    load_model(&(scene->h_fins), "data/h_fins.obj");
    printf("models loaded\n");
    scene->torptex = load_texture("data/torptexture.png");
    scene->sftex = load_texture("data/seafloor.png");
    printf("textures loaded\n");

    scene->material.ambient.red = 0.7;
    scene->material.ambient.green = 0.7;
    scene->material.ambient.blue = 0.7;

    scene->material.diffuse.red = 0.0;
    scene->material.diffuse.green = 0.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.5;
    scene->material.specular.green = 0.5;
    scene->material.specular.blue = 0.5;

    scene->material.shininess = 10.0;

}

void set_lighting()
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 0.5f };
    float diffuse_light[] = { 0.0f, 0.0f, 0.0, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 2000.0f, 100.0f, 1.0f };

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
    set_lighting();

    //torpedo
    glRotatef(-scene->torpedo.pitch, 0, 0, 1.0);

    glBindTexture(GL_TEXTURE_2D, scene->torptex);
    draw_model(&(scene->torpedo.model));

    //screw
    glRotatef(-scene->torpedo.screw.rotation, 1.0, 0, 0);
    draw_model(&(scene->torpedo.screw.model));
    glRotatef(scene->torpedo.screw.rotation, 1.0, 0, 0);


    //fins
    draw_model(&(scene->h_fins));
    glRotatef(scene->torpedo.pitch, 0, 0, 1.0);

    //movement
    glRotatef(scene->torpedo.heading, 0, 1.0, 0);
    glTranslated(scene->torpedo.position.x, -scene->torpedo.position.y, scene->torpedo.position.z);
    glBindTexture(GL_TEXTURE_2D, scene->sftex);
    draw_model(&(scene->seafloor));
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
