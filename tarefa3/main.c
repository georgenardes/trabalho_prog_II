#include <stdio.h>
#include "arvore.h"

int main()
{
    TIPO vet[8] = {33, 15, 41, 38, 34, 47, 43, 49};
    Arvere_t *arv = (Arvere_t *) malloc (sizeof(Arvere_t));

    inicia(arv);
    Tno_t ** raiz = &(arv->raiz);

    for (int i = 0; i < 8; i++){
        insere(raiz, vet[i], i);
    }
    printf("printa_preordem\n");
    printa_preordem(raiz);
    printf("\n---\n");
    printf("printa_ordem\n");
    printa_ordem(raiz);
    printf("\n---\n");
    printf("printa_posordem\n");
    printa_posordem(raiz);
    printf("\n---\n");

    libera_arvore(arv);

    return 0;
}

