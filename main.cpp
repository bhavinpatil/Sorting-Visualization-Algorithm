#include<raylib.h>
#define ScreenWidth 1200
#define ScreenHeight 800

#define MinWindowWidth 500
#define MinWindowHieght 800
#define FPS 120



int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "Sorting Visualization Algorithm");
    SetWindowMinSize(MinWindowHieght, MinWindowHieght);

    SetTargetFPS(FPS);

    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(PURPLE);

        EndDrawing();
    }

    CloseWindow();

    return 0;

}

