#include "raylib.h"
#include "Estruturas.h"
#include "Constantes.h"
#include "Bola.h"
#include "Barra.h"
#include "Bloco.h"
#include "Fases.h"
#include "Itens.h"
#include "Jogador.h"
#include "Menu.h"
#include "Ranking.h"
#include "utils.h"
#include "estado.h"
#include "graficos.h"
#include "sons.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

void inicializarJogo(EstadoJogo *estado, int dificuldade) {
    // Inicializar bola
    iniciarBola(&estado->bola);
    
    // Inicializar barra
    iniciarBarra(&estado->barra);
    
    // Inicializar jogador
    strcpy(estado->jogador.nome, "Jogador");
    estado->jogador.pontuacao = 0;
    estado->jogador.tempo = 0;
    estado->jogador.vidas_jogador = VIDAS_INICIAIS;
    
    // Inicializar fase
    estado->fase_atual = 1;
    iniciarFase(&estado->fase, estado->fase_atual);
    
    // Inicializar itens
    estado->qtd_itens = 0;
    
    // Definir dificuldade
    estado->dificuldade = dificuldade;
}

void desenharHUD(EstadoJogo *estado) {
    char texto[100];
    
    // Desenhar pontuação
    sprintf(texto, "Pontuacao: %d", estado->jogador.pontuacao);
    DrawText(texto, 10, 10, 20, WHITE);
    
    // Desenhar tempo
    sprintf(texto, "Tempo: %ds", estado->jogador.tempo);
    DrawText(texto, 10, 40, 20, WHITE);
    
    // Desenhar vidas
    sprintf(texto, "Vidas: %d", estado->jogador.vidas_jogador);
    DrawText(texto, 10, 70, 20, WHITE);
    
    // Desenhar fase
    sprintf(texto, "Fase: %d", estado->fase_atual);
    DrawText(texto, LARGURA_TELA - 150, 10, 20, WHITE);
    
    // Desenhar dificuldade
    char dificuldade_str[20];
    if (estado->dificuldade == 1) {
        strcpy(dificuldade_str, "Facil");
    } else if (estado->dificuldade == 2) {
        strcpy(dificuldade_str, "Medio");
    } else {
        strcpy(dificuldade_str, "Dificil");
    }
    sprintf(texto, "Dificuldade: %s", dificuldade_str);
    DrawText(texto, LARGURA_TELA - 250, 40, 20, WHITE);
}

void desenharTelaGameOver(EstadoJogo *estado, bool vitoria) {
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Color{0, 0, 0, 200});
    
    if (vitoria) {
        DrawText("VOCE VENCEU!", LARGURA_TELA / 2 - 150, ALTURA_TELA / 2 - 100, 50, YELLOW);
    } else {
        DrawText("GAME OVER!", LARGURA_TELA / 2 - 150, ALTURA_TELA / 2 - 100, 50, RED);
    }
    
    char texto[100];
    sprintf(texto, "Pontuacao Final: %d", estado->jogador.pontuacao);
    DrawText(texto, LARGURA_TELA / 2 - 150, ALTURA_TELA / 2, 30, WHITE);
    
    sprintf(texto, "Tempo: %ds", estado->jogador.tempo);
    DrawText(texto, LARGURA_TELA / 2 - 150, ALTURA_TELA / 2 + 50, 30, WHITE);
    
    DrawText("Pressione ENTER para voltar ao menu", LARGURA_TELA / 2 - 200, ALTURA_TELA / 2 + 150, 20, LIGHTGRAY);
}

void desenharTelaDificuldade() {
    ClearBackground(obterCorFundo());
    
    DrawText("SELECIONE A DIFICULDADE", LARGURA_TELA / 2 - 200, 50, 40, obterCorTitulo());
    
    DrawText("1. Facil (velocidade normal)", LARGURA_TELA / 2 - 150, 200, 25, obterCorTexto());
    DrawText("2. Medio (velocidade +25%)", LARGURA_TELA / 2 - 150, 280, 25, obterCorTexto());
    DrawText("3. Dificil (velocidade +50%)", LARGURA_TELA / 2 - 150, 360, 25, obterCorTexto());
    
    DrawText("Pressione 1, 2 ou 3", LARGURA_TELA / 2 - 100, 500, 20, LIGHTGRAY);
}

int main() {
    srand((unsigned int)time(NULL));
    
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Arkanoid 2D");
    SetTargetFPS(60);

    EstadoJogo estado = {};
    Ranking ranking = {};
    
    int estado_atual = ESTADO_MENU;
    int dificuldade_selecionada = 1;
    float tempo_decorrido = 0.0f;
    int blocos_quebrados = 0;
    
    iniciarRanking(&ranking, (char *)ARQUIVO_RANKING);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        tempo_decorrido += dt;

        BeginDrawing();

        switch (estado_atual) {
            case ESTADO_MENU: {
                int opcao = menuIniciar();
                
                if (opcao == 0) {
                    estado_atual = ESTADO_DIFICULDADE;
                } else if (opcao == 1) {
                    estado_atual = ESTADO_DIFICULDADE;
                } else if (opcao == 2) {
                    estado_atual = ESTADO_RANKING;
                } else if (opcao == 3) {
                    estado_atual = ESTADO_SAIR;
                }
                break;
            }

            case ESTADO_DIFICULDADE: {
                desenharTelaDificuldade();
                
                if (IsKeyPressed(KEY_ONE)) {
                    dificuldade_selecionada = 1;
                    inicializarJogo(&estado, dificuldade_selecionada);
                    estado_atual = ESTADO_JOGANDO;
                    tempo_decorrido = 0.0f;
                    blocos_quebrados = 0;
                } else if (IsKeyPressed(KEY_TWO)) {
                    dificuldade_selecionada = 2;
                    inicializarJogo(&estado, dificuldade_selecionada);
                    estado_atual = ESTADO_JOGANDO;
                    tempo_decorrido = 0.0f;
                    blocos_quebrados = 0;
                } else if (IsKeyPressed(KEY_THREE)) {
                    dificuldade_selecionada = 3;
                    inicializarJogo(&estado, dificuldade_selecionada);
                    estado_atual = ESTADO_JOGANDO;
                    tempo_decorrido = 0.0f;
                    blocos_quebrados = 0;
                }
                break;
            }

            case ESTADO_JOGANDO: {
                ClearBackground(obterCorFundo());

                // Atualizar tempo
                estado.jogador.tempo = (int)tempo_decorrido;

                // Atualizar barra
                atualizarBarra(&estado.barra, dt);

                // Atualizar bola
                atualizarBola(&estado.bola, dt);

                // Verificar colisão bola com barra
                if (verificarColisaoCirculoRetangulo(estado.bola.posicao, estado.bola.radium, estado.barra.retangulo)) {
                    estado.bola.velocidadey *= -1;
                    estado.bola.posicao.y = estado.barra.retangulo.posicao.y - estado.bola.radium;
                    
                    // Adicionar pontos por rebater
                    atualizarPontuacao(&estado.jogador, 10);
                }

                // Verificar colisão bola com blocos
                int total_blocos = estado.fase.linha * estado.fase.coluna;
                for (int i = 0; i < total_blocos; i++) {
                    if (estado.fase.blocos[i].ativo) {
                        if (verificarColisaoCirculoRetangulo(estado.bola.posicao, estado.bola.radium, estado.fase.blocos[i].retangulo)) {
                            // Diminuir vida do bloco
                            estado.fase.blocos[i].TotalDeVida--;
                            
                            if (estado.fase.blocos[i].TotalDeVida <= 0) {
                                estado.fase.blocos[i].ativo = false;
                                blocos_quebrados++;
                                
                                // Calcular pontos
                                int pontos = 100;
                                if (estado.dificuldade == 2) {
                                    pontos = (int)(pontos * 1.25f);
                                } else if (estado.dificuldade == 3) {
                                    pontos = (int)(pontos * 1.5f);
                                }
                                atualizarPontuacao(&estado.jogador, pontos);
                                
                                // Gerar item aleatório
                                if (gerarAleatorio(1, 100) <= 30) { // 30% de chance
                                    int tipo_item = gerarAleatorio(1, 5);
                                    if (estado.qtd_itens < MAX_ITENS) {
                                        iniciarItem(&estado.itens[estado.qtd_itens], tipo_item, 
                                                   estado.fase.blocos[i].retangulo.posicao.x, 
                                                   estado.fase.blocos[i].retangulo.posicao.y);
                                        estado.qtd_itens++;
                                    }
                                }
                            }
                            
                            // Inverter velocidade da bola
                            estado.bola.velocidadey *= -1;
                            estado.bola.posicao.y = estado.fase.blocos[i].retangulo.posicao.y - estado.bola.radium;
                            break;
                        }
                    }
                }

                // Atualizar itens
                for (int i = 0; i < estado.qtd_itens; i++) {
                    if (estado.itens[i].esta_Ativo) {
                        atualizarItem(&estado.itens[i]);
                        
                        // Verificar colisão item com barra
                        Retangulo2D item_rect = {
                            {estado.itens[i].posicao_do_item.x - 5, estado.itens[i].posicao_do_item.y - 5},
                            10, 10
                        };
                        
                        if (verificarColisaoCirculoRetangulo(estado.itens[i].posicao_do_item, 5, estado.barra.retangulo)) {
                            efeitoItem(&estado.itens[i], &estado.jogador, &estado.barra);
                        }
                    }
                }

                // Verificar se bola saiu da tela (game over)
                if (estado.bola.posicao.y > ALTURA_TELA) {
                    atualizarVidas(&estado.jogador);
                    
                    if (estado.jogador.vidas_jogador <= 0) {
                        estado_atual = ESTADO_GAME_OVER;
                        atualizarRanking(&ranking, &estado.jogador);
                    } else {
                        // Reiniciar bola
                        iniciarBola(&estado.bola);
                    }
                }

                // Verificar se fase foi completada
                if (terminarFase(&estado.fase)) {
                    estado.fase_atual++;
                    
                    if (estado.fase_atual > 3) {
                        // Vitória!
                        estado_atual = ESTADO_GAME_OVER;
                        atualizarRanking(&ranking, &estado.jogador);
                    } else {
                        // Próxima fase
                        iniciarFase(&estado.fase, estado.fase_atual);
                        iniciarBola(&estado.bola);
                    }
                }

                // Desenhar tudo
                desenharFase(&estado.fase);
                desenharBarra(&estado.barra);
                desenharBola(&estado.bola);
                
                for (int i = 0; i < estado.qtd_itens; i++) {
                    desenharItem(&estado.itens[i]);
                }
                
                desenharHUD(&estado);
                break;
            }

            case ESTADO_GAME_OVER: {
                ClearBackground(obterCorFundo());
                desenharHUD(&estado);
                
                bool vitoria = (estado.fase_atual > 3);
                desenharTelaGameOver(&estado, vitoria);
                
                if (IsKeyPressed(KEY_ENTER)) {
                    estado_atual = ESTADO_MENU;
                }
                break;
            }

            case ESTADO_RANKING: {
                desenharRanking(&ranking);
                estado_atual = ESTADO_MENU;
                break;
            }

            case ESTADO_SAIR: {
                CloseWindow();
                return 0;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
