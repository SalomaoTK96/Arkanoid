#include "Estruturas.h"
#include "Bloco.h"
#include "Constantes.h"
#include "cores.h"
#include "raylib.h"

void iniciarBloco(Bloco *bloco, float posx, float posy, int vida) {
    bloco->retangulo.posicao.x = posx;
    bloco->retangulo.posicao.y = posy;
    bloco->retangulo.largura = TAMANHO_BLOCO_LARGURA;
    bloco->retangulo.altura = TAMANHO_BLOCO_ALTURA;
    bloco->ativo = true;
    bloco->TotalDeVida = vida;
}

void desenharBloco(Bloco *bloco) {
    if (bloco->ativo) {
        Color cor;
        
        // Cores diferentes baseadas na vida
        if (bloco->TotalDeVida == 3) {
            cor = obterCorBlocoForte();
        } else if (bloco->TotalDeVida == 2) {
            cor = obterCorBlocoMedio();
        } else {
            cor = obterCorBlocoFraco();
        }

        DrawRectangle((int)bloco->retangulo.posicao.x, (int)bloco->retangulo.posicao.y,
                      bloco->retangulo.largura, bloco->retangulo.altura, cor);
        DrawRectangleLines((int)bloco->retangulo.posicao.x, (int)bloco->retangulo.posicao.y,
                           bloco->retangulo.largura, bloco->retangulo.altura, BLACK);
    }
}
