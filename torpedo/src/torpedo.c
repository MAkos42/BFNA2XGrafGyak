#include "torpedo.h"
#include "utils.h"

#include <math.h>
#include <obj/draw.h>
#include <GL/glut.h>

void init_torpedo(Torpedo* torpedo)
{
    torpedo->position.x = 0.0;
    torpedo->position.y = -3.0;
    torpedo->position.z = 0.0;
    torpedo->heading = 0.0;
    torpedo->pitch = 0.0;
    torpedo->velocity = 7;
    torpedo->screw.rotation = 0.0;
    torpedo->screw.rotation_speed = 840;
    torpedo->vfin.rotation = 0;
    torpedo->vfin.rot_target = 0;
    torpedo->hfin.rotation = 0;
    torpedo->hfin.rot_target = 0;
}

void update_torpedo(Torpedo* torpedo, double time)
{
    if (torpedo->vfin.rot_target > torpedo->vfin.rotation)
        torpedo->vfin.rotation += 20 * time;
    if (torpedo->vfin.rot_target < torpedo->vfin.rotation)
        torpedo->vfin.rotation -= 20 * time;

    if (torpedo->hfin.rot_target > torpedo->hfin.rotation)
        torpedo->hfin.rotation += 20 * time;
    if (torpedo->hfin.rot_target < torpedo->hfin.rotation)
        torpedo->hfin.rotation -= 20 * time;

    torpedo->heading += torpedo->vfin.rotation / 2.0 * time;

    if (torpedo->pitch < 10 && torpedo->hfin.rotation > 0)
        torpedo->pitch += torpedo->hfin.rotation / 2.0 * time;
    if (torpedo->pitch > -10 && torpedo->hfin.rotation < 0)
        torpedo->pitch += torpedo->hfin.rotation / 2.0 * time;


    torpedo->position.x += torpedo->velocity * cos(deg_to_rad(torpedo->heading)) * cos(deg_to_rad(torpedo->pitch)) * time;
    torpedo->position.z += torpedo->velocity * sin(deg_to_rad(torpedo->heading)) * cos(deg_to_rad(torpedo->pitch)) * time;
    torpedo->position.y += torpedo->velocity * sin(deg_to_rad(torpedo->pitch)) * time;
    if (torpedo->position.y >= 0) {
        if (torpedo->pitch > 5 && torpedo->hfin.rotation > 0)
            torpedo->pitch -= 10 * time;

        torpedo->position.y = 0;
    }

    if (torpedo->position.y <= -47.6) {
        if (torpedo->pitch < -5 && torpedo->hfin.rotation < 0)
            torpedo->pitch += 15 * time;

        torpedo->position.y = -47.6;
    }

    torpedo->screw.rotation += torpedo->screw.rotation_speed * time;
    if (torpedo->screw.rotation > 360)
        torpedo->screw.rotation -= 360;
}

void draw_torpedo(const Torpedo* torpedo)
{
    //torpedo
    glRotatef(-torpedo->vfin.rotation / 4.0, 0, 1.0, 0);
    glRotatef(-torpedo->pitch, 0, 0, 1.0);

    draw_model(&(torpedo->model));

    //screw
    glRotatef(-torpedo->screw.rotation, 1.0, 0, 0);
    draw_model(&(torpedo->screw.model));
    glRotatef(torpedo->screw.rotation, 1.0, 0, 0);


    //fins

    glTranslated(2.03968, 0, 0);
    glRotatef(torpedo->vfin.rotation, 0, 1.0, 0);
    draw_model(&(torpedo->vfin.model));
    glRotatef(-torpedo->vfin.rotation, 0, 1.0, 0);
    glTranslated(-2.03968, 0, 0);

    glTranslated(2.03968, 0, 0);
    glRotatef(torpedo->hfin.rotation, 0, 0, 1.0);
    draw_model(&(torpedo->hfin.model));
    glRotatef(-torpedo->hfin.rotation, 0, 0, 1.0);
    glTranslated(-2.03968, 0, 0);

    glRotatef(torpedo->pitch, 0, 0, 1.0);
    glRotatef(torpedo->vfin.rotation / 4.0, 0, 1.0, 0);
}

void change_heading(Torpedo* torpedo, double rt)
{
    torpedo->vfin.rot_target = rt;
}

void change_pitch(Torpedo* torpedo, double pt)
{
    if (torpedo->position.y >= 0 && pt > 0 && torpedo->pitch > 5){
        torpedo->hfin.rot_target = 5;
        return;
    }

    if (torpedo->position.y < -46 && pt < 0 && torpedo->pitch < -5) {
        torpedo->hfin.rot_target = -5;
        return;
    }

    torpedo->hfin.rot_target = pt;
}

void change_speed(Torpedo* torpedo, double dv)
{
    torpedo->velocity += dv;

    if (torpedo->velocity < 5)
        torpedo->velocity = 5;
    if (torpedo->velocity > 10)
        torpedo->velocity = 10;

    torpedo->screw.rotation_speed = 120 * torpedo->velocity;
}
