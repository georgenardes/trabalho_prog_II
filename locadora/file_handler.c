#include "file_handler.h"


///Função que recebe uma linha do arquivo de texto e transforma em uma variável do tipo Filme para armazenar as informações do filme
///Recebe uma string que contem uma linha que estava no arquivo
Filme linha_para_filme (char *linha) {

    // Aloca memória para a variável filme
    Filme filme;

    char *st = linha;

    //Caractere que separa as informações
    const char delimiter[] = ";";


    // primeira coluna
    char *ch;
    ch = strtok(st, delimiter);
    sprintf(filme.nome, "%s", ch);

    // segunda coluna
    if (ch != NULL) {
        ch = strtok(NULL, delimiter);
        sprintf(filme.genero, "%s", ch);
    }

    // terceira coluna
    if (ch != NULL) {
        ch = strtok(NULL, delimiter);
        char sano[5];
        sprintf(sano, "%s", ch);
        filme.ano = (unsigned short) atoi(sano);
    }

    // quarta coluna
    if (ch != NULL) {
        ch = strtok(NULL, delimiter);
        char sdur[5];
        sprintf(sdur, "%s", ch);
        filme.duracao = atof(sdur);
    }

    // quinta coluna
    if (ch != NULL) {
        ch = strtok(NULL, delimiter);
        sprintf(filme.diretor, "%s", ch);
    }

    // printf("fim\n");
    // printf("%s\n", filme->nome);
    // printf("%s\n", filme->genero);
    // printf("%d\n", (int)filme->ano);
    // printf("%.2f\n", filme->duracao);
    // printf("%s\n", filme->diretor);


    return filme;
}

///Função que recebe uma linha do arquivo de texto e transforma em uma variável do tipo Filme para armazenar as informações do filme
///Recebe uma string que contem uma linha que estava no arquivo
Admin linha_para_adm(char *linha){

    Admin adm;

    char *st = linha;

    //Caractere que separa as informações
    const char delimiter[] = ";";

    // primeira coluna
    char *ch;
    ch = strtok(st, delimiter);
    sprintf(adm.usuario, "%s", ch);

    // segunda coluna
    if (ch != NULL) {
        ch = strtok(NULL, delimiter);
        sprintf(adm.senha, "%s", ch);
    }

    return adm;
}

///Função que recebe o array de obejtos do tipo Filme e escreve cada filme no arquivo de texto
///Recebe um ponteiro do tipo FILE, o array de Filmes e o tamanho do array
void objeto_para_arquivo(FILE *arquivo, Filme filmes[], int tam){

    //Abre o arquivo ou cria se necessário
    arquivo = init_arquivo("dados.txt");

    for(int i=0; i<tam; i++){
        char aux[255];
        //Para cada filme no array de filmes, cria uma string que contem as informações do filme
        // sprintf(aux, "%s;%s;%d;%.2f;%s", filmes[i].nome, filmes[i].genero, (int)filmes[i].ano, filmes[i].duracao, filmes[i].diretor);
        fprintf(arquivo, "%s;%s;%d;%.2f;%s", filmes[i].nome, filmes[i].genero, (int)filmes[i].ano, filmes[i].duracao, filmes[i].diretor);

        // Escreve a string no arquivo
        // escrita(aux, arquivo);
    }
    //Fecha o arquivo
    fclose(arquivo);
}

///Função que Recebe uma string que contem as informações do filme e que será escrita em um arquivo
///Recebe uma string com as informações e um ponteiro do tipo FILE
void escrita(char filme[255], FILE *arquivo){

    int er;
    //Escreve a string no arquivo

    er = fputs(filme, arquivo);

    if(er == EOF){
        printf("Erro ao escrever uma linha do arquivo.");
    }else{
        //printf("Filme registrado com sucesso!!\n");
    }
}

///Função que copia os dados de um arquivo txt e passa para o array de Filmes para serem manipulados durante a execução do programa
///Recebe um ponteiro do tipo FILE, o array do tipo Filme, o tamanho do array e o nome do arquivo que irá ser aberto
void transfere_filme(FILE *arquivo, Filme dados[], int *tam, char nome[50]){


    //printf("Transferencia de dados %d\n", *tam);

    //Abre ou criar o arquivo
    arquivo = init_arquivo("dados.txt");

    char saux[255];
    int iaux = 0;
    int er;
    //Enquanto não chegar ao fim do arquivo continua lendo linha por linha
    while(fgets(saux, 255, arquivo) != NULL){
        //printf("%d %s\n", *tam, saux);
        //Converte a linha para uma variavel e insere no array
        dados[*tam] = linha_para_filme(saux);
        (*tam)++;
        iaux++;
    }
    //printf("Terminou de ler o arquivo. O arquivo contem %d linhas\n", *tam);
    //Fecha o arquivo
    fclose(arquivo);
    //Exclui o arquivo
    remove(nome);

    return;
}

///Função que copia os dados de um arquivo txt e passa para o array de Admin para serem manipulados durante a execução do programa
///Recebe um ponteiro do tipo FILE, o array do tipo Admin, o tamanho do array e o nome do arquivo que irá ser aberto
void transfere_adm(FILE *arquivo, Admin adms[], int *tam, char nome[50]){
    //Abre ou criar o arquivo
    arquivo = init_arquivo(nome);

    char saux[255];
    int iaux = 0;
    int er;
    //Enquanto não chegar ao fim do arquivo continua lendo linha por linha
    while(fgets(saux, 255, arquivo) != NULL){
        //printf("%d %s\n", *tam, saux);
        //Converte a linha para uma variavel e insere no array
        adms[*tam] = linha_para_adm(saux);
        (*tam)++;
        iaux++;
    }
    //printf("Terminou de ler o arquivo. O arquivo contem %d linhas\n", *tam);
    //Fecha o arquivo
    fclose(arquivo);

    return;
}

///Função que abre o arquivo para leitura e escrita, se o arquivo não existir, ela irá criar
///Recebe uma string com o nome do arquivo
FILE *init_arquivo(char nome[50]){


    FILE *arquivo;
    //Abre um arquivo txt
    arquivo = fopen(nome, "r+");

    if(arquivo == NULL){
        //printf("Nao ha um arquivo %s para salvar. Criando novo arquivo.\n", nome);
        //Cria um arquivo txt se não houver
        arquivo = fopen(nome, "w+");
        if(arquivo == NULL){
            printf("Nao foi possivel criar o arquivo. Encerrando programa!!!\n");
            return NULL;
        }
    }
    return arquivo;
}

