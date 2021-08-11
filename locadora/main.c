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

    // printf("fim\n");
    // printf("%s\n", filme->nome);
    // printf("%s\n", filme->genero);
    // printf("%d\n", (int)filme->ano);
    // printf("%.2f\n", filme->duracao);
    // printf("%s\n", filme->diretor);

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

void transfere(FILE *arquivo, Filme dados[255], int *tam, char nome[50]){

    printf("Transferencia de dados %d\n", *tam);

    char saux[255];
    int iaux = 0;
    int er;

    while(fgets(saux, 255, arquivo) != NULL){
        // printf("%s\n", saux);
        dados[iaux] = *linha_para_filme(saux);
        (*tam)++;
        iaux++;
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

char* pesquisa_opcoes (int *op) {
    char *string_pesquisa = malloc(sizeof(char) * 255);

    printf("(1) Nome. (2) Genero. (3) Ano \n");
    scanf("%d", op);

    if (*op == 1)
        printf("Digite o nome do filme: \n");
    else if (*op == 2)
        printf("Digite o genero do filme: \n");
    else if (*op == 3)
        printf("Digite o ano do filme: \n");
    else
        printf("Opcao invalida \n");

    scanf("%s", string_pesquisa);
    return string_pesquisa;
}

int* pesquisar (Filme filmes[], int tam, int op, const char string_pesquisa[255], int *num_encontrados) {
    printf("%s ======= \n", string_pesquisa);

    int counter = 0;
    int *vet_indices;

    /// verifica quantos filmes deram match
    for (int i = 0; i < tam; i++){
        /// opcao nome
        if (op == 1) {
            /// verifica se nome contem string_pesquisa
            if (strstr(filmes[i].nome, string_pesquisa) != NULL){
                counter++;
            }
        }
        /// opcao genero
        else if (op == 2){
            /// verifica se genero contem string_pesquisa
            if (strstr(filmes[i].genero, string_pesquisa) != NULL){
                counter++;
            }
        }
        /// opcao ano
        else if (op == 3){
            /// verifica se ano filme igual ano pesquisa
            if (filmes[i].ano == (unsigned short) atoi(string_pesquisa)){
                counter++;
            }
        }
    }

    if (counter <= 0)
        return NULL;

    /// aloca vetor de indice dos encontrados
    vet_indices = malloc(sizeof(int) * counter);
    counter = 0;

    /// armazena os indices dos filmes que deram match
    for (int i = 0; i < tam; i++){
        /// opcao nome
        if (op == 1) {
            /// verifica se nome contem string_pesquisa
            if (strstr(filmes[i].nome, string_pesquisa) != NULL){
                vet_indices[counter] = i; // armazena indice do match
                counter++;
            }
        }
        /// opcao genero
        else if (op == 2){
            /// verifica se genero contem string_pesquisa
            if (strstr(filmes[i].genero, string_pesquisa) != NULL){
                vet_indices[counter] = i; // armazena indice do match
                counter++;
            }
        }
        /// opcao ano
        else if (op == 3){
            /// verifica se ano filme igual ano pesquisa
            if (filmes[i].ano == (unsigned short) atoi(string_pesquisa)){
                vet_indices[counter] = i; // armazena indice do match
                counter++;
            }
        }
    }
    *num_encontrados = counter;
    return vet_indices;
}


int main()
{

    FILE *arquivo;
    FILE *aux_arquivo;

    arquivo = init_arquivo("dados.txt");
    aux_arquivo = init_arquivo("auxiliar.txt");

    int op = 1;
    Filme filmes[255];

    //menu();

    int tam = 0;
    // transfere(arquivo, aux_arquivo, "dados.txt");
    transfere(arquivo, filmes, &tam, "dados.txt");

    // printf("Nome do filme: %s\n", filmes[0].nome);
    // print_vector(filmes, tam);
    // print_arq(arquivo);
    // print_arq(aux_arquivo);

    printf("Opcao: ");
    //scanf("%d", &op);

    switch(op){
        case 0:
            printf("Cadastrar\n");
            cadastrar(aux_arquivo);
            break;
        case 1:
            printf("Pesquisar\n");
            int op_pesquisa;
            char *string_pesquisa;
            int num_encontrados; // quantidade de filmes encontrados
            int *vet_indices; // vetor de indices dos filmes encontrados

            /// mostra as opções de pesquisa e retorna a string a
            /// ser pesquisada e a opção selecionada
            string_pesquisa = pesquisa_opcoes(&op_pesquisa);

            /// pesquisa no vetor de filmes os filmes que
            /// contem a string pesquisada
            /// retorna um vetor de indices dos filmes que
            /// deram match
            vet_indices = pesquisar(filmes, tam, op_pesquisa, string_pesquisa, &num_encontrados);

            printf("num_encontrados %d \n", num_encontrados);
            break;
    }

    // menu();

    printf("Fim do programa!!\n");
    getch();
    return 0;
}
