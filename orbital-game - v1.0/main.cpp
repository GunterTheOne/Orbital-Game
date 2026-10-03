#include "raylib.h"
#include <cmath>

int main() {
    InitWindow(1000, 700, "Orbital Game");
    SetTargetFPS(60);

    // Planet (fixed in place for now)
    const Vector2 planetPos = {500.0f, 350.0f};
    const float planetRadius = 40.0f;
    const float GM = 1000000.0f;   // gravity strength (G * planet mass)

    // Physics runs in small fixed steps: 4 steps per frame at 60 FPS
    const float dt = 1.0f / 240.0f;
    const int stepsPerFrame = 4;

    // Ship starts above the planet with some sideways speed
    const Vector2 startPos = {500.0f, 150.0f};
    const Vector2 startVel = {60.0f, 0.0f};
    Vector2 shipPos = startPos;
    Vector2 shipVel = startVel;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {   // press R to reset
            shipPos = startPos;
            shipVel = startVel;
        }

        for (int i = 0; i < stepsPerFrame; i++) {
            float dx = planetPos.x - shipPos.x;
            float dy = planetPos.y - shipPos.y;
            float distSq = dx * dx + dy * dy;
            float dist = std::sqrt(distSq);

            if (dist > planetRadius) {              // stop if we hit the planet
                float accel = GM / distSq;          // a = GM / r^2
                shipVel.x += accel * (dx / dist) * dt;   // velocity first...
                shipVel.y += accel * (dy / dist) * dt;
                shipPos.x += shipVel.x * dt;             // ...then position
                shipPos.y += shipVel.y * dt;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(planetPos, planetRadius, SKYBLUE);
        DrawCircleV(shipPos, 5.0f, WHITE);
        DrawText("Press R to reset", 10, 10, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
