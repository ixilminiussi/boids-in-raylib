#include "raylib.h"
#include "include/boid.h"
#include <iostream>

using namespace std;

int main() {
    InitWindow(1000, 600, "My first Raylib window!");
    SetTargetFPS(60);

    for (float x = 0; x < 1000; x += 40) {
        for (float y = 0; y < 600; y += 40) {
            new Boid(Vector2{ x, y });
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if (IsMouseButtonPressed(0)) {
            for (int i = 0; i < 10; i++) {
                new Boid(Vector2{ (float)GetMouseX(), (float)GetMouseY() });
            }
        }
        for (auto b : Boid::boids) {
            b -> update();
            b -> render();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}