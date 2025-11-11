#include <iostream>

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

struct Posicao {
    int x;
    int y;
};

struct Retangulo2D {
    Posicao posicao;
    int largura;
    int altura;
};

struct Bloco {
    Retangulo2D retangulo;
    bool ativo;
    int TotalDeVida;
};

struct Bola {
    Posicao posicao;
    int radium;
    int velocidadex;
    int velocidadey;
    bool prendeu;
};

struct Jogador {
    Retangulo2D retangulo;
    int tamanho;
};

#endif
