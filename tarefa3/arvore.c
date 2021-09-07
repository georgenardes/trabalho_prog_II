#include "arvore.h"


void inicia (Arvere_t *arv){
    arv->raiz = NULL;
}

void insere(Tno_t **no, TIPO dado, int chave){
     if ((*no) == NULL){
         (*no) = (Tno_t*) malloc(sizeof(Tno_t));
         (*no)->chave = chave;
         (*no)->dado = dado;
         (*no)->direita = NULL;
         (*no)->esquerda = NULL;
     } else {
         if (dado < (*no)->dado){
             insere(&((*no)->esquerda), dado, chave);
         }
         else if (dado > (*no)->dado ){
             insere(&((*no)->direita), dado, chave);
         }
     }
}

void printa_preordem (Tno_t **no){
    if((*no) != NULL){
        printf("%d -> %d \n", (*no)->chave,(*no)->dado);
        printa_preordem(&((*no)->esquerda));
        printa_preordem(&((*no)->direita));
    }
}

void printa_ordem (Tno_t **no){
    if((*no) != NULL){
        printa_ordem(&((*no)->esquerda));
        printf("%d -> %d \n", (*no)->chave,(*no)->dado);
        printa_ordem(&((*no)->direita));
    }
}

void printa_posordem (Tno_t **no){
    if((*no) != NULL){
        printa_posordem(&((*no)->esquerda));
        printa_posordem(&((*no)->direita));
        printf("%d -> %d \n", (*no)->chave,(*no)->dado);
    }
}

void remover(Tno_t **no){
    Tno_t *apagar;
    Tno_t *maior = (*no)->esquerda;

    if(maior == NULL)
    {
        apagar = (*no);
        (*no) = (*no)->direita;
        free(apagar);
        return;
    }
    Tno_t *pai = NULL;
    while(maior->direita != NULL){
        pai = maior;
        maior = maior->direita;
    }

    maior->direita = (*no)->direita;

    if(pai != NULL) {     // Pai inicialmente é NULL
        pai->direita = maior->esquerda;
        maior->esquerda = (*no)->esquerda;
    }
    apagar = (*no);
    (*no) = maior;
    free(apagar);
}

void procura_remove(Tno_t **no, int chave){
    if((*no) != NULL){
        if((*no)->chave == chave)
            remover(no);
        else if((*no)->chave > chave)
            procura_remove(&((*no)->esquerda), chave);
        else
            procura_remove(&((*no)->direita), chave);
    }
}

void libera_arvore(Arvere_t *arv){
    Tno_t ** raiz = &(arv->raiz);

    while((*raiz) != NULL){
        printf("apagando %d\n", (*raiz)->dado);
        procura_remove(raiz, (*raiz)->chave);
    }

}

