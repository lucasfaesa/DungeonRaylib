#include "raylib.h"
#include "Game.h"
#include "FrameTimer.h";
#include "CameraManager.h"

int main()
{
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 800;
	InitWindow(windowWidth, windowHeight, "First Person");

    SetTargetFPS(60);               

    Game game = Game(true);

    FrameTimer frameTimer;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        const float deltaTime = frameTimer.GetFrameDuration();
        //Input Reading
        // ---------------------------------------------------------------------------------
        game.InputRead();
        // ---------------------------------------------------------------------------------
        

        // Update
        //----------------------------------------------------------------------------------
        
        //TODO DELTA TIME
        game.Update(deltaTime);
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        game.Draw();
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
