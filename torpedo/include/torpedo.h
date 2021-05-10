#ifndef TORPEDO_H
#define TORPEDO_H

#include "utils.h"

#include <obj/model.h>

typedef struct Screw
{
    struct Model model;
    double rotation;
    double rotation_speed;
} Screw;

typedef struct V_fin
{
    struct Model model;
    double rotation;
    double rot_target;
} V_fin;

typedef struct H_fin
{
    struct Model model;
    double rotation;
    double rot_target;
} H_fin;

typedef struct Torpedo
{
    vec3 position;
    Model model;
    Screw screw;
    H_fin hfin;
    V_fin vfin;
    double heading;
    double pitch;
    double velocity;
} Torpedo;

void init_torpedo(Torpedo* torpedo);

void update_torpedo(Torpedo*, double dt);

void draw_torpedo(const Torpedo* torpedo);

void change_heading(Torpedo* torpedo, double rt);

void change_pitch(Torpedo* torpedo, double pt);

void change_speed(Torpedo* torpedo, double dv);

#endif /* TORPEDO_H */
