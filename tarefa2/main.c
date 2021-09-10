#include <stdio.h>
#include <stdlib.h>

#include "lista.h"


int main()
{
    /*
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

    printf("-----");
    //removeContatoNome(contatos, "George");
    removeContatoIndex(contatos, 1);
    mostraContatos(*contatos);

    //consultaContato(*contatos, "Luiz");

    printf("\nNumero de contatos na agenda: %d\n", quantidadeContatos(*contatos));

    //apagaLista(contatos);
    //mostraContatos(*contatos);

    printf("\nFim do programa!\n");

    return 0;*/
    do {

        // solicita opção para o usuario
        op = menu();

        switch(op){

            case 0:///Pesquisa filmes

                do {
                    char string_pesquisa[255]; // string a ser pesquisada
                    int num_encontrados = 0;       // quantidade de filmes encontrados
                    int filme_selecionado = -1;

                    /// menu de busca
                    op_pesquisa = menu_busca();
                    if (op_pesquisa == 4){ // exit
                        break;
                    }

                    if (op_pesquisa < 3){
                        /// recebe string de pesquisa
                        scanf("%s", &string_pesquisa);
                    }



                    /// exibe resultados
                    //filme_selecionado = mostra_filmes(filmes, tam_filme, 0, vet_indices, num_encontrados);




                } while (op_pesquisa < 4);
                break;

            case 1:///Cadastra filmes


                break;

            case 2:///Deleta filmes

                    do {
                        char string_pesquisa[255]; // string a ser pesquisada

                        /// menu de busca
                        op_pesquisa = menu_busca();
                        if (op_pesquisa == 4){ // exit
                            break;
                        }


                        /// recebe string de pesquisa
                        scanf("%s", &string_pesquisa);


                        do {
                            /// realiza pesquisa no vetor de filme
                            //vet_indices = pesquisar(filmes, tam_filme, op_pesquisa, string_pesquisa, &num_encontrados);

                            /// exibe resultados
                            //pos = mostra_filmes(filmes, tam_filme, 1, vet_indices, num_encontrados);

                            /// exibe info do filme selecionado
                            if (pos != -1){
                                deletar(filmes, pos, &tam_filme);
                                objeto_para_arquivo(arquivo, filmes, tam_filme);
                                num_encontrados--;
                            }
                        } while (pos != -1 || num_encontrados <= 0);

                    } while (op_pesquisa < 4);

                break;

            case 3:///Sai do programa

                objeto_para_arquivo(arquivo, filmes, tam_filme);
                system("cls");
                printf("\nFim do programa!!\n");
                break;
        }
        system("cls");
    } while (op != 3);

    return 0;
}
