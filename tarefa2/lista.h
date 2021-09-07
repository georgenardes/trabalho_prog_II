#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Econtato
{

    char *nome;
    char *email;
    char *telefone;

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
Elemento *novoElemento(char *nome, char *email, char *telefone);
void insereContato(Lista_e *lista, char *nome, char *email, char *telefone);
void removeContatoIndex (Lista_e *lista, int index);
void removeContatoNome (Lista_e *lista, char *nome);
void mostraContatos(Lista_e lista);
void consultaContato(Lista_e lista, char *nome);
int quantidadeContatos (Lista_e lista);




#endif // LISTA_H_INCLUDED
