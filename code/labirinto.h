#ifndef LABIRINTO_H_INCLUDED
#define LABIRINTO_H_INCLUDED
#include <stdio.h>

int iniciaJogo(FILE *arquivo);
void imprimeLabirinto(int** labirinto, int linhas, int colunas);
void constroiLabirinto(FILE *arquivo, int** labirinto, int linhas, int colunas);
void localizaCachorro(int** labirinto, int linhas, int colunas, int* linhaCachorro, int* colunaCachorro);

int movimenta_cachorro(int** labirinto, int linhas, int colunas, int i, int j);
int percorreLabirinto(int** labirinto, int linhas, int colunas, int linhaCachorro, int colunaCachorro, int* numMovimentos, int* numChamadas, int* numNivel);

#endif // LABIRINTO_H_INCLUDED
