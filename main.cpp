#include <iostream>
#include "raylib.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "xviz");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawPixel(10, 10, GREEN);
    DrawLine(20, 20, 80, 80, YELLOW);
//    DrawBezier({40, 40}, {70, 70}, {100, 100}, {130, 130}, 3, BLACK);
    DrawCircle(150, 150, 50, RED);
    DrawEllipse(300, 200, 100, 50, BROWN);
    DrawRing({400, 300}, 40, 80, 0, 360, 32, LIME);
    DrawRectangle(500, 100, 80, 120, SKYBLUE);
    DrawTriangle({600, 50}, {620, 120}, {680, 60}, VIOLET);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
