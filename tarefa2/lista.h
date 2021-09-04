#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inicializa (struct lista_e *lista);
struct Elemento *novoElemento (struct Contato contato);
void insereContato(struct lista_e *lista, struct Contato elemento);
void removeContato(struct lista_e *lista, int index);
void mostraContatos(struct lista_e lista);
int quantidadeContatos (struct lista_e lista);

#endif // LISTA_H_INCLUDED
