#include "graficos.h"
#include "Constantes.h"

// Definição das cores do jogo
Color COR_FUNDO = {20, 20, 40, 255};
Color COR_TEXTO = {255, 255, 255, 255};
Color COR_TITULO = {255, 255, 0, 255};
Color COR_BLOCO_FORTE = {255, 0, 0, 255};
Color COR_BLOCO_MEDIO = {255, 165, 0, 255};
Color COR_BLOCO_FRACO = {255, 255, 0, 255};
Color COR_BOLA = {255, 255, 0, 255};
Color COR_BARRA = {255, 255, 255, 255};
Color COR_ITEM_VIDA = {0, 255, 0, 255};
Color COR_ITEM_AUMENTAR = {0, 0, 255, 255};
Color COR_ITEM_DIMINUIR = {128, 0, 128, 255};
Color COR_ITEM_PONTOS = {255, 215, 0, 255};
Color COR_ITEM_INVERSOR = {255, 192, 203, 255};

void inicializarCores() {
    // Cores já inicializadas acima
}

void desenharTelaCarregamento() {
    ClearBackground(COR_FUNDO);
    DrawText("CARREGANDO...", LARGURA_TELA / 2 - 100, ALTURA_TELA / 2 - 30, 40, COR_TITULO);
}

void desenharFundo() {
    ClearBackground(COR_FUNDO);
    
    // Desenhar padrão de fundo (opcional)
    for (int i = 0; i < LARGURA_TELA; i += 50) {
        DrawLine(i, 0, i, ALTURA_TELA, Color{40, 40, 60, 100});
    }
    for (int i = 0; i < ALTURA_TELA; i += 50) {
        DrawLine(0, i, LARGURA_TELA, i, Color{40, 40, 60, 100});
    }
}

void desenharBorda() {
    DrawRectangleLines(0, 0, LARGURA_TELA, ALTURA_TELA, COR_TEXTO);
}

