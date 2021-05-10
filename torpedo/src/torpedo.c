#include "torpedo.h"
#include "utils.h"

#include <GL/glut.h>
#include <math.h>

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
}

void update_torpedo(Torpedo* torpedo, double time)
{

    if (torpedo->velocity < 5)
        torpedo->velocity = 5;
    if (torpedo->velocity > 10)
        torpedo->velocity = 10;

    torpedo->position.x += torpedo->velocity * cos(deg_to_rad(torpedo->heading)) * cos(deg_to_rad(torpedo->pitch)) * time;
    torpedo->position.z += torpedo->velocity * sin(deg_to_rad(torpedo->heading)) * cos(deg_to_rad(torpedo->pitch)) * time;
    torpedo->position.y += torpedo->velocity * sin(deg_to_rad(torpedo->pitch)) * time;

    if (torpedo->position.y > 0) {
        torpedo->position.y = 0;
        if(torpedo->pitch > 5)
            torpedo->pitch -= 0.1;

    }

    torpedo->screw.rotation += torpedo->screw.rotation_speed * time;
    if (torpedo->screw.rotation > 360)
        torpedo->screw.rotation -= 360;
}

void change_heading(Torpedo* torpedo, double dh)
{
    torpedo->heading += dh;
    if (torpedo->heading < 0)
        torpedo->heading += 360;
    if (torpedo->heading >= 360)
        torpedo->heading -= 360;
}

void change_pitch(Torpedo* torpedo, double dp)
{
    if (torpedo->position.y >= 0 && dp > 0 && torpedo->pitch >= 5)
        dp = 0;
    torpedo->pitch += dp;
    if (torpedo->pitch < -15)
        torpedo->pitch = -15;
    if (torpedo->pitch > 15)
        torpedo->pitch = 15;
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
