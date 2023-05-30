#ifndef GAME_HPP
# define GAME_HPP

#include "main.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

class Game
{
private:
    int screenWidth;
    int screenHeight;
    Texture2D background;

    Paddle players[2];
    Ball ball;

public:
    Game();
    ~Game();

    int menu();
    void loop();
};

void	ft_exit();
int	menu_mouse_click();

#endif