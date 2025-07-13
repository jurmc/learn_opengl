#include "raylib.h"
#include "raymath.h"

#include<math.h>
#include<sstream>
#include<string>
#include<iostream>

struct _Object3d {
    Vector3 pos;

    float yaw;
    float pitch;
    float roll;

    float speed;
    size_t vertex_n;
    Vector3 *vertices;
};
typedef struct _Object3d Object3d;


struct _CameraParams {
    float speed;
    float r;
    float y_angle;
};
typedef _CameraParams CameraParams;

void CameraPosition(CameraParams *params, Vector3 *pos) {
    pos->y = params->r/2;
    pos->x = params->r * sin(params->y_angle * DEG2RAD);
    pos->z = params->r * cos(params->y_angle * DEG2RAD);
}

void HandleCameraInput(CameraParams *camera_p, Camera3D *camera) {
    // Camera
    if (IsKeyDown(KEY_DOWN)) {
        camera_p->r += camera_p->speed/10.0f;
    }
    if (IsKeyDown(KEY_UP)) {
        camera_p->r -= camera_p->speed/10.0f;
    }
    if (IsKeyDown(KEY_LEFT)) {
        camera_p->y_angle -= camera_p->speed;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        camera_p->y_angle += camera_p->speed;
    }

    CameraPosition(camera_p, &camera->position);
}
 
void HandleObjectInput(Object3d *o) {
    // Object
    if (IsKeyDown(KEY_W)) {
        o->pos.z += o->speed;
    }
    if (IsKeyDown(KEY_S)) {
        o->pos.z -= o->speed;
    }
    if (IsKeyDown(KEY_A)) {
        o->pos.x -= o->speed;
    }
    if (IsKeyDown(KEY_D)) {
        o->pos.x += o->speed;
    }
    if (IsKeyDown(KEY_KP_ADD)) {
        o->pos.y -= o->speed;
    }
    if (IsKeyDown(KEY_KP_SUBTRACT)) {
        o->pos.y += o->speed;
    }

    // Yaw
    if (IsKeyDown(KEY_KP_1)) {
        o->yaw -= 1;
    }
    if (IsKeyDown(KEY_KP_3)) {
        o->yaw += 1;
    }

    // Pitch
    if (IsKeyDown(KEY_KP_8)) {
        o->pitch -= 1;
    }
    if (IsKeyDown(KEY_KP_2)) {
        o->pitch += 1;
    }

    // Roll
    if (IsKeyDown(KEY_KP_7)) {
        o->roll -= 1;
    }
    if (IsKeyDown(KEY_KP_9)) {
        o->roll += 1;
    }
}

Object3d CreateObject() {
    Object3d o;
    size_t n = 6;
    float r = 3;

    o.vertices = (Vector3 *)malloc(n * sizeof(Vector3));

    unsigned int angle = 30;
    for (size_t i = 0; i < n; ++i) {
        o.vertices[i].x = r * cos(angle * DEG2RAD);
        o.vertices[i].y = r * sin(angle * DEG2RAD);
        o.vertices[i].z = 0;
        angle += 60;
    }

    o.vertex_n= n;
    o.pos = Vector3{0.0f, 0.0f, 0.0f};

    o.yaw = 0;
    o.pitch = 0;
    o.roll = 0;

    o.speed = 0.1f;
    return o;
}

void DrawObject(Object3d *o) {
    Vector3 loc_x = {1.0f, 0.0f, 0.0f};
    Vector3 loc_y = {0.0f, 1.0f, 0.0f};
    Vector3 loc_z = {0.0f, 0.0f, 1.0f};

    Matrix pitch_rot = MatrixRotate(loc_z, o->pitch * DEG2RAD);
    loc_x = Vector3Transform(loc_x, pitch_rot);
    loc_y = Vector3Transform(loc_y, pitch_rot);

   
    Matrix yaw_rot = MatrixRotate(loc_y, o->yaw * DEG2RAD);
    loc_x = Vector3Transform(loc_x, yaw_rot);
    loc_z = Vector3Transform(loc_z, yaw_rot);

    Matrix roll_rot = MatrixRotate(loc_x, o->roll * DEG2RAD);
    loc_y = Vector3Transform(loc_y, roll_rot);
    loc_z = Vector3Transform(loc_z, roll_rot);

    DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, loc_x, GRAY);
    DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, loc_y, GRAY);
    DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, loc_z, GRAY);

    DrawSphere(o->pos, 0.3f, RED);           
    Matrix trans_m = MatrixTranslate(o->pos.x, o->pos.y, o->pos.z);

    for (size_t i = 0; i < o->vertex_n; ++i) {

        size_t i2;
        if (i == 0) {
            i2 = o->vertex_n-1;
        } else {
            i2 = i-1;
        }
        Vector3 v1 = o->vertices[i];
        Vector3 v2 = o->vertices[i2];

        Vector3 trans_v1 = v1;
        Vector3 trans_v2 = v2;

        trans_v1 = Vector3Transform(trans_v1, pitch_rot);
        trans_v2 = Vector3Transform(trans_v2, pitch_rot);   

        trans_v1 = Vector3Transform(trans_v1, yaw_rot);
        trans_v2 = Vector3Transform(trans_v2, yaw_rot);   

        trans_v1 = Vector3Transform(trans_v1, roll_rot);
        trans_v2 = Vector3Transform(trans_v2, roll_rot);   

        trans_v1 = Vector3Transform(trans_v1, trans_m);
        trans_v2 = Vector3Transform(trans_v2, trans_m);   

        DrawLine3D(v1, v2, RED);
        DrawLine3D(trans_v1, trans_v2, GREEN);
    }
}

void DebugObject(Object3d *o) {
    std::stringstream s;
    s << "Obj pos x: " << o->pos.x << ", y: " << o->pos.y << ", z: " << o->pos.z << std::endl;
    s << "Yaw: " << o->yaw << ", Pitch: " << o->pitch << ", Roll: " << o->roll << std::endl;

    DrawText(s.str().c_str(), 10, 70, 20, DARKGRAY);
}

void getOrt(Vector3 base, Vector3 *o1, Vector3 *o2) {
    if (base.x != 0) {
        o1->x = (base.y + base.z) / base.x;
        o1->y = 1;
        o1->z = 1;
    }
    if (base.y != 0) {
        o1->x = 1;
        o1->y = (base.x + base.z) / base.y;
        o1->z = 1;
    }
    if (base.z != 0) {
        o1->x = 1;
        o1->y = 1;
        o1->z = (base.x + base.y) / base.z;
    }

    Vector3 o2_temp = Vector3CrossProduct(base, *o1);
    *o2 = o2_temp;

    Vector3 temp = Vector3Normalize(*o1);
    *o1 = temp;
    temp = Vector3Normalize(*o2);
    *o2 = temp;
}

void DrawArrow3D(Vector3 v1, Vector3 v2, Color col) {
    DrawLine3D(v1, v2, col);

    Vector3 base = Vector3Subtract(v2, v1);
    Vector3 o1, o2;
    getOrt(Vector3Subtract(v2, v1), &o1, &o2);

    DrawLine3D(v2, Vector3Add(v2, o1), ORANGE);
    DrawLine3D(v2, Vector3Subtract(v2, o1), ORANGE);

    Vector3 p1 = Vector3Add(v2, o1);
    Vector3 p2 = Vector3Subtract(v2, o1);
    Vector3 p3 = Vector3Add(v2, Vector3Normalize(v2));
    DrawTriangle3D(p1, p2, p3, DARKBLUE);
    DrawTriangle3D(p1, p3, p2, DARKBLUE);
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
    CameraParams camera_p; 
    camera_p.speed = 1.0f;
    camera_p.r = 12;
    camera_p.y_angle = 0;

    Camera3D camera = { 0 };
    CameraPosition(&camera_p, &camera.position);
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Object3d object = CreateObject();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    //
    //

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        HandleCameraInput(&camera_p, &camera);
        HandleObjectInput(&object);

        // Update

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
                DrawObject(&object);
            EndMode3D();

            std::stringstream s;
            s << "camera pos: " << camera.position.x << ", " << camera.position.y << ", " << camera.position.z;
            DrawFPS(10, 10);
            DrawText(s.str().c_str(), 10, 40, 20, DARKGRAY);
            DebugObject(&object);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

