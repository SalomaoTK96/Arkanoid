#include "raylib.h"

#include <cmath>
#include <iostream>

  const int screenWidth = 800;
  const int screenHeight = 600;

Void movimentarJogador(){ 

}

Void movimentarBola(){ 

}

Void trocarNivel(){ 

}

int main() {
  InitWindow(screenWidth, screenHeight, "raylib basic window");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("It works!", 20, 20, 20, BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
