#ifndef DATA_TYPES_H_INCLUDED
#define DATA_TYPES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome[80];
    char genero[25];
    unsigned short ano; // 16 bits
    float duracao;
    char diretor[100];
} Filme;

typedef struct{

    char usuario[50];
    char senha[10];

} Admin;

#endif // DATA_TYPES_H_INCLUDED
