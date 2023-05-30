#ifndef BALL_HPP
# define BALL_HPP

#include "main.hpp"
#include "Paddle.hpp"

class Paddle;
class Ball
{
public:
    float x;
    float y;
    float vx;
    float vy;
    float spin;
    float radius;
    
    Ball();

    int update(Paddle *players);
    void render();
};

#endif