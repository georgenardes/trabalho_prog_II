#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


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


void cabecalho()
{
    gotoxy(0, 0);
    textcolor(LIGHTYELLOW, BLACK);
    printf( "Locadora de Videos");
    gotoxy(0, 1);
    textcolor(YELLOW, BLACK);
    printf( "Engenharia de Computacao - UNIVALI");
    gotoxy(0, 2);
    printf( "<Nome da disciplina>");
    gotoxy(0, 3);
    printf( "Andriy Fujii");
    textcolor(WHITE, BLACK);
    gotoxy(0, 7);

	//Opcional
    printf( "Opcoes:");
    gotoxy(0, 16);
    printf( "Utilize as setas para cima/baixo para selecionar uma opcao");
    gotoxy(0, 17);
    printf( "Pressione Enter para selecionar");
}

//Funcionamento do menu
//Tecla 72 e a setinha p/ cima
//Tecla 80 e a setinha p/ baixo
//Tecla 13 e enter
int menu()
{
    int tecla, aux = 0;
    do{
        textcolor(BRIGHTWHITE, BLACK); //Da "highlight" na opcao selecionada
        gotoxy(18, 7);
        printf( "Adicionar novo video");

        gotoxy(18, 8);
        printf( "View created characters");

        gotoxy(18, 9);
        printf( "Load");

        gotoxy(18, 10);
        printf( "Delete character");

        gotoxy(18, 11);
        printf( "Exit");

        textcolor(BLACK, WHITE);
        switch (aux)
        {
            case 0:
                gotoxy(18, 7);
                printf( "Add new character");
                break;
            case 1:
                gotoxy(18, 8);
                printf( "View created characters");
                break;
            case 2:
                gotoxy(18, 9);
                printf( "Load");
                break;
            case 3:
                gotoxy(18, 10);
                printf( "Delete character");
                break;
            case 4:
                gotoxy(18, 11);
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

#endif // MENU_H_INCLUDED
