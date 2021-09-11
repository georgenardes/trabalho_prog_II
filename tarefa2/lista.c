#include "lista.h"

// Cria uma lista vazia
Lista_e* criaLista(){
    // Aloca mem�ria para a lista
    Lista_e *contatos = (Lista_e *) malloc(sizeof(Lista_e));

    // Inicializa
    contatos->cont = 0;
    contatos->inicio = NULL;

    return contatos;

}

// Limpa a lista e libera a mem�ria
void apagaLista(Lista_e *lista){

    Elemento *elemento = lista->inicio;

    if (elemento != NULL){
        apagaRec(elemento);

        //Libera mem�ria alocada para a lista
        free(lista);
    }else{// A lista esta vazia
        //Libera mem�ria alocada para a lista
        free(lista);
    }

    printf("Lista excluida");
}

// Fun��o criada para auxiliar na libera��o da lista recursivamente
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
//Fun��o que recebe os atributos de um contato e cria um contato novo
Elemento *novoElemento (char nome[], char email[], char telefone[])
{
    // Aloca mem�ria para um elemento(contato)
    Elemento *novo = (Elemento *)malloc(sizeof(Elemento));

    sprintf(novo->contato.nome, "%s", nome);
    sprintf(novo->contato.email, "%s", email);
    sprintf(novo->contato.telefone, "%s", telefone);

    novo->proximo = NULL;

    return novo;
}

// Fun��o que recebe os atributos de um contato e adiciona na lista
void insereContato(Lista_e *lista, char nome[], char email[], char telefone[])
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
}

// Fun��o que remove um contato da lista atraves do index
void removeContatoIndex (Lista_e *lista, int index)
{
    Elemento *elemento = lista->inicio;
    Elemento *aux = NULL; // Vari�vel auxiliar
    int i = 0;

    // Contato a ser retirado � o primeiro da lista
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
// Fun��o que remove um contato da lista atraves do nome
void removeContatoNome(Lista_e *lista, char *nome)
{
    Elemento *elemento = lista->inicio;
    Elemento *aux = NULL;
    int isFirst = 1;

    // Percorre a lista at� n�o houver proximo elenento
    while(elemento != NULL){

        // Retira e deleta o elemento da lista
        if (strcmp(elemento->contato.nome, nome) == 0){
            // Verifica se n�o � o primeiro elemento da lista
            if(isFirst == 0){

                aux->proximo = elemento->proximo;
                lista->cont--;
                free(elemento);

            }else{
                lista->inicio = elemento->proximo;
                lista->cont--;
                free(elemento);
            }
            break;
        }

        aux = elemento;
        elemento = elemento->proximo;
        isFirst = 0;
    }
}

void mostraContatos(Lista_e lista){

    Elemento *elemento = lista.inicio;

    // Verifica se a lista esta vazia
    while (elemento != NULL)
    {
        printf("\nNome: %s\n", elemento->contato.nome);
        elemento = elemento->proximo;

    }

}

// Fun��o que retorna um contato consultado pelo nome
Elemento* consultaContatoNome(Lista_e lista, char *nome){

    Elemento *elemento = lista.inicio;
    // Verifica se a lista esta vazia
    while (elemento != NULL)
    {
        //Percorre toda a lista e mostra contatos com o mesmo nome
        if(strcmp(elemento->contato.nome, nome) == 0){
            return elemento;
        }
        elemento = elemento->proximo;
    }
    return NULL;
}
// Fun��o que retorna um contato consultado pelo index
Elemento* consultaContatoIndex(Lista_e lista, int index){

    Elemento *elemento = lista.inicio;
    int i = 0;
    // Verifica se a lista esta vazia
    while (elemento != NULL){
        if (i < index){
            elemento = elemento->proximo;
            i++;
        }else{
            return elemento;
        }
    }
    return NULL;

}

// Fun��o que retorna a quantidade de contatos na lista
int quantidadeContatos (Lista_e lista)
{
    return lista.cont;
}
