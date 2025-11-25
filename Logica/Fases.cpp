#include "Estruturas.h"
#include "Fases.h"
#include "Bloco.h"
#include "Constantes.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>

void iniciarFase(Fase *fase, int fase_numero) {
    // Definir número de linhas e colunas baseado na fase
    if (fase_numero == 1) {
        fase->linha = 3;
        fase->coluna = 8;
    } else if (fase_numero == 2) {
        fase->linha = 4;
        fase->coluna = 8;
    } else {
        fase->linha = 5;
        fase->coluna = 8;
    }

    int total_blocos = fase->linha * fase->coluna;
    
    // Alocar memória para os blocos
    fase->blocos = (Bloco *)malloc(total_blocos * sizeof(Bloco));

    // Inicializar blocos com posições aleatórias e vidas
    int indice = 0;
    float espacamento_x = LARGURA_TELA / (fase->coluna + 1);
    float espacamento_y = 80;

    for (int i = 0; i < fase->linha; i++) {
        for (int j = 0; j < fase->coluna; j++) {
            float posx = (j + 1) * espacamento_x - TAMANHO_BLOCO_LARGURA / 2;
            float posy = 50 + i * (TAMANHO_BLOCO_ALTURA + 10);
            
            // Vida aleatória entre 1 e 3
            int vida = (rand() % 3) + 1;
            
            iniciarBloco(&fase->blocos[indice], posx, posy, vida);
            indice++;
        }
    }
}

void desenharFase(Fase *fase) {
    int total_blocos = fase->linha * fase->coluna;
    for (int i = 0; i < total_blocos; i++) {
        desenharBloco(&fase->blocos[i]);
    }
}

void gerarItem(Fase *fase, ItensEspeciais item[], int maxItens) {
    // Esta função será chamada quando um bloco for destruído
    // A lógica de geração de itens está em Itens.cpp
}

bool terminarFase(Fase *fase) {
    int total_blocos = fase->linha * fase->coluna;
    
    // Verificar se todos os blocos foram destruídos
    for (int i = 0; i < total_blocos; i++) {
        if (fase->blocos[i].ativo) {
            return false;
        }
    }
    
    // Liberar memória dos blocos
    free(fase->blocos);
    fase->blocos = NULL;
    
    return true;
}
