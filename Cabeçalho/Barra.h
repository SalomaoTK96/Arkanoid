#include <iostream>

#include "Estruturas.h"

#ifndef BARRA
#define BARRA

void iniciarBarra(Barra *barra);

void atualizarBarra(Barra *barra, int dt);

void atualizarTamanho(Barra *barra, int tamanhoAd, bool adicionar);

void desenharBarra(Barra *barra);

#endif
