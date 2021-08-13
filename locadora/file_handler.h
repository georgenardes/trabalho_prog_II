#ifndef FILE_HANDLER_H_INCLUDED
#define FILE_HANDLER_H_INCLUDED

#include "data_types.h"

///Função que recebe uma linha do arquivo de texto e transforma em uma variável do tipo Filme para armazenar as informações do filme
///Recebe uma string que contem uma linha que estava no arquivo
Filme linha_para_filme (char *linha);

///Função que recebe uma linha do arquivo de texto e transforma em uma variável do tipo Filme para armazenar as informações do filme
///Recebe uma string que contem uma linha que estava no arquivo
Admin linha_para_adm(char *linha);

///Função que recebe o array de obejtos do tipo Filme e escreve cada filme no arquivo de texto
///Recebe um ponteiro do tipo FILE, o array de Filmes e o tamanho do array
void objeto_para_arquivo(FILE *arquivo, Filme filmes[], int tam);

///Função que Recebe uma string que contem as informações do filme e que será escrita em um arquivo
///Recebe uma string com as informações e um ponteiro do tipo FILE
void escrita(char filme[255], FILE *arquivo);

///Função que copia os dados de um arquivo txt e passa para o array de Filmes para serem manipulados durante a execução do programa
///Recebe um ponteiro do tipo FILE, o array do tipo Filme, o tamanho do array e o nome do arquivo que irá ser aberto
void transfere_filme(FILE *arquivo, Filme dados[], int *tam, char nome[50]);

///Função que copia os dados de um arquivo txt e passa para o array de Admin para serem manipulados durante a execução do programa
///Recebe um ponteiro do tipo FILE, o array do tipo Admin, o tamanho do array e o nome do arquivo que irá ser aberto
void transfere_adm(FILE *arquivo, Admin adms[], int *tam, char nome[50]);

///Função que abre o arquivo para leitura e escrita, se o arquivo não existir, ela irá criar
///Recebe uma string com o nome do arquivo
FILE *init_arquivo(char nome[50]);

#endif // FILE_HANDLER_H_INCLUDED
