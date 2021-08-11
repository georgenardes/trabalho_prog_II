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
void cadastrar(Filme filmes[], int *tam);
void deletar(Filme filmes[], int pos, int *tam);
Filme* linha_para_filme (char *linha);
void transfere(FILE *arquivo, Filme dados[], int *tam, char nome[50]);
FILE *init_arquivo(char nome[50]);
void objeto_para_arquivo(FILE *arquivo, Filme filmes[], int tam);

//Função que recebe uma linha do arquivo de texto e transforma em uma variável do tipo Filme para armazenar as informações do filme
//Recebe uma string que contem uma linha que estava no arquivo
Filme* linha_para_filme (char *linha) {


    // Aloca memória para a variável filme
    Filme *filme = malloc(sizeof(Filme));

    char *st = linha;

    //Caractere que separa as informações
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
    /*
    printf("fim\n");
    printf("%s\n", filme->nome);
    printf("%s\n", filme->genero);
    printf("%d\n", (int)filme->ano);
    printf("%.2f\n", filme->duracao);
    printf("%s\n", filme->diretor);*/

    return filme;
}
//Função que recebe o array de obejtos do tipo Filme e escreve cada filme no arquivo de texto
//Recebe um ponteiro do tipo FILE, o array de Filmes e o tamanho do array
void objeto_para_arquivo(FILE *arquivo, Filme filmes[], int tam){

    //Abre o arquivo ou cria se necessário
    arquivo = init_arquivo("dados.txt");

    for(int i=0; i<tam; i++){
        char aux[255];
        //Para cada filme no array de filmes, cria uma string que contem as informações do filme
        sprintf(aux, "%s;%s;%d;%.2f;%s", filmes[i].nome, filmes[i].genero, (int)filmes[i].ano, filmes[i].duracao, filmes[i].diretor);
        //Escreve a string no arquivo
        escrita(aux, arquivo);
    }
    //Fecha o arquivo
    fclose(arquivo);
}

//Função que insere um filme no array de filmes
//Recebe o array de filmes e o tamanho do array
void cadastrar(Filme filmes[], int *tam){

    char aux[255];
    if(*tam<255){


        Filme *filme = malloc(sizeof(Filme));
        printf("Digite o nome do filme: ");
        scanf("%s", &filme->nome);
        printf("Digite o genero do filme: ");
        scanf("%s", &filme->genero);
        printf("Digite o ano do filme: ");
        scanf("%hu", &filme->ano);
        printf("Digite a duracao do filme: ");
        scanf("%f", &filme->duracao);
        printf("Digite o diretor do filme: ");
        scanf("%s", &aux);
        sprintf(filme->diretor, "%s\n", aux);

        filmes[*tam] = *filme;
        (*tam)++;

        printf("%d de %d filmes cadastrados\n", *tam, 255);

    }else{
        printf("Limite de filmes cadastrados atingido: %d de %d filmes cadastrados\n", *tam, 255);
    }

    return;
}
//Função que remove do array de filmes
//Recebe o array de Filmes, a posição que deseja ser deletada e tamanho do array
void deletar(Filme filmes[], int pos, int *tam){

    //Se por acaso receber uma posição maior que o tamanho total de filmes
    if(!pos>(*tam)+1){
        printf("Posicao maior que o tamanho do vetor");
        return;
    }
    //Desloca todos os elemento apos a posição "para a esquerda" do array
    for(int i = pos - 1; i < (*tam) - 1; i++){
        filmes[i] = filmes[i+1];
    }

    (*tam)--;

    return;

}
//Função que Recebe uma string que contem as informações do filme e que será escrita em um arquivo
//Recebe uma string com as informações e um ponteiro do tipo FILE
void escrita(char filme[255], FILE *arquivo){

        int er;
        //Escreve a string no arquivo
        er = fputs(filme, arquivo);

        if(er == EOF){
            printf("Erro ao escrever uma linha do arquivo.");
        }else{
            printf("Filme registrado com sucesso!!\n");
        }

}
//Auxiliar
void print_arq(FILE *arquivo){


    printf("Conteudo do arquivo: \n");
    char saux[255];
    while(fgets(saux, 255, arquivo) != NULL){
        printf("%s\n", saux);
    }
}
//Auxiliar
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
//Função que copia os dados de um arquivo txt e passa para o array de Filmes para serem manipulados durante a execução do programa
//Recebe um ponteiro do tipo FILE, o array do tipo Filme, o tamanho do array e o nome do arquivo que irá ser aberto
void transfere(FILE *arquivo, Filme dados[], int *tam, char nome[50]){


    printf("Transferencia de dados %d\n", *tam);

    //Abre ou criar o arquivo
    arquivo = init_arquivo("dados.txt");

    char saux[255];
    int iaux = 0;
    int er;
    //Enquanto não chegar ao fim do arquivo continua lendo linha por linha
    while(fgets(saux, 255, arquivo) != NULL){
        printf("%d %s\n", *tam, saux);
        //Converte a linha para uma variavel e insere no array
        dados[*tam] = *linha_para_filme(saux);
        (*tam)++;
    }
    printf("Terminou de ler o arquivo. O arquivo contem %d linhas\n", *tam);
    //Fecha o arquivo
    fclose(arquivo);
    //Exclui o arquivo
    remove(nome);

    return;
}
//Função que abre o arquivo para leitura e escrita, se o arquivo não existir, ela irá criar
//Recebe uma string com o nome do arquivo
FILE *init_arquivo(char nome[50]){

    FILE *arquivo;
    //Abre um arquivo txt
    arquivo = fopen(nome, "r+");

    if(arquivo == NULL){
        printf("Nao ha um arquivo %s para salvar. Criando novo arquivo.\n", nome);
        //Cria um arquivo txt se não houver
        arquivo = fopen(nome, "w+");
        if(arquivo == NULL){
            printf("Nao foi possivel criar o arquivo. Encerrando programa!!!\n");
            return NULL;
        }
    }
    return arquivo;
}

void busca(int op){



}

int main()
{
    //Variável que irá receber o arquivo
    FILE *arquivo;

    int op = 0;
    //Array do tipo Filme que irá armazenar os filmes durante a execução do código
    Filme dados[255];
    //Tamanho do array dados
    int tam = 0;


    transfere(arquivo, dados, &tam, "dados.txt");
    //cadastrar(dados, &tam);
    deletar(dados, 3, &tam);

    print_vector(dados, tam);

    objeto_para_arquivo(arquivo, dados, tam);
    //print_arq(arquivo);
    //print_arq(aux_arquivo);

    printf("Opcao: ");
    //scanf("%d", &op);

    switch(op){

    case 0:
        printf("Cadastrar\n");
        //cadastrar(aux_arquivo);

        break;
    case 1:
        printf("Opcao 2\n");
        break;
    }

    printf("Fim do programa!!\n");
    getch();
    return 0;
}
