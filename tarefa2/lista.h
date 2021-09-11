#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Econtato
{

    char nome[20];
    char email[30];
    char telefone[15];

} Contato;

typedef struct LElemento
{
    Contato contato;
    //Aponta pro proximo elemento da lista
    struct LElemento *proximo;

} Elemento;

typedef struct listaE
{
    Elemento *inicio;
    int cont;

} Lista_e;

Lista_e* criaLista();
Elemento *novoElemento(char nome[], char email[], char telefone[]);
void insereContato(Lista_e *lista, char nome[], char email[], char telefone[]);
void removeContatoIndex (Lista_e *lista, int index);
void removeContatoNome (Lista_e *lista, char *nome);
void apagaLista(Lista_e *lista);
void mostraContatos(Lista_e lista);
Elemento* consultaContatoNome(Lista_e lista, char *nome);
Elemento* consultaContatoIndex(Lista_e lista, int index);
int quantidadeContatos (Lista_e lista);




#endif // LISTA_H_INCLUDED
