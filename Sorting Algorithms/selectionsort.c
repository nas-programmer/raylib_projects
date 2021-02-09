#include "raylib.h"

/* void selectionSort(int *h_arr, int *states, int *flag, int w, int *counter){
    if ((*counter) < w){
        int min_idx = (*counter);
        for (int j = (*counter)+1; j < w ; j++){
            if (h_arr[min_idx] > h_arr[j]){
                states[j] = 0;
                min_idx = j;
            }else {
                states[j] = 1;
                states[min_idx] = 1;
            }
         
        }
        int temp = h_arr[(*counter)];
        h_arr[(*counter)] = h_arr[min_idx];
        h_arr[min_idx] = temp;
    }else {
        (*flag) = 1;
    }
    (*counter) ++;
    if ((*counter) - 1 < w){
        states[(*counter) - 1] = 2;
    }
} */


int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Selection Sort");

    SetTargetFPS(60);               // Set the application to run at 60 frames-per-second
    
    //Width of the bars
    int n = 4;
    
    //Number of bars
    const int w = 200;
    
    //Array of bars and their state 
    int h_arr[w], states[w];
    
    //Setting the height of bars
    for (int i = 0; i < w ; i++){
        h_arr[i] = GetRandomValue(10, 440);
        states[i] = 1;
    }
    int counter = 0, flag= 0;
    //int *countptr = &counter, *flagptr = &flag;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (counter < w){
            int min_idx = counter;
            for (int j = counter+1; j < w ; j++){
                if (h_arr[min_idx] > h_arr[j]){
                    states[j] = 0;
                    min_idx = j;
                }else {
                    states[j] = 1;
                    states[min_idx] = 1;
                }
             
            }
            int temp = h_arr[counter];
            h_arr[counter] = h_arr[min_idx];
            h_arr[min_idx] = temp;
        }else {
            flag = 1;
        }
        counter ++;
        if (counter - 1 < w){
            states[counter - 1] = 2;
        }
        //selectionSort(h_arr, states, flagptr, w, countptr);
        // Draw
        //----------------------------------------------------------------------------------
        Color color = WHITE;
        BeginDrawing();
            ClearBackground(BLACK);
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
                DrawText("Done", screenWidth/2 - 60, screenHeight/2, 50, RED);
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
