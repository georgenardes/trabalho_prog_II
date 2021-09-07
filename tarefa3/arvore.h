#ifndef ARVERES_H
#define ARVERES_H

#include <stdio.h>
#include <stdlib.h>

typedef int TIPO;

struct Tno{
    int chave;
    TIPO dado;
    struct Tno *esquerda;
    struct Tno *direita;
};
typedef struct Tno Tno_t;

struct Arvere{
    struct Tno *raiz;
};
typedef struct Arvere Arvere_t;

void inicia (Arvere_t *arv);
void insere(Tno_t **no, TIPO dado, int chave);
void printa_preordem (Tno_t **no);
void printa_ordem (Tno_t **no);
void printa_posordem (Tno_t **no);
void remover(Tno_t **no);
void procura_remove(Tno_t **no, int chave);
void libera_arvore(Arvere_t *arv);

#endif // ARVERES_H
