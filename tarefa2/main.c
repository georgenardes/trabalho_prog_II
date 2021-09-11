#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <conio.h>

#include "lista.h"

#define BLACK        0
#define WHITE        7
#define BRIGHTWHITE  15

//Esconde o cursor no cmd
void hidecursor()
{
    CONSOLE_CURSOR_INFO cursor = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

//Pula para a posicao (x, y) no cmd
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Muda a cor de escrita
void textcolor(int text, int background)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD) (text | background<<4));
}

void desenha_borda(int xi, int yi, int x, int y){ // FUNÇÃO PARA DESENHAR PAREDES
    int h, l; // VARIAVEL AUXILIAR DE DESENHO
    for(l=0;l<x;l++)   // DESENHA PAREDE HORIZONTAL
    {
        gotoxy(xi+l,yi); printf("%c",205);
        gotoxy(xi+l,yi+y); printf("%c",205);
    }
    for(h=1;h<y;h++)   // DESENHA PAREDE VERTICAL
    {
        gotoxy(xi,yi+h); printf("%c",186);
        gotoxy(xi+x,yi+h); printf("%c",186);
    }
    // PONTAS DA ESQUERDA
    gotoxy(xi,yi); printf("%c", 201); ///superior
    gotoxy(xi,yi+y); printf("%c", 200); ///inferior
    // PONTAS DA DIREITA
    gotoxy(xi+x,yi); printf("%c",187); ///superior
    gotoxy(xi+x, yi+y); printf("%c",188); ///inferior
}

void desenha_coluna(int xi, int yi, int y){
    int h;
    for(h=1;h<y;h++)   // DESENHA PAREDE VERTICAL
    {
        gotoxy(xi,yi+h); printf("%c",186);
    }

}

// limpa parte do console (x inicial, x final, y inicial, y final)
void limpa_bloco (int xi, int xf, int yi, int yf){
    textcolor(BRIGHTWHITE, BLACK);

    for(int i = xi; i < xf; i++){
        for (int j = yi; j < yf; j++){
            gotoxy(i,j);
            printf(" ");
        }
    }
}

int menu(int tamLista){

    desenha_borda(0, 0, 118, 29);
    desenha_coluna(20, 0, 29 );

    int tecla, aux = 0;

    //Para fazer o efeito de seleção, primeiro ele printa as opções normais, depois no switch case ele printa a opção que esta com o cursor com as cores invertidas
    do{
        textcolor(BRIGHTWHITE, BLACK);
        gotoxy(3, 5);
        printf( "Contatos (%d)", tamLista);

        gotoxy(3, 7);
        printf( "Buscar contato");

        gotoxy(3, 9);
        printf( "Novo contato");

        gotoxy(3, 11);
        printf( "Deletar contato");

        gotoxy(3, 14);
        printf( "Exit");


        gotoxy(40, 29);
        printf(" Utilize as setas do teclado para navegar! ");

        textcolor(BLACK, WHITE);
        switch (aux)
        {
            case 0:
                gotoxy(3, 5);
                printf( "Contatos");
                break;
            case 1:
                gotoxy(3, 7);
                printf( "Buscar contato");
                break;
            case 2:
                gotoxy(3, 9);
                printf( "Novo contato");
                break;
            case 3:
                gotoxy(3, 11);
                printf( "Deletar contato");
                break;
            case 4:
                gotoxy(3, 14);
                printf( "Exit");
                break;
        }
        textcolor(WHITE, BLACK);

        tecla = _getch();

        switch (tecla) //Funcionamento da selecao das opcoes
        {
            case 72:
                if (aux != 0)
                    aux--;
                break;
            case 80:
                if (aux != 4)
                    aux++;
                break;
        }
        if (tecla == 13) //Verifica se enter foi pressionado, caso sim, retorna um valor
            return aux;
    }
    while (tecla != 13);
    return -1;
}

///Função que insere um filme no array de filmes
///Recebe o array de filmes e o tamanho do array
void cadastrar(char nome[], char email[], char telefone[]){

    char aux[20];
    int auy = 0, tecla = 0;

        // Filme filme;
        gotoxy(25, 5);
        printf("Nome do contato: ");
        scanf("%s", nome);

        //scanf("%s", &nome);
        //scanf("%s", filme.nome);
        gotoxy(25,6);
        printf("E-mail: ");
        scanf("%s", email);
        //scanf("%s", filme.genero);
        gotoxy(25,7);
        printf("Telefone: ");
        scanf("%s", telefone);
        //scanf("%hu", &(filme.ano));

        //scanf("%s", aux);
        //sprintf(filme->diretor, "%s\n", aux);

        do{
            textcolor(BRIGHTWHITE, BLACK);
            gotoxy(25,11);
            printf("Confirmar?");

            gotoxy(25, 13);
            printf("Sim");

            gotoxy(31, 13);
            printf("Nao");

            textcolor(BLACK, WHITE);
            switch (auy)
            {
                case 0:
                    gotoxy(25, 13);
                    printf("Sim");
                    break;
                case 1:
                    gotoxy(31, 13);
                    printf("Nao");
                    break;
            }
            textcolor(WHITE, BLACK);

            tecla = _getch();

            switch (tecla) //Funcionamento da selecao das opcoes
            {
                // esquerda
                case 75:
                    if (auy != 0)
                        auy--;
                    break;
                // direita
                case 77:
                    if (auy != 1)
                        auy++;
                    break;
            }

            if (tecla == 13) //Verifica se enter foi pressionado, caso sim, retorna um valor
            {
                if(auy == 0){
                    gotoxy(25, 15);
                    printf("Cadastro confirmado!!");
                    //Sleep(1000);
                }else{
                    gotoxy(25, 12);
                    printf("Cadastro cancelado!!");
                    sprintf(nome, "%s", "null");
                    //Sleep(1000);
                }
            }

        }while (tecla != 13);

        return;
}

void busca_contato(char nome[]){

    gotoxy(25, 5);
    printf("Nome: ");
    scanf("%s", nome);

}

//Mostra o nome dos contatos e opcão de info ou deletar (retorna o indice do filme selecionado)
//op = 0 info, op = 1 deletar
int mostra_contatos(Lista_e lista, int qtd, int op){

    desenha_coluna(48, 0, 29);
    limpa_bloco(50, 110, 5, 25);

    int xi = 50, yi = 5;
    int tecla, aux = 0, auy = 0;

    if (qtd <= 0){
        textcolor(BRIGHTWHITE, BLACK);

        gotoxy(xi,yi+(aux*2));
        printf("Nenhum contato cadastrado!!!");

        tecla = _getch();
        limpa_bloco(50, 110, 5, 25);
        return -1;
    }


    do {
        textcolor(BRIGHTWHITE, BLACK);

        Elemento *elemento = lista.inicio;

        int i = 0;
        while(elemento != NULL){
            gotoxy(xi,yi+(i*2));
            printf("%s", elemento->contato.nome);

            gotoxy(xi+40,yi+(i*2));

            if (op == 0){ // op = 0 info, op = 1 deletar
                printf("INFO");
            }else{
                printf("DELETAR");
            }

            elemento = elemento->proximo;
            i++;
        }

        // saida
        gotoxy(xi+40,yi+(qtd*2));
        printf("Exit");

        // destaca opcao selecionada
        textcolor(BLACK, WHITE);
        if (qtd == aux){ // exit option
            gotoxy(xi+40,yi+(aux*2));
            printf("Exit");
        } else {
            gotoxy(xi,yi+(aux*2));

            Elemento *elemento = lista.inicio;
            i = 0;
            while(elemento != NULL){
                if(i< aux){
                    elemento = elemento->proximo;
                    i++;
                }else{
                    break;
                }
            }
            printf("%s",elemento->contato.nome);

            gotoxy(xi+40,yi+(aux*2));
            if (op == 0){ // op = 0 info, op = 1 deletar
                printf("INFO");
            }else{
                printf("DELETAR");
            }

        }

        textcolor(WHITE, BLACK);

        tecla = _getch();

        switch (tecla) //Funcionamento da selecao das opcoes
        {
            // esquerda
            case 75:
                if (auy != 0)
                    auy--;
                break;
            // direita
            case 77:
                if (auy != 1)
                    auy++;
                break;
            // cima
            case 72:
                if (aux != 0)
                    aux--;
                break;

            // baixo
            case 80:
                if (aux != qtd)
                    aux++;
                break;
        }
        if (tecla == 13) //Verifica se enter foi pressionado, caso sim, retorna um valor
        {
            limpa_bloco(50, 110, 5, 25);

            if (aux == qtd)
                return -1;

            /// retorna indice do filme selecionado
            return aux;
        }

    } while (tecla != 13);

    return -1;
}

//Mostra o nome dos contatos e opcão de info (retorna o indice do filme selecionado)
int deleta_contatos(Lista_e lista, int qtd){

    desenha_coluna(48, 0, 29);
    limpa_bloco(50, 110, 5, 25);

    int xi = 50, yi = 5;
    int tecla, aux = 0, auy = 0;

    if (qtd <= 0){
        textcolor(BRIGHTWHITE, BLACK);

        gotoxy(xi,yi+(aux*2));
        printf("Nenhum contato cadastrado!!!");

        tecla = _getch();
        limpa_bloco(50, 110, 5, 25);
        return -1;
    }


    do {
        textcolor(BRIGHTWHITE, BLACK);

        Elemento *elemento = lista.inicio;

        int i = 0;
        while(elemento != NULL){
            gotoxy(xi,yi+(i*2));
            printf("%s", elemento->contato.nome);

            gotoxy(xi+40,yi+(i*2));
            printf("DELETAR");

            elemento = elemento->proximo;
            i++;
        }

        // saida
        gotoxy(xi+40,yi+(qtd*2));
        printf("Exit");

        // destaca opcao selecionada
        textcolor(BLACK, WHITE);
        if (qtd == aux){ // exit option
            gotoxy(xi+40,yi+(aux*2));
            printf("Exit");
        } else {
            gotoxy(xi,yi+(aux*2));

            Elemento *elemento = lista.inicio;
            i = 0;
            while(elemento != NULL){
                if(i< aux){
                    elemento = elemento->proximo;
                    i++;
                }else{
                    break;
                }
            }
            printf("%s",elemento->contato.nome);

            gotoxy(xi+40,yi+(aux*2));
            printf("DELETAR");

        }

        textcolor(WHITE, BLACK);

        tecla = _getch();

        switch (tecla) //Funcionamento da selecao das opcoes
        {
            // esquerda
            case 75:
                if (auy != 0)
                    auy--;
                break;
            // direita
            case 77:
                if (auy != 1)
                    auy++;
                break;
            // cima
            case 72:
                if (aux != 0)
                    aux--;
                break;

            // baixo
            case 80:
                if (aux != qtd)
                    aux++;
                break;
        }
        if (tecla == 13) //Verifica se enter foi pressionado, caso sim, retorna um valor
        {
            limpa_bloco(50, 110, 5, 25);

            if (aux == qtd)
                return -1;

            /// retorna indice do filme selecionado
            return aux;
        }

    } while (tecla != 13);

    return -1;
}

void mostra_contato(Elemento *contato){

    desenha_coluna(48, 0, 29);
    limpa_bloco(50, 110, 5, 25);

    if (contato != NULL){
        gotoxy(50, 5);
        printf("Nome: %s", contato->contato.nome);

        gotoxy(50, 7);
        printf("E-mail: %s", contato->contato.email);

        gotoxy(50, 9);
        printf("Telefone: %s", contato->contato.telefone);
    }else{
        gotoxy(50, 5);
        printf("Nenhum contato!!!");
    }

    int tecla = 0;

    do{
        tecla = _getch();
    }
    while(tecla != 13);

}

int main()
{

    char nome[20];
    char email[30];
    char telefone[15];

    Lista_e *contatos = NULL;
    contatos = criaLista();

    int op = 0, pos, op_pesquisa, index = 0;

    do {

        // solicita opção para o usuario
        op = menu(contatos->cont);

        switch(op){

            case 0: ///Ver contatos

                index = mostra_contatos(*contatos, contatos->cont, 0);

                if(index > -1){
                    Elemento *contato = NULL;
                    contato = consultaContatoIndex(*contatos, index);
                    mostra_contato(contato);
                }

                break;

            case 1: ///Procurar contato

                busca_contato(nome);
                Elemento *contato = NULL;
                contato = consultaContatoNome(*contatos, nome);

                mostra_contato(contato);

                break;

            case 2: ///Cadastra contato

                    cadastrar(nome, email, telefone);
                    if(strcmp(nome, "null") != 0){
                         insereContato(contatos, nome, email, telefone);
                    }
                    else{
                        printf("Cancel");
                    }

                break;

            case 3: ///Deleta contato

                index = mostra_contatos(*contatos, contatos->cont, 1);
                if(index > -1)
                    removeContatoIndex(contatos, index);
                break;

            case 4:///Sai do programa

                system("cls");
                printf("\nFim do programa!!\n");
                break;
        }
        system("cls");
    } while (op != 4);

    return 0;
}
