#include <raylib.h>
#include <iostream>

using namespace std;

int main(){
    cout << "Starting Game! \n";

    //Make Window
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "My Pong Game");
    SetTargetFPS(60);


    //Game Loop
    while(!WindowShouldClose){
        BeginDrawing();

        EndDrawing();
    }











    CloseWindow();
    return 0;
}