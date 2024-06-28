#include "raylib.h"
#include "Game.h"
#include "FrameTimer.h";

int main()
{
    Game game = Game(true);

    game.Start();

    constexpr int windowWidth = 800;
    constexpr int windowHeight = 800;
	InitWindow(windowWidth, windowHeight, "First Person");

    Camera3D camera { 0 };
    camera.position = Vector3{ 0.0f, 30.f, 30.f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);               

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


        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        

        BeginMode3D(camera);
            game.Draw();    
        EndMode3D();

        //DrawRectangle(windowWidth / 4 * 2 - 60, 100, 120, 60, RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
