#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "file_handler.h"

void deletar(Filme filmes[], int pos, int *tam);
int* pesquisar (Filme filmes[], int tam, int op, const char string_pesquisa[255], int *num_encontrados);

int main() {
    //Variável que irá receber o arquivo
    FILE *arquivo;
    FILE *adm_arquivo;

    int op = 3;
    int op_pesquisa = 0;
    //Array do tipo Filme que irá armazenar os filmes durante a execução do código
    Filme filmes[255];
    //Array do tipo Admin que irá armazenar os adms durante a execução do código
    Admin adms[10];
    //Tamanho do array
    int tam_filme = 0;
    int tam_adms = 0;

    //Transfere os dados do arquivo para o array
    transfere_filme(arquivo, filmes, &tam_filme, "dados.txt");
    transfere_adm(adm_arquivo, adms, &tam_adms, "admin.txt");

    do {

        // solicita opção para o usuario
        op = menu();

        switch(op){

            case 0:///Pesquisa filmes

                do {
                    char string_pesquisa[255]; // string a ser pesquisada
                    int num_encontrados = 0;       // quantidade de filmes encontrados
                    int *vet_indices;          // vetor de indices dos filmes encontrados
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

                    /// realiza pesquisa no vetor de filme
                    vet_indices = pesquisar(filmes, tam_filme, op_pesquisa, string_pesquisa, &num_encontrados);

                    do {
                        /// exibe resultados
                        filme_selecionado = mostra_filmes(filmes, tam_filme, 0, vet_indices, num_encontrados);

                        /// exibe info do filme selecionado
                        if (filme_selecionado != -1){
                            mostra_info(filmes[filme_selecionado]);
                        }
                    } while (filme_selecionado != -1);

                } while (op_pesquisa < 4);
                break;

            case 1:///Cadastra filmes
                if (autenticacao(adms, tam_adms)==1){
                    cadastrar(filmes, &tam_filme);
                    objeto_para_arquivo(arquivo, filmes, tam_filme);
                }
                break;

            case 2:///Deleta filmes
                if(autenticacao(adms, tam_adms)==1){
                    do {
                        char string_pesquisa[255]; // string a ser pesquisada
                        int num_encontrados = 0;       // quantidade de filmes encontrados
                        int *vet_indices;          // vetor de indices dos filmes encontrados
                        int pos = -1;

                        /// menu de busca
                        op_pesquisa = menu_busca();
                        if (op_pesquisa == 4){ // exit
                            break;
                        }

                        if (op_pesquisa < 3){
                            /// recebe string de pesquisa
                            scanf("%s", &string_pesquisa);
                        }

                        do {
                            /// realiza pesquisa no vetor de filme
                            vet_indices = pesquisar(filmes, tam_filme, op_pesquisa, string_pesquisa, &num_encontrados);

                            /// exibe resultados
                            pos = mostra_filmes(filmes, tam_filme, 1, vet_indices, num_encontrados);

                            /// exibe info do filme selecionado
                            if (pos != -1){
                                deletar(filmes, pos, &tam_filme);
                                objeto_para_arquivo(arquivo, filmes, tam_filme);
                                num_encontrados--;
                            }
                        } while (pos != -1 || num_encontrados <= 0);

                    } while (op_pesquisa < 4);
                }
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


///Função que remove do array de filmes
///Recebe o array de Filmes, a posição que deseja ser deletada e tamanho do array
void deletar(Filme filmes[], int pos, int *tam){

    //Se por acaso receber uma posição maior que o tamanho total de filmes
    if(!pos>(*tam)+1){
        printf("Posicao maior que o tamanho do vetor");
        return;
    }
    //Desloca todos os elemento apos a posição "para a esquerda" do array
    for(int i = pos; i < (*tam) - 1; i++){
        filmes[i] = filmes[i+1];
    }

    (*tam)--;

    return;

}

/// pesquisa no vetor de filmes os filmes que contem a string pesquisada
/// retorna um vetor de indices dos filmes que deram match
int* pesquisar (Filme filmes[], int tam, int op, const char string_pesquisa[255], int *num_encontrados) {
    int counter = 0;
    int *vet_indices;

    /// mostrar todos
    if (op == 3) {
        vet_indices = malloc(sizeof(int) * tam);

        for (int i = 0; i < tam; i++){
            vet_indices[i] = i;
        }
        *num_encontrados = tam;
        return vet_indices;
    }


    /// verifica quantos filmes deram match
    for (int i = 0; i < tam; i++){
        /// opcao nome
        if (op == 0) {
            /// verifica se nome contem string_pesquisa
            if (strstr(filmes[i].nome, string_pesquisa) != NULL){
                counter++;
            }
        }
        /// opcao genero
        else if (op == 1){
            /// verifica se genero contem string_pesquisa
            if (strstr(filmes[i].genero, string_pesquisa) != NULL){
                counter++;
            }
        }
        /// opcao ano
        else if (op == 2){
            /// verifica se ano filme igual ano pesquisa
            if (filmes[i].ano == (unsigned short) atoi(string_pesquisa)){
                counter++;
            }
        }
    }

    if (counter <= 0)
        return NULL;

    /// aloca vetor de indice dos encontrados
    vet_indices = malloc(sizeof(int) * counter);
    counter = 0;

    /// armazena os indices dos filmes que deram match
    for (int i = 0; i < tam; i++){
        /// opcao nome
        if (op == 0) {
            /// verifica se nome contem string_pesquisa
            if (strstr(filmes[i].nome, string_pesquisa) != NULL){
                vet_indices[counter] = i; // armazena indice do match
                counter++;
            }
        }
        /// opcao genero
        else if (op == 1){
            /// verifica se genero contem string_pesquisa
            if (strstr(filmes[i].genero, string_pesquisa) != NULL){
                vet_indices[counter] = i; // armazena indice do match
                counter++;
            }
        }
        /// opcao ano
        else if (op == 2){
            /// verifica se ano filme igual ano pesquisa
            if (filmes[i].ano == (unsigned short) atoi(string_pesquisa)){
                vet_indices[counter] = i; // armazena indice do match
                counter++;
            }
        }
    }
    *num_encontrados = counter;
    return vet_indices;
}

