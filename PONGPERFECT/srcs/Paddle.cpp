#include "Paddle.hpp"


Paddle::Paddle(bool side, bool isbot): width(20), height(100), isbot(isbot), side(side)
{
    if (!side)
        x = 0;
    else
        x = WIDTH - width;
    y = HEIGHT / 2 - height / 2;

    width = 20;
    height = 100;
    vy = 0;
}

Paddle::~Paddle()
{
}

void Paddle::update(Ball &ball)
{
    if (isbot)
    {
        float predict = ball.y + ball.vy * fabs((x - ball.x) / ball.vx);
        if (predict < 0)
            predict = -predict;
        else if (predict > HEIGHT)
            predict = HEIGHT - (predict - HEIGHT);
        float diff = predict - (y + height / 2);
        vy *= 0.99;
        vy += diff / sqrt(5 + fabs(x - ball.x) * 50);
        if (vy > 10)
            vy = 10;
        else if (vy < -10)
            vy = -10;
    }
    else
    {
        float target = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
        if (target != 0)
            vy += (10 * target - vy) / 10;
        else
            vy *= 0.8;
    }

    y += vy;
    if (y < 0 || y > HEIGHT - height)
    {
        vy = 0;
        if (y < 0)
            y = 0;
        else if (y > HEIGHT - height)
            y = HEIGHT - height;
    }

}

void Paddle::render()
{
    DrawRectangle(x, y, width, height, BLACK);
}