#include "Estruturas.h"
#include "Barra.h"
#include "raylib.h"

#define VELOCIDADE 400

void iniciarBarra(Barra *barra) {

    barra->retangulo.posicao.x = 350;
    barra->retangulo.posicao.y = 550;
    barra->retangulo.largura = 100;
    barra->retangulo.altura = 20;
    barra->velocidadex = 0;

}
void atualizarBarra(Barra *barra, float dt) {
    
    if (IsKeyDown(KEY_LEFT) || IsKeyDown (KEY_A)) {
        barra->velocidadex = -VELOCIDADE;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown (KEY_D)) {
        barra->velocidadex = VELOCIDADE;
    } else {
        barra->velocidadex = 0.0;
    }

    barra->retangulo.posicao.x += barra->velocidadex * dt;

    
    if (barra->retangulo.posicao.x < 0) {
        barra->retangulo.posicao.x = 0;
    }
    
    if (barra->retangulo.posicao.x + barra->retangulo.largura > 800) {

        barra->retangulo.posicao.x = 800 - barra->retangulo.largura;

    } 
}

void atualizarTamanho(Barra *barra, int tamanhoAd, bool adicionar)
{
    
    if (adicionar) {

        barra->retangulo.largura += tamanhoAd;

    } else {

        barra->retangulo.largura -= tamanhoAd;

    } //adicionar verificação se a barra está maior que a tela

}

void desenharBarra(Barra *barra) {

    DrawRectangle((int)barra->retangulo.posicao.x, (int)barra->retangulo.posicao.y,
                  (int)barra->retangulo.largura, (int)barra->retangulo.altura, WHITE);

    DrawRectangleLines ((int)barra->retangulo.posicao.x, (int)barra->retangulo.posicao.y,
                  (int)barra->retangulo.largura, (int)barra->retangulo.altura, BLACK);
}
