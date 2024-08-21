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

class Paddle {
public:
    float x, y;
    float width, height;
    int speed;

    void Draw(){
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update(){
        if (IsKeyDown(KEY_UP)){
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN)){
            y = y + speed;
        }

        Limit
    }

};

class CpuPaddle: public Paddle{
    public:
    void Update(int ball_y){
        if ( y + height/2 > ball_y){
            y = y - speed;
        }
        if (y + height/2 <= ball_y){
            y = y + speed;
        }
    }


};

Ball ball;
Paddle player;
CpuPaddle cpu;

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

    player.width = 25;
    player.height = 120;
    player.x = width - player.width - 10;
    player.y = height /2 - player.height /2;
    player.speed = 6; 

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = height /2 - cpu.height /2;
    cpu.speed = 6; 


    //Game Loop
    while(!WindowShouldClose()){
        BeginDrawing();

        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        ClearBackground(BLACK);
        DrawLine(width /2, 0, width /2, height, WHITE);

        ball.Draw();
        player.Draw();
        cpu.Draw();
        

        EndDrawing();
    }











    CloseWindow();
    return 0;
}