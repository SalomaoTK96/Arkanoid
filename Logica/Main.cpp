#include "raylib.h"
#include "Estruturas.h"

const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;

int main() {
   
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Arkanoid 2D");
    SetTargetFPS(60);

    
    bool jogoRodando = true;

    
    Barra barra;
    barra.retangulo.posicao.x = LARGURA_TELA / 2 - 50;
    barra.retangulo.posicao.y = ALTURA_TELA - 30;
    barra.retangulo.largura = 100;
    barra.retangulo.altura = 20;
    barra.velocidadex = 5.0f;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (jogoRodando) {
           
            if (IsKeyDown(KEY_RIGHT) && barra.retangulo.posicao.x + barra.retangulo.largura < LARGURA_TELA) {
                barra.retangulo.posicao.x += barra.velocidadex;
            }
            if (IsKeyDown(KEY_LEFT) && barra.retangulo.posicao.x > 0) {
                barra.retangulo.posicao.x -= barra.velocidadex;
            }

            
            DrawRectangle(barra.retangulo.posicao.x, barra.retangulo.posicao.y, barra.retangulo.largura, barra.retangulo.altura, WHITE);
        } else {
            
            DrawText("Pressione ENTER para iniciar o jogo", 200, 300, 20, WHITE);

            if (IsKeyPressed(KEY_ENTER)) {
                jogoRodando = true; 
            }
        }

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
