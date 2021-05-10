#ifndef TORPEDO_H
#define TORPEDO_H

#include "utils.h"

#include <obj/model.h>

typedef struct Screw
{
    struct Model model;
    double rotation;
    int rotation_speed;
} Screw;

typedef struct Torpedo
{
    vec3 position;
    Model model;
    Screw screw;
    double heading;
    double pitch;
    double velocity;
} Torpedo;

void init_torpedo(Torpedo* torpedo);

void update_torpedo(Torpedo*, double dt);

void change_heading(Torpedo* torpedo, double dh);

void change_pitch(Torpedo* torpedo, double dp);

void change_speed(Torpedo* torpedo, double dv);

#endif /* TORPEDO_H */
