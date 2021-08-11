#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"

typedef struct {
    char nome[80];
    char genero[25];
    unsigned short ano; // 16 bits
    float duracao;
    char diretor[100];
} Filme;

void print_vector(Filme vetor[], int tam);
void print_arq(FILE *arquivo);
void escrita(char filme[255], FILE *arquivo);
void cadastrar(FILE *arquivo);
Filme* linha_para_filme (char *linha);
void transfere(FILE *arquivo, Filme dados[], int *tam, char nome[50]);
FILE *init_arquivo(char nome[50]);


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
        char sdur[5];
        sprintf(sdur, "%s", ch);
        filme->duracao = atof(sdur);
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
    printf("%.2f\n", filme->duracao);
    printf("%s\n", filme->diretor);

    return filme;
}

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

void print_arq(FILE *arquivo){

    printf("Conteudo do arquivo: \n");
    char saux[255];
    while(fgets(saux, 255, arquivo) != NULL){
        printf("%s\n", saux);
    }
}

void print_vector(Filme vetor[], int tam){

    printf("Filmes\n");
    for(int i = 0; i<tam; i++){
        printf("Info do filme %s\n", vetor[i].nome);
        printf("%s\n", vetor[i].genero);
        printf("%d\n", (int)vetor[i].ano);
        printf("%f\n", vetor[i].duracao);
        printf("%s\n", vetor[i].diretor);
        printf("\n");
    }

    return;
}

void transfere(FILE *arquivo, Filme dados[], int *tam, char nome[50]){

    printf("Transferencia de dados %d\n", *tam);

    char saux[255];
    int iaux = 0;
    int er;

    while(fgets(saux, 255, arquivo) != NULL){
        printf("%s\n", saux);
        dados[iaux] = *linha_para_filme(saux);
        (*tam)++;
    }
    printf("Terminou de ler o arquivo. O arquivo contem %d linhas\n", *tam);
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
    Filme dados[255];

    //menu();

    int tam = 0;
    //transfere(arquivo, aux_arquivo, "dados.txt");
    transfere(arquivo, dados, &tam, "dados.txt");

    printf("Nome do filme: %s\n", dados[0].nome);

    //print_vector(dados, tam);
    //print_arq(arquivo);
    //print_arq(aux_arquivo);

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



    char linha[] = "Nome;Genero;2000;2;Nolan";
    Filme *filme = linha_para_filme(linha);
    printf("linha %s\n", linha);

    // menu();

    printf("Fim do programa!!\n");
    getch();
    return 0;
}
