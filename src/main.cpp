#include <raylib.h>
#include <iostream>

using namespace std;

class Ball {
    public:
    float x,y;
    int speed_x, speed_y;
    int radius;

    void Draw(){
        DrawCircle(x, y, radius, WHITE);
    }
    void Update(){
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0){
            speed_y *= -1;
        }
        if(x + radius >= GetScreenWidth() || x - radius <= 0){
            speed_x *= -1;
        }        
    }
};


Ball ball;

int main(){
    cout << "Starting Game! \n";

    //Make Window
    const int width = 1280;
    const int height = 800;
    InitWindow(width, height, "My Pong Game");
    SetTargetFPS(60);


    ball.radius = 20;
    ball.x = width /2;
    ball.y = height /2;
    ball.speed_x = 7;
    ball.speed_y = 7;


    //Game Loop
    while(!WindowShouldClose()){
        BeginDrawing();

        ball.Update();

        ClearBackground(BLACK);
        DrawLine(width /2, 0, width /2, height, WHITE);

        ball.Draw();

        //Draw Paddles
        DrawRectangle(10, height /2 - 60, 25, 120, WHITE);
        DrawRectangle(width-35, height /2 - 60, 25, 120, WHITE);

        

        EndDrawing();
    }











    CloseWindow();
    return 0;
}