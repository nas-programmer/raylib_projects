#include "raylib.h"

int button(int x, int y, const char *text, int *begin){    
    struct Rectangle r1 = {.x = x - 10, .y = y - 5, .width= MeasureText(text, 80) + 20, .height= 50};
    if (CheckCollisionPointRec(GetMousePosition(), r1)){
        DrawText(text, x - 80, y-25, 100, RED);
        if (IsMouseButtonPressed(0)){
            if (*begin == 0){
                *begin = 1;
            }else if(*begin == 1){
                *begin = 0;
            }
            return 1;
        }
    }else{
        DrawText(text, x, y, 80, RED);
        return 0;
    }
    return 0;
}

int partition(int *arr, int start, int end, int *states){
    for(int i = start; i < end; i++){
        states[i] = 0;
    }
    int newStart = start;
    int pivot = arr[end];
    states[start] = 0;
    
    for (int i = start; i < end; i++){
        if (pivot > arr[i]){
            int temp = arr[newStart];
            arr[newStart] = arr[i];
            arr[i] = temp;
            states[newStart] = 1;
            newStart += 1;
            states[newStart] = 0;
        }
    }
    int temp = arr[newStart];
    arr[newStart] = arr[end];
    arr[end] = temp;
    return newStart;
}


int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Quick Sort");

    SetTargetFPS(60);               // Set the application to run at 60 frames-per-second
    
    //Width of the bars
    int n = 4;
    
    //Number of bars
    const int w = 200;
    
    //Array of bars and their state 
    int h_arr[w], states[w];
    
    int counter = 0, flag= 0, id1 = 0, id2 = 0, begin = 0;
    int *countptr = &counter, *flagptr = &flag, *beginptr = &begin;
     
    int end = w - 1;
    int start = 0;
    int size = end - start + 1;
    int stack[size];

    int top = 0;
    stack[top] = 0;
    top += 1;
    stack[top] = end;

    int j = 0;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (id1 ==1){
            if (top >= 0){
                end = stack[top];
                top -= 1;
                start = stack[top];
                top -= 1;
                int p = partition(h_arr, start, end, states);
                states[p] = 1;
                
                if (p-1 > start){
                    top += 1;
                    stack[top] = start;
                    top += 1;
                    stack[top] = p - 1;
                }

                if (p+1 < end){
                    top += 1;
                    stack[top] = p+1;
                    top += 1;
                    stack[top] = end;
                }
            }else {
                if (j < w){
                    states[j] = 2;
                    j+=1;
                }else{
                    flag= 1;
                }
            }
        }
        // Draw
        //----------------------------------------------------------------------------------
        Color color = WHITE;
        BeginDrawing();
            ClearBackground(BLACK);
            if (begin == 1){
                for (int i = 0; i < w; i++){
                    if (states[i] == 0){
                        color = RED;
                    }else if (states[i] == 2){
                        color = GREEN;
                    }else {
                        color = WHITE;
                    }
                    DrawRectangle(i*n, screenHeight - h_arr[i], n, h_arr[i], color);
                }
                if (flag == 1){
                   if (button(screenWidth/2 - 100, screenHeight/2, "Done", beginptr) == 1){
                       CloseWindow();
                       return 0;
                   }
                    
                }
            }else {
                for (int i = 0; i < w ; i++){
                    h_arr[i] = GetRandomValue(10, 440);
                    states[i] = 1;
                }
                int counter = 0, flag= 0;
                int *countptr = &counter, *flagptr = &flag;
                
                id1 = button(screenWidth/4, screenHeight/3, "Quick Sort", beginptr);
            }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
