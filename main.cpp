#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;
#define ScreenWidth 1200
#define ScreenHeight 800

#define MinWindowWidth 500
#define MinWindowHieght 800
#define FPS 120

#define NORMAL 0
#define SORTED 1
#define SELECTED 2

// Size of the Arrays
int NumberOfPillars = 50;

bool ShouldRandomizeArray = true;
bool ShouldShowMenuScreen = true;
bool BubbleSortPressed = false;

void ShowMenuScreen();

void Button(float x, float y, char *Text, Color color, bool &state);
void Bubble_Sort_Button(float tmo, char Bubb_Sort_Text[]);

void SortArray();
void DrawArray(vector<pair<int, int>> arr);
void RandomizeArray(vector<pair<int, int>> &arr);

Color FindColorForPiller(int PillerState);

vector<pair<int, int>> arr(NumberOfPillars);

void DrawArray(vector<pair<int, int>> arr)
{
    float Barwidth = (float)GetScreenWidth() / NumberOfPillars;

    for (int i = 0; i < NumberOfPillars; i++)
    {
        Color color = FindColorForPiller(arr[i].second);

        DrawRectangleV(Vector2{(float)i * Barwidth, (float)GetScreenHeight() - arr[i].first},
                       Vector2{Barwidth, (float)arr[i].first},
                       color);
    }
}

void RandomizeArray(vector<pair<int, int>> &arr)
{

    for (int i = 0; i < NumberOfPillars; i++)
        arr[i] = {GetRandomValue(40, MinWindowWidth - 80), NORMAL};
    ShouldRandomizeArray = false;

    return;
}

Color FindColorForPiller(int pillerState)
{
    switch (pillerState)
    {
    case SELECTED:
        return LIGHTGRAY;
        break;
    case SORTED:
        return GREEN;
        break;
    default:
        return GOLD;
        break;
    }
}

void ShowMenuScreen()
{

    float font = (2.5 * GetScreenWidth()) / 100;
    char Bubble_Sort_Text[] = "Bubble Sort!";
    float tmp = MeasureText(Bubble_Sort_Text, font) / 2;
    Bubble_Sort_Button(tmp, Bubble_Sort_Text);
    DrawArray(arr);
}

void Bubble_Sort_Button(float size, char Bubble_Sort_Text[])
{
    Color color;
    if (BubbleSortPressed)
        color = BLUE;
    else
        color = GREEN;

    Button(GetScreenWidth() / 2 - size, GetScreenHeight() / 20, Bubble_Sort_Text, color, BubbleSortPressed);
}

void Button(float x, float y, char *Text, Color color, bool &state)
{
    float font = (2.5 * GetScreenWidth() / 100);
    Rectangle r1 = {
        .x = x,
        .y = y,
        .width = (float)MeasureText(Text, font),
        .height = (float)font,
    };

    if (CheckCollisionPointRec(GetMousePosition(), r1))
    {
        DrawText(Text, x, y, font, RED);

        if (IsMouseButtonPressed(0))
        {

            if (state == true)

                state = false;
            else 
                state = true;

            return;
        }
    }
    else
    {
        DrawText(Text, x, y, font, color);
    }

    return;
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "Sorting Visualization Algorithm");
    SetWindowMinSize(MinWindowHieght, MinWindowHieght);

    SetTargetFPS(FPS);

    while (!WindowShouldClose())
    {
        if (ShouldShowMenuScreen)
            ShowMenuScreen();

        if (ShouldRandomizeArray)
            RandomizeArray(arr);

        BeginDrawing();

        ClearBackground(PURPLE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
