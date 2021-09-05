#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct Contato{

    char nome[30];
    char email[50];
    char telefone[15];

};

struct Elemento
{
    struct Contato contato;
    //Aponta pro proximo elemento da lista
    struct Elemento *proximo;

};

struct lista_e
{
    struct Elemento *inicio;
    int cont;

};


struct Elemento *novoElemento (struct Contato contato);
void insereContato(struct lista_e *lista, struct Contato elemento);
void removeContato(struct lista_e *lista, int index);
void mostraContatos(struct lista_e lista);
int quantidadeContatos (struct lista_e lista);
struct lista_e criaLista ();

#endif // LISTA_H_INCLUDED
