#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <windows.h>
#include <conio.h>

#define BLACK        0
#define BLUE         1
#define GREEN        2
#define AQUA         3
#define RED          4
#define PURPLE       5
#define YELLOW       6
#define WHITE        7
#define GRAY         8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTAQUA    11
#define LIGHTRED     12
#define LIGHTPURPLE  13
#define LIGHTYELLOW  14
#define BRIGHTWHITE  15

typedef struct {
    char nome[80];
    char genero[25];
    unsigned short ano; // 16 bits
    float duracao;
    char diretor[100];
} Filme;


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

//Mostra o nome dos filmes e opcão de info (retorna o indice do filme selecionado)
int mostra_filmes(Filme filmes[], int tam, int *vet_indices, int num_encontrados){

    desenha_coluna(48, 0, 29);
    limpa_bloco(50, 110, 5, 25);

    int xi = 50, yi = 5;
    int tecla, aux = 0, auy = 0;


    if (num_encontrados <= 0){
        textcolor(BRIGHTWHITE, BLACK);

        gotoxy(xi,yi+(aux*2));
        printf("Nenhum filme encontrado!");

        tecla = _getch();
        limpa_bloco(50, 110, 5, 25);
        return -1;
    }


    do {
        textcolor(BRIGHTWHITE, BLACK);

        // mostra todos filmes encontrados
        for(int i = 0; i < num_encontrados; i++){
            gotoxy(xi,yi+(i*2));
            printf("%s",filmes[vet_indices[i]].nome);

            gotoxy(xi+40,yi+(i*2));
            printf("INFO");
        }

        // saida
        gotoxy(xi+40,yi+(num_encontrados*2));
        printf("Exit");

        // destaca opcao selecionada
        textcolor(BLACK, WHITE);
        if (num_encontrados == aux){ // exit option
            gotoxy(xi+40,yi+(aux*2));
            printf("Exit");
        } else {                    // filme[aux]
            gotoxy(xi,yi+(aux*2));
            printf("%s",filmes[vet_indices[aux]].nome);

            gotoxy(xi+40,yi+(aux*2));
            printf("INFO");
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
                if (aux != num_encontrados)
                    aux++;
                break;
        }
        if (tecla == 13) //Verifica se enter foi pressionado, caso sim, retorna um valor
        {
            limpa_bloco(50, 110, 5, 25);

            if (aux == num_encontrados)
                return -1;

            /// retorna indice do filme selecionado
            return vet_indices[aux];
        }

    } while (tecla != 13);

    return -1;
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


void mostra_info (Filme filme){
    int xi = 50, yi = 5;

    // limpa parte para escrever info
    limpa_bloco(50, 110, 5, 20);

    gotoxy(xi,yi++);
    printf("Info.");
    gotoxy(xi,yi++);
    printf("Nome: %s", filme.nome);
    gotoxy(xi,yi++);
    printf("Genero: %s", filme.genero);
    gotoxy(xi,yi++);
    printf("Ano: %d", (int)filme.ano);
    gotoxy(xi,yi++);
    printf("Duracao: %.2f", filme.duracao);
    gotoxy(xi,yi++);
    printf("Diretor: %s", filme.diretor);
    gotoxy(xi,yi++);

    // divisao
    for (int j = 0; j < 50; j++)
        printf("=");

    getch();

    // limpa parte escrita
    limpa_bloco(50, 110, 5, 20);
}



int menu_busca(){

    int tecla, aux = 0, yi = 5;

    // limpa bloco para escrever opções
    limpa_bloco(25, 48, 5, 14);

    do{
        textcolor(BRIGHTWHITE, BLACK);
        gotoxy(25, 5);
        printf("Nome");

        gotoxy(25, 7);
        printf("Genero");

        gotoxy(25, 9);
        printf("Ano");

        gotoxy(25, 14);
        printf("Exit");

        textcolor(BLACK, WHITE);
        switch (aux)
        {
            case 0:
                gotoxy(25, 5);
                printf("Nome");
                break;
            case 1:
                gotoxy(25, 7);
                printf("Genero");
                break;
            case 2:
                gotoxy(25, 9);
                printf("Ano");
                break;
            case 3:
                gotoxy(25, 14);
                printf("Exit");
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
                if (aux != 3)
                    aux++;
                break;
        }

        if (tecla == 13) //Verifica se enter foi pressionado, caso sim, retorna um valor
        {
            gotoxy(35,yi+(aux*2));
            printf(":");
            gotoxy(36,yi+(aux*2));
            return aux;
        }

    }
    while (tecla != 13);
    return -1;

}

int menu(){

    desenha_borda(0, 0, 118, 29);
    desenha_coluna(20, 0, 29 );

    int tecla, aux = 0;

    //Para fazer o efeito de seleção, primeiro ele printa as opções normais, depois no switch case ele printa a opção que esta com o cursor com as cores invertidas
    do{
        textcolor(BRIGHTWHITE, BLACK);
        gotoxy(5, 5);
        printf( "Pesquisar");

        gotoxy(5, 8);
        printf( "Cadastrar");

        gotoxy(5, 9);
        printf( "Deletar");

        gotoxy(5, 14);
        printf( "Exit");

        textcolor(BLACK, WHITE);
        switch (aux)
        {
            case 0:
                gotoxy(5, 5);
                printf( "Pesquisar");
                break;
            case 1:
                gotoxy(5, 8);
                printf( "Cadastrar");
                break;
            case 2:
                gotoxy(5, 9);
                printf( "Deletar");
                break;
            case 3:
                gotoxy(5, 14);
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
                if (aux != 3)
                    aux++;
                break;
        }
        if (tecla == 13) //Verifica se enter foi pressionado, caso sim, retorna um valor
            return aux;
    }
    while (tecla != 13);
    return -1;
}


#endif // INTERFACE_H_INCLUDED
