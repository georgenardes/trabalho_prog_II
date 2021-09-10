#include "lista.h"

// Cria uma lista vazia
Lista_e* criaLista(){


    Lista_e *contatos = (Lista_e *) malloc(sizeof(Lista_e));

    contatos->cont = 0;
    contatos->inicio = NULL;

    return contatos;

}

void apagaLista(Lista_e *lista){

    Elemento *elemento = lista->inicio;

    if (elemento != NULL){
        apagaRec(elemento);

        //Libera memória alocada para a lista
        free(lista);
    }else{// A lista esta vazia
        //Libera memória alocada para a lista
        free(lista);
    }

    printf("Lista excluida");
}

void apagaRec(Elemento *contato){

    if(contato->proximo != NULL){
        apagaRec(contato->proximo);
        printf("Apagando contato: %s\n", contato->contato.nome);
        free(contato);
    }else{
        printf("Apagando contato: %s\n", contato->contato.nome);
        free(contato);
    }

}

Elemento *novoElemento (char *nome, char *email, char *telefone)
{
    Elemento *novo = (Elemento *)malloc(sizeof(Elemento));

    novo->contato.nome = nome;
    novo->contato.email = email;
    novo->contato.telefone = telefone;

    novo->proximo = NULL;

    return novo;
}

void insereContato(Lista_e *lista, char *nome, char *email, char *telefone)
{

    Elemento *ponteiro = lista->inicio;

    // Verifica se ja existe algum elemento na lista
    if(ponteiro != NULL)
    {

        // Pega o ultimo elemento da lista
        while(ponteiro -> proximo != NULL)
        {
            ponteiro = ponteiro -> proximo;
        }

        // Cria um novo elemento e atribui o mesmo ao proximo do ultimo
        Elemento *novoContato = novoElemento (nome, email, telefone);
        ponteiro->proximo = novoContato;
        lista->cont++;

    } else
    {
        // Cria um novo elemento e atribui como inicio da lista
        Elemento *novoContato = novoElemento (nome, email, telefone);
        lista->inicio = novoContato;
        lista->cont++;

    }

    return 0;
}

//Arrumar
void removeContatoIndex (Lista_e *lista, int index)
{
    Elemento *elemento = lista->inicio;
    Elemento *aux = NULL;
    int i = 0;

    // Contato a ser retirado é o primeiro da lista
    if(index == 0){
        lista->inicio = elemento->proximo;
        lista->cont--;
        free(elemento);
        return 0;
    }

    while(elemento->proximo != NULL){

        if(i < index){
            aux = elemento;
            elemento = elemento->proximo;
            i++;
        }else{
            aux->proximo = elemento->proximo;
            lista->cont--;
            free(elemento);
            break;
        }
    }
}

void removeContatoNome(Lista_e *lista, char *nome)
{
    Elemento *elemento = lista->inicio;
    Elemento *aux = NULL;
    int isFirst = 1;

    // Percorre a lista até não houver proximo elenento
    while(elemento != NULL){

        // Retira e deleta o elemento da lista
        if (elemento->contato.nome == nome){

            if(isFirst == 0){

                aux->proximo = elemento->proximo;
                lista->cont--;
                free(elemento);

            }else{
                lista->inicio = elemento->proximo;
                lista->cont--;
                free(elemento);
            }

            printf("\nContato deletado\n");
            return 0;
        }

        aux = elemento;
        elemento = elemento->proximo;
        isFirst = 0;
    }

    printf("\nNao ha contato com este nome\n");
    return 0;

}

void mostraContatos(Lista_e lista){

    Elemento *elemento = lista.inicio;

    // Verifica se a lista esta vazia
    while (elemento != NULL)
    {
        printf("\nNome: %s\n", elemento->contato.nome);
        elemento = elemento->proximo;

    }

    //printf("\nSem mais contatos\n");

    return 0;
}

void consultaContato(Lista_e lista, char *nome){

    Elemento *elemento = lista.inicio;
    // Verifica se a lista esta vazia
    while (elemento != NULL)
    {
        //Percorre toda a lista e mostra contatos com o mesmo nome
        if(elemento->contato.nome == nome){
            printf("\nNome: %s\n", elemento->contato.nome);
            printf("\nEmail: %s\n", elemento->contato.email);
            printf("\nTelefone: %s\n", elemento->contato.telefone);
        }

        elemento = elemento->proximo;
    }
    return 0;
}

int quantidadeContatos (Lista_e lista)
{
    return lista.cont;
}
