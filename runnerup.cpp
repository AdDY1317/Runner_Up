#include "raylib.h"

int main()
{   
    //window Dimension
    const int windowheight = 500;
    const int windowwidth = 500;
    //initialize Window
    InitWindow(windowwidth,windowheight,"RunnerUp");

    SetTargetFPS(60);
    //!WindowShouldClose()-----NEGATION 
    while(!WindowShouldClose())
    {
        //Game Logic Begins
        BeginDrawing();
        ClearBackground(WHITE);

        //Game Logic Ends
        EndDrawing();
    }
    CloseWindow();
}