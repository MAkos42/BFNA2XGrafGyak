#include "callbacks.h"
#include "camera.h"
#include "torpedo.h"
#include "bubble.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct {
    int x;
    int y;
} mouse_position;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&camera);
    draw_scene(&scene);
    glPopMatrix();

    if (is_preview_visible) {
        glBindTexture(GL_TEXTURE_2D, camera.helptex);
        show_texture_preview();
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
    /*
    ww = width;
    wh = height;//*/
}

void mouse(int button, int state, int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
    switch (button) {
    case 3:
        if (camera.zoom > 2.5)
            change_camera_zoom(&camera, -0.5);
        break;
    case 4:
        if (camera.zoom < 30)
            change_camera_zoom(&camera, 0.5);
        break;
    }
    glutPostRedisplay();
}

void motion(int x, int y)
{
    double sensitivity = 0.2;
    rotate_camera(&camera, (mouse_position.x - x) * sensitivity , (mouse_position.y - y) * sensitivity);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        //pitch
    case 'w':
        change_pitch(&(scene.torpedo), -20);
        break;
    case 's':
        change_pitch(&(scene.torpedo), 20);
        break;

        //heading
    case 'a':
        change_heading(&(scene.torpedo), -35);
        break;
    case 'd':
        change_heading(&(scene.torpedo), 35);
        break;

        //speed
    case 'q':
        change_speed(&(scene.torpedo), -0.1);
        break;
    case 'e':
        change_speed(&(scene.torpedo), 0.1);
        break;

    case 't':
        if (is_preview_visible) {
            is_preview_visible = FALSE;
        }
        else {
            is_preview_visible = TRUE;
        }
        break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
        //pitch
    case 'w':
    case 's':
        change_pitch(&(scene.torpedo), 0.0);
        break;

        //heading
    case 'a':
    case 'd':
        change_heading(&(scene.torpedo), 0.0);
        break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    scene.t = glutGet(GLUT_ELAPSED_TIME);
    scene.dt = (double)(scene.t - last_frame_time) / 1000;
    last_frame_time = scene.t;

    int p = scene.torpedo.velocity;
    double hdg = deg_to_rad(scene.torpedo.heading);
    int r = rand();
    if (r % 200 <= (p * p)) {
        push_bubble(&(scene.bubblelist), creat_bubble(scene.torpedo.position.x - (2.0 * cos(hdg)) + ((r % 41 - 20) / 100.0), scene.torpedo.position.y - (2.0 * sin(deg_to_rad(scene.torpedo.pitch))) + ((r % 31 - 15) / 100.0), scene.torpedo.position.z - (2.0 * sin(hdg)) + ((r % 51 - 25) / 100.0)));
    }
    r = rand();
    if (r % 200 <= (p * p)) {
        push_bubble(&(scene.bubblelist), creat_bubble(scene.torpedo.position.x - (2.0 * cos(hdg)) + ((r % 41 - 20) / 100.0), scene.torpedo.position.y - (2.0 * sin(deg_to_rad(scene.torpedo.pitch))) + ((r % 31 - 15) / 100.0), scene.torpedo.position.z - (2.0 * sin(hdg)) + ((r % 51 - 25) / 100.0)));
    }
    r = rand();
    if (r % 400 <= (p * p)) {
        push_bubble(&(scene.bubblelist), creat_bubble(scene.torpedo.position.x - (2.0 * cos(hdg)) + ((r % 41 - 20) / 100.0), scene.torpedo.position.y - (2.0 * sin(deg_to_rad(scene.torpedo.pitch))) + ((r % 31 - 15) / 100.0), scene.torpedo.position.z - (2.0 * sin(hdg)) + ((r % 51 - 25) / 100.0)));
    }


    //update_camera(&camera, elapsed_time);
    update_torpedo(&(scene.torpedo), scene.dt);
    update_bubbles(&(scene.bubblelist), scene.dt);


    glutPostRedisplay();
}
