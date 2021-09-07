#include <stdio.h>
#include <stdlib.h>

#include "lista.h"


int main()
{
    printf("Hello world!\n");

    Lista_e *contatos = NULL;
    contatos = criaLista();

    char *nome = "Paulo";
    char *email = "p@hotmail.com";
    char *telefone = "33322333";

    insereContato(contatos, nome, email, telefone);
    nome = "George";
    insereContato(contatos, nome, email, telefone);
    nome = "Luiz";
    insereContato(contatos, nome, email, telefone);
    mostraContatos(*contatos);

    removeContatoNome(contatos, "George");
    mostraContatos(*contatos);

    consultaContato(*contatos, "Luiz");

    printf("\nNumero de contatos na agenda: %d\n", quantidadeContatos(*contatos));

    printf("\nFim do programa!\n");

    return 0;
}
