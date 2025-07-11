#include "raylib.h"
#include "rlgl.h"

void DrawArrow3D(Vector3 v1, Vector3 v2, Color col) {
    DrawLine3D(v1, v2, col);
    //DrawCube(v1, 0.2, 0.2, 0.2, col);
    //DrawSphere(v2, 0.2, col);

    DrawCylinder(v2, 0.0f, 0.2f, 0.5f, 10, col);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_DOWN)) {
            camera.position.y -= 0.1;
        }
        if (IsKeyDown(KEY_UP)) {
            camera.position.y += 0.1;
        }
        if (IsKeyDown(KEY_LEFT)) {
            camera.position.x -= 0.1;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            camera.position.x += 0.1;
        }
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        //
        //

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawArrow3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{7.0f, 0.0f, 0.0f}, BLUE);
                DrawArrow3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 7.0f, 0.0f}, RED);
                DrawArrow3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 0.0f, 7.0f}, GREEN);

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

