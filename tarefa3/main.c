#include <stdio.h>
#include "arvore.h"
#include <windows.h>
#include <conio.h>

int main()
{
    TIPO vet[8] = {33, 15, 41, 38, 34, 47, 43, 49};
    Arvere_t *arv = (Arvere_t *) malloc (sizeof(Arvere_t));
    inicia(arv);

    Tno_t ** raiz = &(arv->raiz);
    for (int i = 0; i < 8; i++){
        insere(raiz, vet[i], i);
    }

    int input_char = 0;
    do {
        system("cls");

        printf("Digite o numero da opcao desejada ou ESC para encerrar o programa.\n\n");
        printf("(1) Visita em pre-ordem\n");
        printf("(2) Visita em ordem\n");
        printf("(3) Vista em pos-ordem\n");

        do {
            input_char = _getch();
        } while (input_char != 49 && input_char != 50 && input_char != 51 && input_char != 27);

        system("cls");

        if (input_char == 49){
            printf("Selecionado opcao de vista em pre-ordem\n\n");
            printa_preordem(raiz);
            printf("\n---\n");
            _getch();
        } else if (input_char == 50){
            printf("Selecionado opcao de vista em ordem\n\n");
            printa_ordem(raiz);
            printf("\n---\n");
            _getch();
        } else if (input_char == 51) {
            printf("Selecionado opcao de vista em pos-ordem\n\n");
            printa_posordem(raiz);
            printf("\n---\n");
            _getch();
        } else if (input_char == 27) {
            break;
        }

    } while (1);

    printf("Liberando memoria...\n");

    // libera memória
    libera_arvore(arv);
    return 0;
}

