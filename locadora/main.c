#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"


void cadastrar(FILE *arquivo){

    char filme[255] ;

    printf("Digite um filme: ");
    scanf("%s", &filme);

    printf("%s\n", filme);
    escrita(filme, arquivo);

    return;
}

void escrita(char filme[255], FILE *arquivo){

        int er;
        er = fputs(filme, arquivo);

        if(er == EOF){
            printf("Erro ao escrever uma linha do arquivo.");
        }else{

            printf("Filme registrado com sucesso!!");
        }

}

void leitura(FILE *arquivo){

    printf("Conteudo do arquivo: \n");
    char saux[255];
    while(fgets(saux, 255, arquivo) != NULL){
        printf("%s\n", saux);
    }
}

/*
void transfere(FILE *arquivo, FILE *aux_arquivo, char nome[50]){

    printf("Transferencia de dados\n");

    char saux[255];
    int iaux = 0;
    int er;

    while(fgets(saux, 255, arquivo) != NULL){
        printf("%s\n", saux);
        er = fputs(saux, aux_arquivo);

        if(er == EOF){
            printf("Erro ao passar uma linha do arquivo. Linha: %d", iaux);
        }

        iaux++;
    }
    printf("Terminou de ler o arquivo. O arquivo contem %d linhas\n", iaux);
    fclose(arquivo);
    remove(nome);

    return;
}
*/
void transfere(FILE *arquivo, char dados[][255], char nome[50]){

    printf("Transferencia de dados\n");

    char saux[255];
    int iaux = 0;
    int er;

    while(fgets(saux, 255, arquivo) != NULL){
        printf("%s\n", saux);
        dados[iaux][255] = saux;

        iaux++;
    }
    printf("Terminou de ler o arquivo. O arquivo contem %d linhas\n", iaux);
    //fclose(arquivo);
    //remove(nome);

    return;
}

FILE *init_arquivo(char nome[50]){

    FILE *arquivo;

    arquivo = fopen(nome, "r+");

    if(arquivo == NULL){
        printf("Nao ha um arquivo %s para salvar. Criando novo arquivo.\n", nome);
        arquivo = fopen(nome, "w+");
        if(arquivo == NULL){
            printf("Nao foi possivel criar o arquivo. Encerrando programa!!!\n");
            return NULL;
        }

    }

    return arquivo;

}


int main()
{
    FILE *arquivo;
    FILE *aux_arquivo;

    arquivo = init_arquivo("dados.txt");
    aux_arquivo = init_arquivo("auxiliar.txt");

    int op = 0;
    char dados[255][255]; //Cria a variavel que vai guardar as informações durante a execução do código. Armazena até 255 strings de 255 caracteres.

    //menu();

    int tam = 0;
    //transfere(arquivo, aux_arquivo, "dados.txt");
    transfere(arquivo, dados, "dados.txt");

    leitura(arquivo);
    leitura(aux_arquivo);

    printf("tam: %d\n", tam);

    printf("Opcao: ");
    //scanf("%d", &op);

    switch(op){

    case 0:
        printf("Cadastrar\n");
        cadastrar(aux_arquivo);

        break;
    case 1:
        printf("Opcao 2\n");
        break;
    }


    printf("Fim do programa!!\n");
    return 0;
}
