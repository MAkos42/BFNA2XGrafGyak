#include "ball.h"

void move_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
}

void start_ball(Ball* ball, float x, float y)
{
    ball->radius = 10;
    move_ball(ball, x, y);
    ball->speed_x = 200;
    ball->speed_y = 200;
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
}

