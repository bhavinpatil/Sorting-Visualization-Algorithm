#include <raylib.h>
#include <bits/stdc++.h>

using namespace std;
#define ScreenWidth 1200
#define ScreenHeight 800

#define MinWindowWidth 500
#define MinWindowHieght 800
#define FPS 120

// Piller States:
#define NORMAL 0
#define SORTED 1
#define SELECTED 2

// Size of the Arrays
int NumberOfPillars = 50;

// Sorting Speed:
int SortingSpeed = 61;

// Sorting:
void Bubble_sort(vector<pair<int, int>> &arr);

// Bools:
bool ShouldRandomizeArray = true;
bool ShouldShowMenuScreen = true;
bool ShouldShowStartOptions = false;
bool ShouldStartSorting = false;
bool ShouldShowEndingScreen = false;

bool BubbleSortPressed = false;

bool addSpeed = false;
bool subSpeed = false;
bool addSize = false;
bool subSize = false;
bool NormalSize = false;
bool NormalSpeed = false;

// Screens:
void ShowMenuScreen();
void ShowStartOptions();
void ShowEndingScreen();

void Button(float x, float y, char *Text, Color color, bool &state);
void Bubble_Sort_Button(float tmo, char Bubb_Sort_Text[]);
void Start_Button(float size, float font, char Start[]);
void ChangeSpeed(char operation, int &val);
void ChangeSize(char operation, int &val);

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

void RandomizeArray(vector<pair<int, int>> &arr) // Generating Random Pillers
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
        return YELLOW;
        break;
    case SORTED:
        return GREEN;
        break;
    default:
        return WHITE;
        break;
    }
}

// Screens:
void ShowMenuScreen()
{

    float font = (2.5 * GetScreenWidth()) / 100;
    char Bubble_Sort_Text[] = "Bubble Sort!";
    float tmp = MeasureText(Bubble_Sort_Text, font) / 2;
    Bubble_Sort_Button(tmp, Bubble_Sort_Text);
    DrawArray(arr);
}

void ShowStartOptions()
{
    float font = (2.5 * GetScreenWidth()) / 100;

    char StartText[] = "Start Sorting!";
    float tmp = (25 * GetScreenWidth()) / 100;
    Start_Button(tmp, font, StartText);

    // Button for Randomizing Array
    tmp += MeasureText(StartText, font) + 75;
    char RandomizeArrayText[] = "Randomize Array!";
    Button(tmp, GetScreenHeight() / 20 + font * 2, RandomizeArrayText, DARKGRAY, ShouldRandomizeArray);

    addSpeed = false;
    subSpeed = false;
    addSize = false;
    subSize = false;

    NormalSize = false;
    NormalSpeed = false;

    // Button for Speed of Sorting the Pillers
    tmp = (84.2 * GetScreenWidth()) / 100;
    char TimeButtonText[] = "Speed";
    Button(tmp, GetScreenHeight() / 20 + font * 2, TimeButtonText, BLUE, NormalSpeed);
    if (NormalSpeed)
    {
        ChangeSpeed('/', SortingSpeed);
        return;
    }

    // Button to Increase the Speed of Sorting
    tmp += MeasureText(TimeButtonText, font) + 20;
    char SpeedPlusButtonText[] = "+";
    Button(tmp, GetScreenHeight() / 20 + font * 2, SpeedPlusButtonText, ORANGE, addSpeed);
    if (addSpeed)
    {
        ChangeSpeed('+', SortingSpeed);
        return;
    }

    // Button to Decrease the Speed of Sorting
    tmp += MeasureText(SpeedPlusButtonText, font) + 20;
    char SpeedMinusButtonText[] = "-";
    Button(tmp, GetScreenHeight() / 20 + font * 2, SpeedMinusButtonText, ORANGE, addSpeed);
    if (subSpeed)
    {
        ChangeSpeed('-', SortingSpeed);
        return;
    }

    // Button for Size of Pillers
    tmp = (5 * GetScreenWidth()) / 100;
    char SizeButtonText[] = "Size";
    Button(tmp, GetScreenHeight() / 20 + font * 2, SizeButtonText, BLUE, NormalSize);
    if (NormalSize)
    {
        ChangeSize('/', NumberOfPillars);
        return;
    }

    // Button to Increase Size of Pillers
    tmp += MeasureText(SizeButtonText, font) + 20;
    char SizePlusButton[] = "+";
    Button(tmp, GetScreenHeight() / 20 + font * 2, SizePlusButton, ORANGE, addSize);
    if (addSize)
    {
        ChangeSize('+', NumberOfPillars);
        return;
    }

    // Button to Decrease Size of Pillers
    tmp += MeasureText(SizePlusButton, font) + 20;
    char SizeMinusButton[] = "-";
    Button(tmp, GetScreenHeight() / 20 + font * 2, SizeMinusButton, ORANGE, subSize);
    if (subSize)
    {
        ChangeSize('-', NumberOfPillars);
        return;
    }
}

void ShowEndingScreen()
{
    DrawArray(arr);
    ShouldShowMenuScreen = true;
    ShouldShowStartOptions = false;
}

// Funtion to change the speed of sorting
void ChangeSpeed(char operation, int &val)
{
    switch (operation)
    {
    case '-':
        val = val - 10 > 0 ? val - 10 : val;
        break;
    case '+':
        val += 10;

    default:
        val = 61;
        break;
    }
    SetTargetFPS(SortingSpeed);
}

// Funtion to change the Size of Pillers
void ChangeSize(char operation, int &val)
{
    switch (operation)
    {
    case '-':
        if (val > 5)
        {
            val -= 5;
            for (int i = 0; i < 5; i++)
                arr.pop_back();
        }
        break;

    case '+':
        val += 5;
        for (int i = 0; i < 5; i++)
            arr.push_back({GetRandomValue(40, MinWindowWidth - 80), NORMAL});
        break;

    default:
        while (NumberOfPillars > 50)
        {
            NumberOfPillars--;
            arr.pop_back();
        }
        while (NumberOfPillars < 50)
        {
            NumberOfPillars++;
            arr.push_back({GetRandomValue(40, MinWindowWidth - 80), NORMAL});
        }

        break;
    }

    for (int i = 0; i < NumberOfPillars; i++)
    {
        arr[i].second = NORMAL;
    }

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

// Buttons:

void Start_Button(float size, float font, char Start[])
{

    Button(size, GetScreenWidth() / 20 + font * 2, Start, DARKGRAY, ShouldStartSorting);
    return;
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

void SortArray()
{
    Bubble_sort(arr);
    DrawArray(arr);
}

// Bubble Sort:
void Bubble_sort(vector<pair<int, int>> &arr)
{
    int endingPoint = NumberOfPillars;

    bool Swapped;

    do
    {
        Swapped = false;
        for (int i = 0; i < endingPoint - 1; i++)
        {
            arr[i].second = SELECTED;
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                Swapped = true;
            }

            BeginDrawing();
            ClearBackground(BLACK);

            for (int j = NumberOfPillars - 1; j >= endingPoint; j--)
                arr[j].second = SORTED;
            DrawArray(arr);

            for (int k = i; k >= 0; k--)
                arr[k].second = NORMAL;

            EndDrawing();
        }
        endingPoint--;
    } while (Swapped);

    for (int i = NumberOfPillars - 1; i >= 0; i--)
        arr[i].second = SORTED;
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

        ShouldShowStartOptions = false;
        if (BubbleSortPressed)
            ShouldShowStartOptions = true;

        if (ShouldShowStartOptions)
            ShowStartOptions();

        if (ShouldRandomizeArray)
            RandomizeArray(arr);

        if (ShouldStartSorting)
        {
            ShouldShowMenuScreen = false;
            ShouldShowStartOptions = false;
            SortArray();

            ShouldStartSorting = false;
            ShouldShowEndingScreen = true;
        }

        if (ShouldShowEndingScreen)
            ShowEndingScreen();

        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
