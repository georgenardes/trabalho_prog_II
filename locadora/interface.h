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

void drawBox(int xi, int yi, int x, int y){ // FUNÇÃO PARA DESENHAR PAREDES
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

int menu()
{
    drawBox(0,0, 118, 29);
    int tecla, aux = 0;
    do{
        textcolor(BRIGHTWHITE, BLACK); //Da "highlight" na opcao selecionada
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
