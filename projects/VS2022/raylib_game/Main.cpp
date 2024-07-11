#include "raylib.h"
#include "Game.h"
#include "FrameTimer.h";
#include "CameraManager.h"

int main()
{
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 800;
	InitWindow(windowWidth, windowHeight, "First Person");
    SetRandomSeed(0xaabbccff);
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
        
        //DrawText(TextFormat("%.3f FPS", deltaTime), 20, 20, 20, LIGHTGRAY);
        
        game.FixedUpdateCalculation(deltaTime);

        game.Update(deltaTime);
        


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        game.Draw();
        game.DrawCanvas();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    game.OnApplicationClose();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
