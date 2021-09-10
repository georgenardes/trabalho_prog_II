#include "arvore.h"

/**
    Atribui Null ao elemento raiz da arvore
*/
void inicia (Arvere_t *arv){
    arv->raiz = NULL;
}

/**
    Função recebe o nó raiz, o dado e a chave.

    Caso o nó seja nulo, é criado um novo dado com alocação
    de memória.

    Se o nó não for nulo, é verificado se o dado a ser
    inserido é menor ou maior, chamando a função insere
    recursivamente com o novo nó raiz.
*/
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

/**

    Printa preordem com a seguinte lógica recursiva:
        Printa elemento
        visita todos da esquerda.
        visita todos da direita.
*/
void printa_preordem (Tno_t **no){
    if((*no) != NULL){
        printf("%d -> %d \n", (*no)->chave,(*no)->dado);
        printa_preordem(&((*no)->esquerda));
        printa_preordem(&((*no)->direita));
    }
}

/**
    Printa ordem com a seguinte lógica recursiva
        visita todos da esquerda.
        Printa elemento
        visita todos da direita.
*/
void printa_ordem (Tno_t **no){
    if((*no) != NULL){
        printa_ordem(&((*no)->esquerda));
        printf("%d -> %d \n", (*no)->chave,(*no)->dado);
        printa_ordem(&((*no)->direita));
    }
}

/**
    Printa pos-ordem com a seguinte lógica recursiva
        visita todos da esquerda.
        visita todos da direita.
        Printa elemento
*/
void printa_posordem (Tno_t **no){
    if((*no) != NULL){
        printa_posordem(&((*no)->esquerda));
        printa_posordem(&((*no)->direita));
        printf("%d -> %d \n", (*no)->chave,(*no)->dado);
    }
}

/**
    Remove nó

    Seleciona o maior nó à esquerda ou o primeiro nó à direita
    para substituir o nó a ser removido
*/
void remover(Tno_t **no){
    Tno_t *apagar;
    Tno_t *maior = (*no)->esquerda;

    if(maior == NULL){
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

/**
    Procura valor a ser removido
*/
void procura_remove(Tno_t **no, TIPO dado){
    if((*no) != NULL){
        if((*no)->dado == dado)
            remover(no);
        else if((*no)->dado > dado)
            procura_remove(&((*no)->esquerda), dado);
        else
            procura_remove(&((*no)->direita), dado);
    }
}

/**
    Libera memória alocada
*/
void libera_arvore(Arvere_t *arv){
    Tno_t ** raiz = &(arv->raiz);

    while((*raiz) != NULL){
        printf("%d\n", (*raiz)->dado);
        procura_remove(raiz, (*raiz)->dado);
    }
    free(raiz);
    free(arv);
}

