#include <raylib.h>
#include <iostream>

using namespace std;

int player_score = 0;
int cpu_score = 0;

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

        if(x + radius >= GetScreenWidth()){
            cpu_score++;
            resetBall();
        } //cpu wins
        
        if(x - radius <= 0){
            player_score++;
            resetBall();
        }//Player Wins
    }
    void resetBall(){
        x = GetScreenWidth() /2;
        y = GetScreenHeight() /2;
        int speed_choices[2] = {-1,1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];
    }
};

class Paddle {
protected:
    void LimitMovment(){
        if( y <= 0){
            y = 0;
        }
        if ( y + height >= GetScreenHeight()){
            y = GetScreenHeight() - height;
        }
    }
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
        LimitMovment();
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
        LimitMovment();
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main(){
    SetExitKey(KEY_NULL);
    cout << "Starting Game! \n";

    //Make Window
    const int width = 1920;
    const int height = 1080;
    InitWindow(width, height, "My Pong Game");
    SetTargetFPS(60);

    //Ball Properties
    ball.radius = 20;
    ball.x = width /2;
    ball.y = height /2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    //Player Properties
    player.width = 25;
    player.height = 120;
    player.x = width - player.width - 10;
    player.y = height /2 - player.height /2;
    player.speed = 6; 

    //Cpu Properties
    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = height /2 - cpu.height /2;
    cpu.speed = 6; 


    //Game Loop
    while(!WindowShouldClose()){
        BeginDrawing();
        //Update Objects
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        //Collision Checking
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
            ball.speed_x *= -1;
        }

        ClearBackground(BLACK);
        DrawLine(width /2, 0, width /2, height, WHITE);

        //Draw Objects 
        ball.Draw();
        player.Draw();
        cpu.Draw();

        DrawText(TextFormat("%i", cpu_score), width/4 -20 , 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 *width/4 -20 , 20, 80, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}