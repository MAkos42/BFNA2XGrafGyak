#include "init.h"

#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.0, 0.75, 1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float fogcolor[] = {0.0f, 0.0f, 0.4f, 1.0f};

    glFogf(GL_FOG_MODE, GL_EXP);
    glFogfv(GL_FOG_COLOR, fogcolor);
    glFogf(GL_FOG_DENSITY, 0.04f);
    glHint(GL_FOG_HINT, GL_NICEST);
    glFogf(GL_FOG_START, 0.0f);
    glFogf(GL_FOG_END, 1000.0f);

    glEnable(GL_FOG);


    srand(time(0));
}
