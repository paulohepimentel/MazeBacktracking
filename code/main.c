#include <stdio.h>
#include <stdlib.h>
#include "labirinto.h"

int main()
{


    int opcao = 1;
    int carregou = 0;
    char nomeArquivo[20];
    while (opcao == 1 || opcao == 2){
        printf("PROGRAMA Labirinto: Opcoes do programa:\n");
        printf("1) Carregar novo arquivo de dados.\n");
        printf("2) Processar e exibir resposta.\n");
        printf("3 ou qualquer outro caracter) Sair do programa.\n");
        printf("Digite um numero:\n");
        scanf(" %d", &opcao);
        if (opcao == 1){
            carregou = 1;
            printf("Por favor digite o nome do arquivo: \n");
            scanf(" %s", &nomeArquivo);
        } else if (opcao == 2 && carregou == 1){
            FILE* arquivo = fopen(nomeArquivo, "r");
            iniciaJogo(arquivo);

        } else{
            printf("Por favor carregue antes um arquivo de dados! \n");
        }
    }
return 0;
}

