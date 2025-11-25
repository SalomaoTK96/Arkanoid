#include "Estruturas.h"
#include "Itens.h"
#include "Constantes.h"
#include "cores.h"
#include "raylib.h"

void iniciarItem(ItensEspeciais *item, int tipo, float posx, float posy) {
    item->posicao_do_item.x = posx;
    item->posicao_do_item.y = posy;
    item->tipo = tipo;
    item->velocidadey = 150.0f;
    item->esta_Ativo = true;
}

void desenharItem(ItensEspeciais *item) {
    if (item->esta_Ativo) {
        Color cor;
        
        // Cores diferentes para cada tipo de item
        switch (item->tipo) {
            case ITEM_VIDA:
                cor = obterCorItemVida();
                break;
            case ITEM_AUMENTAR_BARRA:
                cor = obterCorItemAumentar();
                break;
            case ITEM_DIMINUIR_BARRA:
                cor = obterCorItemDiminuir();
                break;
            case ITEM_PONTOS_EXTRAS:
                cor = obterCorItemPontos();
                break;
            case ITEM_INVERSOR:
                cor = obterCorItemInversor();
                break;
            default:
                cor = WHITE;
        }

        DrawRectangle((int)item->posicao_do_item.x - 5, (int)item->posicao_do_item.y - 5, 10, 10, cor);
        DrawRectangleLines((int)item->posicao_do_item.x - 5, (int)item->posicao_do_item.y - 5, 10, 10, BLACK);
    }
}

void atualizarItem(ItensEspeciais *item) {
    if (item->esta_Ativo) {
        item->posicao_do_item.y += item->velocidadey * GetFrameTime();

        // Desativar item se sair da tela
        if (item->posicao_do_item.y > ALTURA_TELA) {
            item->esta_Ativo = false;
        }
    }
}

void efeitoItem(ItensEspeciais *item, Jogador *jogador, Barra *barra) {
    if (!item->esta_Ativo) return;

    switch (item->tipo) {
        case ITEM_VIDA:
            jogador->vidas_jogador++;
            break;
        case ITEM_AUMENTAR_BARRA:
            if (barra->retangulo.largura < 200) {
                barra->retangulo.largura += 20;
            }
            break;
        case ITEM_DIMINUIR_BARRA:
            if (barra->retangulo.largura > 40) {
                barra->retangulo.largura -= 20;
            }
            break;
        case ITEM_PONTOS_EXTRAS:
            jogador->pontuacao += 500;
            break;
        case ITEM_INVERSOR:
            jogador->pontuacao = (jogador->pontuacao > 0) ? 0 : jogador->pontuacao;
            break;
    }

    item->esta_Ativo = false;
}

