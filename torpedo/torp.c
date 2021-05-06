
#include "model.h"
#include "draw.h"

#include <SOIL/SOIL.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

//window size
int ww = 960;
int wh = 720;

//camera
double rotateX;
double rotateY;

//idő
int t;
double dt;

//movement
double posx = 0.0;
double posy = -5.0;
double posz = 0.0;
double hdg = 0.0;
double pitch = 0.0;

//propeller animáció
double screw_rot;
double rot_speed = 800;

//objects
struct Model body;
struct Model screw;
struct Model v_fins;
struct Model h_fins;
struct Model sf;
struct Model seafloor[5][5];


//textures
GLuint torptex;
GLuint sftex;


typedef GLubyte Pixel[3]; /*represents red green blue*/

void draw_seafloor(){
	int i;
	int j;
	for(i = 4; i < 0; i--)
		for(j = 4; j < 0 ; j--)
			draw_model(&seafloor[i][j]);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    GLfloat light_position[] = {300, 5000, -200, 0.};
    GLfloat light_color[] = {1, 1, 1, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, light_color);

    glRotatef(-rotateX, 0, 1.0, 0);
    glRotatef(rotateY, sin(rotateX*M_PI/180.0), 0, cos(rotateX*M_PI/180.0));
	
	
    glRotatef(-pitch, 0, 0, 1.0);
	glBindTexture(GL_TEXTURE_2D, torptex);
	
    draw_model(&body);
	
	
    glRotatef(screw_rot, 1.0, 0, 0);
    draw_model(&screw);
    glRotatef(-screw_rot, 1.0, 0, 0);//*/
	
    //draw_model(&h_fins);
	
    glRotatef(pitch, 0, 0, 1.0);
	
    glRotatef(-hdg, 0, 1.0, 0);
	glTranslated(posx, -posy, posz);
	
	glBindTexture(GL_TEXTURE_2D, sftex);
    draw_model(&sf);
	
	
	draw_seafloor();

    glPopMatrix();

    glutSwapBuffers();
	
	
    glutPostRedisplay();
}

void idle()
{
	//calculate time delta
	int nt = glutGet(GLUT_ELAPSED_TIME);
	dt = (nt-t)/1000.0;
	t = nt;
	
	//movement
	posx += rot_speed/120.0 * cos(hdg*M_PI/180) * cos(pitch*M_PI/180) * dt;
	posz += rot_speed/120.0 * -sin(hdg*M_PI/180) * cos(pitch*M_PI/180) * dt;
	posy += rot_speed/120.0 * sin(pitch*M_PI/180) * dt;
	//printf("x:%lf z:%lf\n hdg:%lf spd:n/a\n",posx,posz,hdg);
	
	//screw animation
	screw_rot -= rot_speed*dt;
	if(screw_rot < 0)
		screw_rot += 360.0;
}

void reshape(GLsizei width, GLsizei height)
{
    glViewport (0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
	ww = width;
	wh = height;
}

void mouseHandler(int button, int state, int x, int y)
{
}

void motionHandler(int x, int y)
{
    rotateX = x*720/(double)ww;
    rotateY = (y-270)*160/(double)wh;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key){
		//speed
		case 'w':
			if(rot_speed <= 1200)
				rot_speed+= 50;
			break;
		case 's':
			if(rot_speed >= 600)
				rot_speed-= 50;
			break;
	}
	
    glutPostRedisplay();
}

void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		//pitch
		case GLUT_KEY_UP:
			if (pitch > -10)
				pitch -= 100*dt;
			break;
		case GLUT_KEY_DOWN:
			if (pitch < 10)
				pitch += 100*dt;
			break;
		//heading
		case GLUT_KEY_LEFT:
			hdg += 100*dt;
			if (hdg >= 360)
				hdg -=360;
			break;
		case GLUT_KEY_RIGHT:
			hdg -= 100*dt;
			if (hdg < 0)
				hdg += 360;
			break;
	}

	glutPostRedisplay();
}

GLuint initialize_texture(char* filename)
{
    GLuint texture_name;
	
    glGenTextures(1, &texture_name);
	glBindTexture(GL_TEXTURE_2D, texture_name); 

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    int width;
    int height;

    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_AUTO);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (Pixel*)image);


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    return texture_name;
}

void create_seafloor()
{
	int i;
	int j;
	for(i = 0; i < 5; i++){
		for(j = 0; j < 5; j++){
			printf("[%d,%d]\n",i,j);
			load_model("data/plane.obj", &seafloor[i][j]);
			repos_model(&seafloor[i][j],(j-2)*512,0,(i-2)*512);
			print_bounding_box(&seafloor[i][j]);
		}
	}
}

void initialize()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.529, 0.808, 0.922, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        6.0, 2.0, 0.0, // eye
        0.0, 0.0, 0.0, // look at
        0.0, 1.0, 0.0  // up
    );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glClearDepth(1.0);

    torptex = initialize_texture("data/torptexture.png");
	sftex = initialize_texture("data/seafloor.png");
	
	
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	
	
	t = glutGet(GLUT_ELAPSED_TIME);
}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    rotateX = 0.0;
    rotateY = 0.0;

    load_model("data/torp.obj", &body);
    print_model_info(&body);
    print_bounding_box(&body);
	
    load_model("data/screw.obj", &screw);
    print_model_info(&screw);
    print_bounding_box(&screw);//*/
	/*
    load_model("data/h_fins.obj", &h_fins); //why arent these objects showing?!
    print_model_info(&h_fins);
    print_bounding_box(&h_fins);//*/
	
	//create_seafloor();
	
	load_model("data/plane1.obj", &sf);
    print_model_info(&sf);
    print_bounding_box(&sf);//*/
	
	
    glutInit(&argc, argv);

    glutInitWindowSize(ww, wh);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    int window = glutCreateWindow("GLUT Window");
    glutSetWindow(window);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseHandler);
    glutPassiveMotionFunc(motionHandler);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialInput);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
