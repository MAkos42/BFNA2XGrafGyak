#ifndef BUBBLE_H
#define BUBBLE_H

#include "utils.h"
#include "torpedo.h"

#include <GL/glut.h>
#include <obj/model.h>

typedef struct Bubble
{
	vec3 pos;
	double life;
} Bubble;

typedef struct Node {
	Bubble data;
	struct Node* next;
	struct Node* prev;
} Node;

/**
 * Creates a new bubble from torpedo position
 */
Bubble creat_bubble(double posx, double posy, double posz);

/**
 * Adds a bubble to the front of the linked list
 */
void push_bubble(struct Node** head_ref, Bubble new_data);

void update_bubbles(struct Node** head_ref, double time);

void draw_bubbles(struct Node* head_ref, const struct Model* bubble);
#endif /* BUBBLE_H */
