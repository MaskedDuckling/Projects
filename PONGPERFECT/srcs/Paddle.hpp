#ifndef PADDLE_HPP
# define PADDLE_HPP

#include "main.hpp"
#include "Ball.hpp"

class Ball;
class Paddle
{
public:
    float x;
    float y;
    float vy;
    float width;
    float height;
    bool isbot;
    bool side;

    Paddle(bool side, bool isbot);
    ~Paddle();

    void update(Ball &ball);
    void render();
};

#endif
