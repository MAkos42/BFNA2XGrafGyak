#include "bubble.h"
#include "texture.h"

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <obj/draw.h>

Bubble creat_bubble(double posx, double posy, double posz)
{
    Bubble new_bubble;
    new_bubble.pos.x = posx;
    new_bubble.pos.z = posz;
    new_bubble.pos.y = posy;
    new_bubble.life = 1.0;
    return new_bubble;
}

void push_bubble(struct Node** head_ref, Bubble new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;

    new_node->next = (*head_ref);
    new_node->prev = NULL;

    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;

    (*head_ref) = new_node;
}

void update_bubbles(struct Node** head_ref, double time)
{
    if (head_ref == NULL)
        return;
    if (*head_ref == NULL)
        return;
    struct Node* node = *head_ref;
    while (node != NULL) {
        node->data.life -= time;

        if(node->data.pos.y < 0)
            node->data.pos.y += 2 * time;

        if (node->next == NULL  && *head_ref != node) {
            if (node->data.life <= 0) {
                node->prev->next = NULL;
                free(node);
            }
            node = NULL;
        }
        else {
            node = node->next;
        }

    }
}

void draw_bubbles(struct Node* head_ref, const struct Model* bubble)
{
    if (head_ref == NULL)
        return;
    struct Node* node = head_ref;
    while (node != NULL) {
        glTranslated(node->data.pos.x, node->data.pos.y, node->data.pos.z);
        draw_model(bubble);
        glTranslated(-node->data.pos.x, -node->data.pos.y, -node->data.pos.z);
        node = node->next;
    }

}
