#include "Ball.hpp"

Ball::Ball()
{
    x = WIDTH / 2;
    y = HEIGHT / 2;
    vx = 10;
    vy = 10;
    radius = 10;
    spin = 0;
}

void Ball::render()
{

    float posx = spin * vy;
    float posy = -spin * vx;
    DrawCircle(x - posx, y - posy, radius + 5 * fabs(spin), RED);
    DrawCircle(x + posx, y + posy, radius + 5 * fabs(spin), BLUE);
    DrawCircle(x, y, radius, BLACK);
}
/*
(vx)   ( 0)    (vy * sp)
(vy) ^ ( 0)  = (-vx * sp)
( 0)   (sp)    (0)
*/

int Ball::update(Paddle *players)
{
    spin *= 0.999;
    vx += spin * vy * 0.01;
    vy += -spin * vx * 0.01;
    x += vx;
    y += vy;
    if (y < 0)  {
        vy = fabs(vy);
        spin = 0;
    }
    else if (y > HEIGHT)    {
        vy = -fabs(vy);
        spin = 0;
    }
    
    if (x < 0 || x > WIDTH) {
        x = WIDTH / 2;
        y = HEIGHT / 2;
        vx = 10;
        vy = 10;
        spin = 0;
        if (x < 0)
            return (1);
        else if (x > WIDTH)
            return (-1);
    }
    else if (x < players[0].width + radius)
    {
        float diff = y - (players[0].y + players[0].height / 2);
        if (fabs(diff) < radius + players[0].height / 2)
        {
            spin += (players[0].vy - vy) / 20;
            vx = fabs(vx) + 1;
            vy += (players[0].vy - vy) / 2;
            // vy = diff / 10;
        }
    }
    else if (x > WIDTH - players[1].width - radius)
    {
        float diff = y - (players[1].y + players[1].height / 2);
        if (fabs(diff) < radius + players[1].height / 2)
        {
            spin += (vy - players[1].vy) / 20;
            vx = -fabs(vx) - 1;
            vy += (players[1].vy - vy) / 2;
            // vy = diff / 10;
        }
    }
    if (spin > 1)
        spin = 1;
    else if (spin < -1)
        spin = -1;

    return (0);
}
