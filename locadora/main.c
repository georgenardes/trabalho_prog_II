#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


typedef struct {
    char nome[80];
    char genero[25];
    unsigned short ano; // 16 bits
    char duracao;       // 8 bits
    char diretor[100];
} Filme;


Filme* linha_para_filme (char *linha) {
    Filme *filme = malloc(sizeof(Filme));

    char *st = linha;
    const char delimiter[] = ";";

    // primeira coluna
    char *ch;
    ch = strtok(st, delimiter);
    sprintf(filme->nome, "%s", ch);

    // segunda coluna
    if (ch != NULL) {
        ch = strtok(NULL, delimiter);
        sprintf(filme->genero, "%s", ch);
    }

    // terceira coluna
    if (ch != NULL) {
        ch = strtok(NULL, delimiter);
        char sano[5];
        sprintf(sano, "%s", ch);
        filme->ano = (unsigned short) atoi(sano);
    }

    // quarta coluna
    if (ch != NULL) {
        ch = strtok(NULL, delimiter);
        char sdur[2];
        sprintf(sdur, "%s", ch);
        filme->duracao = (char) atoi(sdur);
    }

    // quinta coluna
    if (ch != NULL) {
        ch = strtok(NULL, delimiter);
        sprintf(filme->diretor, "%s", ch);
    }

    printf("fim\n");
    printf("%s\n", filme->nome);
    printf("%s\n", filme->genero);
    printf("%d\n", (int)filme->ano);
    printf("%d\n", (int)filme->duracao);
    printf("%s\n", filme->diretor);

    return filme;
}


int main()
{
    char linha[] = "Nome;Genero;2000;2;Nolan";
    Filme *filme = linha_para_filme(linha);
    printf("linha %s\n", linha);

    // menu();


    getch();
    return 0;
}
