#include "Game.hpp"
#include <iostream>

Game::Game(): players{Paddle(0, 0), Paddle(1, 1)}, ball()
{   
    screenWidth = WIDTH;
    screenHeight = HEIGHT;
    
    InitWindow(screenWidth, screenHeight, "BorderClone");
    SetTargetFPS(60);
    // background = LoadTexture("sprites/background.png");
}

Game::~Game()
{
    // UnloadTexture(background);
	CloseWindow();
}

int	Game::menu()
{
    Texture2D title = LoadTexture("sprites/ener_fail.png");
    Rectangle source = {.x = 0, .y = 0, .width = (float) title.width, .height = (float) title.height};
    Rectangle dest = {.x = 0, .y = 0, .width = WIDTH, .height = HEIGHT};
    while (1)
    {
        BeginDrawing();
        DrawTexturePro(title, source, dest, {.x = 0, .y = 0}, 0, WHITE);
        DrawText("ONE POOOOONG", 0, 0, 50, BLACK);
        DrawText("PLAY",150, 150, 50, BLACK);
        DrawText("Exit",150, 300, 50, BLACK);
        EndDrawing();
        if(WindowShouldClose())
            return (0); 
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && menu_mouse_click())
            return (1);
    }
    UnloadTexture(title);
    return (1);
}

void Game::loop()
{
    while (1)
    {
        if(WindowShouldClose())
            return;

        //update()
        players[0].update(ball);
        players[1].update(ball);
        ball.update(players);

        // render()
        BeginDrawing();
        ClearBackground(WHITE);
        players[0].render();
        players[1].render();
        ball.render();
        EndDrawing();
    }
}


int	menu_mouse_click()
{
    int pos[2] = {GetMouseX() , GetMouseY()};
    if (pos[0] < 150 || pos[0] > 250)
        return (0);
    if (pos[1] > 150 && pos[1] < 200)
        return(1);
    else if (pos[1] > 300 && pos[1] < 350)
        return 0;
    return (0);
}