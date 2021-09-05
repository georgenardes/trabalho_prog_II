#include "lista.h"

lista_e criaLista ()
{
    struct lista_e lista;
    lista->inicio = NULL;
    lista->cont = 0;

    return lista;
}

Elemento *novoElemento (struct Contato contato)
{
    Elemento *novo = (struct Elemento)malloc(sizeof(struct Elemento));
    novo -> contato = contato;
    novo -> proximo = NULL;
    return novo;
}

void insereContato(struct lista_e *lista, struct Contato elemento)
{

    struct Elemento *ponteiro = lista->inicio;

    // Verifica se ja existe algum elemento na lista
    if(ponteiro != NULL)
    {

        // Pega o ultimo elemento da lista
        while(ponteiro -> proximo != NULL)
        {
            ponteiro = ponteiro -> proximo;
        }

        // Cria um novo elemento e atribui o mesmo ao proximo do ultimo
        Elemento *novo = novoElemento (elemento);
        ponteiro -> proximo = novo;
        lista.cont++;

    } else
    {
        // Cria um novo elemento e atribui como inicio da lista
        Elemento *novo = novoElemento (elemento);
        lista.inicio = novo;
        lista.cont++;

    }

    return 0;
}

void removeContato (struct lista_e *lista, int index)
{
    Elemento *elemento = lista->inicio;

    // Verifica se a lista esta vazia
    if (elemento != NULL)
    {

        for (int i = 0; i < index; i++){
            elemento = elemento->proximo;
        }

        // Retira e deleta o primeiro elemento da lista
        lista.inicio = elemento -> proximo;
        lista.cont--;

        free(elemento);

    }
}

void mostraContatos(struct lista_e lista){

    Elemento *elemento = lista->inicio;

    // Verifica se a lista esta vazia
    while (elemento != NULL)
    {
        printf("Nome: %s", elemento.contato.nome);
        elemento = elemento->proximo;

    }

    printf("Fim");

    return 0;
}

int quantidadeContatos (struct lista_e lista)
{
    return lista.cont;
}
