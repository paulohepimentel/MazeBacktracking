#include "labirinto.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int** criaLabirinto(int linhas, int colunas){ //Recebe a quantidade de Linhas e Colunas como Parâmetro

    int i,j; //Variáveis Auxiliares
    int **matriz = (int**)malloc(linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros

    for(i=0; i<linhas; i++){ //Percorre as linhas do Vetor de Ponteiros

        matriz[i] = (int*) malloc(colunas*sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.

        for(j=0; j<colunas; j++){ //Percorre o Vetor de Inteiros atual.
            matriz[i][j] = 0; //Inicializa com 0.
        }
    }
    return matriz; //Retorna o Ponteiro para a Matriz Alocada
}

void imprimeLabirinto(int** labirinto, int linhas, int colunas){

    int i, j;

    /*Imprimindo a coluna de coordenadas*/
    for(i=0; i<colunas; i++){
        printf("\t[%d]",i);
    }

    for(i=0; i<linhas; i++){
        /*Imprimindo a linha de coordenadas*/
        printf("\n\n [%d]",i);

        /*Imprimindo o labirinto*/
        for(j=0; j<colunas; j++){
            printf("\t %d",labirinto[i][j]);
        }
    }
    printf("\n\n");
}

void constroiLabirinto(FILE *arquivo, int** labirinto, int linhas, int colunas){
    int i=0, j=0;

    char caractere;

    fgetc(arquivo);
    while((caractere=fgetc(arquivo)) != EOF){

        if(caractere == '\n'){
            i++;
            j=0;
        }
        else{
            labirinto[i][j] = caractere-48;
            j++;
        }
    }
}

void localizaCachorro(int** labirinto, int linhas, int colunas, int* linhaCachorro, int* colunaCachorro){

    int i,j;

    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++) {

            if(labirinto[i][j] == 2){
                (*linhaCachorro) = i;
                (*colunaCachorro) = j;
            }
        }
    }
}

int iniciaJogo(FILE *arquivo){

    int** labirinto;
    int linhas=0, colunas=0;
    int linhaCachorro = 0, colunaCachorro = 0;

    int numMovimentos = 0;
    int numChamadas =0;
    int numNivel =1;

    fscanf(arquivo,"%d %d", &linhas, &colunas);
    labirinto = criaLabirinto(linhas,colunas);
    constroiLabirinto(arquivo,&*labirinto,linhas,colunas);

    imprimeLabirinto(&*labirinto,linhas,colunas);

    localizaCachorro(&*labirinto,linhas,colunas, &linhaCachorro, &colunaCachorro);
    printf(" O cachorro comeca na coordenada [%d][%d]\n\n",linhaCachorro,colunaCachorro);

    printf("Linhas: %d\nColunas:%d\n\n",linhas-1,colunas-1);

    if(percorreLabirinto(&*labirinto, linhas-1, colunas-1, linhaCachorro, colunaCachorro, &numMovimentos,&numChamadas, &numNivel) == 1){
        printf("\n O cachorro se movimentou %d vezes e chegou na coluna %d da primeira linha  \n\n", numMovimentos, colunaCachorro);
        printf(" Numero de chamadas: %d\n\n", numChamadas);
        printf(" Nivel maximo: %d\n\n", numNivel);
        imprimeLabirinto(&*labirinto,linhas,colunas);
        return 0;
    }
    printf("\n O cachorro se movimentou %d vezes e percebeu que o labirinto nao tem saida. \n\n", numMovimentos);

    return 1;
}

//-------------------------------------------------------------------------------------------------------
int movimenta_cachorro(int** labirinto, int linhas, int colunas, int i, int j){

    /* Confere os limites */
    if(i<0){
        printf(" Passou dos limites i<0\n");
        return 0;
    }
    if(i>linhas){
        printf(" Passou dos limites i>linhas\n");
        return 0;
    }
    if(j<0){
        printf(" Passou dos limites j<0\n");
        return 0;
    }
    if(j>colunas){
        printf(" Passou dos limites j>colunas\n");
        return 0;
    }
    if(labirinto[i][j] == 3){
        printf(" Bateu na parede\n");
        return 0;
    }

    if(labirinto[i][j] == 0){
        printf(" Posicao marcada\n");
        return 0;
    }

    return 1; /* Pode se mover para essa posição */
}

int percorreLabirinto(int** labirinto, int linhas, int colunas, int linhaCachorro, int colunaCachorro, int* numMovimentos, int* numChamadas, int* numNivel){

	if(linhaCachorro==0 && labirinto[linhaCachorro][colunaCachorro]==1){
		labirinto[linhaCachorro][colunaCachorro] = 2;
        return 1;
	}

    if(movimenta_cachorro(labirinto, linhas, colunas,linhaCachorro,colunaCachorro) == 1){
		labirinto[linhaCachorro][colunaCachorro] = 0;
		(*numMovimentos)++;
        /* O cachorro se move para cima */
        printf("Linha: %d  Coluna: %d \n",linhaCachorro-1,colunaCachorro);
        (*numChamadas)++;
        if(percorreLabirinto(labirinto, linhas, colunas, linhaCachorro-1, colunaCachorro,numMovimentos,numChamadas,numNivel) == 1){
            (*numNivel)++;
            return 1;
        }
        /* Se move para o lado direito */
        printf("Linha: %d  Coluna: %d \n",linhaCachorro,colunaCachorro+1);
        (*numChamadas)++;
        if (percorreLabirinto(labirinto, linhas, colunas, linhaCachorro, colunaCachorro+1,numMovimentos,numChamadas,numNivel) == 1){
            (*numNivel)++;
            return 1;
        }
        /* Se move para o lado esquerdo */
        printf("Linha: %d  Coluna: %d \n",linhaCachorro,colunaCachorro-1);
        (*numChamadas)++;
        if (percorreLabirinto(labirinto, linhas, colunas, linhaCachorro, colunaCachorro-1,numMovimentos,numChamadas,numNivel) == 1){
            (*numNivel)++;
            return 1;
        }
        /* Senão "desmarca" posição para recomeçar outra possivel solução */
        labirinto[linhaCachorro][colunaCachorro] = 1;
        (*numMovimentos)++;
        printf(" Backtracking\n");
        return 0;
    }
    return 0;
}
