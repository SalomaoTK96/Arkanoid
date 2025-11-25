#include "Ranking.h"
#include "Constantes.h"
#include "cores.h"
#include "raylib.h"
#include <cstdio>
#include <cstring>

void iniciarRanking(Ranking *ranking, char *arquivo) {
    ranking->total_jogadores = 0;
    
    // Inicializar todos os jogadores com valores padrão
    for (int i = 0; i < MAX_JOGADORES; i++) {
        strcpy(ranking->jogador[i].nome, "---");
        ranking->jogador[i].pontuacao = 0;
        ranking->jogador[i].tempo = 0;
        ranking->jogador[i].vidas_jogador = 0;
    }

    carregarRanking(ranking);
}

void atualizarRanking(Ranking *ranking, Jogador *jogador) {
    // Encontrar a posição correta para inserir o novo jogador
    int posicao = ranking->total_jogadores;

    // Procurar a posição baseada na pontuação
    for (int i = 0; i < ranking->total_jogadores; i++) {
        if (jogador->pontuacao > ranking->jogador[i].pontuacao) {
            posicao = i;
            break;
        }
    }

    // Se o ranking está cheio e a pontuação é menor que a última, não adicionar
    if (ranking->total_jogadores >= MAX_JOGADORES && posicao == ranking->total_jogadores) {
        return;
    }

    // Deslocar os jogadores para baixo
    if (ranking->total_jogadores < MAX_JOGADORES) {
        ranking->total_jogadores++;
    }

    for (int i = ranking->total_jogadores - 1; i > posicao; i--) {
        ranking->jogador[i] = ranking->jogador[i - 1];
    }

    // Inserir o novo jogador
    ranking->jogador[posicao] = *jogador;

    salvarRanking(ranking);
}

void desenharRanking(Ranking *ranking) {
    bool voltando = false;

    while (!voltando && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(obterCorFundo());

        DrawText("RANKING", LARGURA_TELA / 2 - 80, 30, 50, obterCorTitulo());

        // Desenhar cabeçalho
        DrawText("Pos", 50, 100, 20, obterCorTexto());
        DrawText("Nome", 120, 100, 20, obterCorTexto());
        DrawText("Pontuacao", 300, 100, 20, obterCorTexto());
        DrawText("Tempo", 500, 100, 20, obterCorTexto());

        // Desenhar ranking
        for (int i = 0; i < ranking->total_jogadores && i < MAX_JOGADORES; i++) {
            char posicao[10];
            sprintf(posicao, "%d", i + 1);
            
            char pontuacao_str[20];
            sprintf(pontuacao_str, "%d", ranking->jogador[i].pontuacao);
            
            char tempo_str[20];
            sprintf(tempo_str, "%ds", ranking->jogador[i].tempo);

            DrawText(posicao, 50, 140 + i * 30, 20, obterCorTexto());
            DrawText(ranking->jogador[i].nome, 120, 140 + i * 30, 20, obterCorTexto());
            DrawText(pontuacao_str, 300, 140 + i * 30, 20, obterCorTexto());
            DrawText(tempo_str, 500, 140 + i * 30, 20, obterCorTexto());
        }

        DrawText("Pressione ESC para voltar", LARGURA_TELA / 2 - 150, 550, 20, LIGHTGRAY);

        if (IsKeyPressed(KEY_ESCAPE)) {
            voltando = true;
        }

        EndDrawing();
    }
}

void salvarRanking(Ranking *ranking) {
    FILE *arquivo = fopen(ARQUIVO_RANKING, "w");
    
    if (arquivo == NULL) {
        return;
    }

    fprintf(arquivo, "%d\n", ranking->total_jogadores);

    for (int i = 0; i < ranking->total_jogadores; i++) {
        fprintf(arquivo, "%s %d %d\n", 
                ranking->jogador[i].nome,
                ranking->jogador[i].pontuacao,
                ranking->jogador[i].tempo);
    }

    fclose(arquivo);
}

void carregarRanking(Ranking *ranking) {
    FILE *arquivo = fopen(ARQUIVO_RANKING, "r");
    
    if (arquivo == NULL) {
        ranking->total_jogadores = 0;
        return;
    }

    fscanf(arquivo, "%d\n", &ranking->total_jogadores);

    for (int i = 0; i < ranking->total_jogadores && i < MAX_JOGADORES; i++) {
        fscanf(arquivo, "%s %d %d\n",
               ranking->jogador[i].nome,
               &ranking->jogador[i].pontuacao,
               &ranking->jogador[i].tempo);
    }

    fclose(arquivo);
}

