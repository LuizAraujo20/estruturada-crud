//
//  main.c
//  estruturada-crud
//
//  Created by Luiz Carlos da Silva Araujo on 06/04/21.

#include <stdio.h>
#include <stdlib.h>

#define MAX 100


int main(int argc, const char * argv[]) {
    int qtdProdutos = 0, indice;
    char opcao;
    struct {
        int codigo;
        char descricao[20];
        float valor;
    } produtos[MAX];
    
    do{
        //menu
//        system("CLEAR");
        printf("SGP - SISTEMA DE GERENCIAMENTO DE PRODUTOS\n");
        printf("\nMENU DE PRODUTOS");
        printf("\n1 - INCLUIR");
        printf("\n2 - LISTAR TODOS");
//        printf("3 - PESQUISAR ESPECIFICO");
        printf("\n3 - ALTERAR");
        printf("\n4 - EXCLUIR");
        printf("\nX - SAIR");
        printf("\nOPCAO: ");
        fflush(stdin);
        opcao = getchar();
        
        switch(opcao){
            case '1':
                //incluir
                do{
                    printf("\nINCLUSAO DE PRODUTO");
                    printf("\nCodigo: ");
                    scanf("%d", &produtos[qtdProdutos].codigo);
                    printf("Descricao: ");
                    fflush(stdin);
                    gets(produtos[qtdProdutos].descricao);
                    printf("Preco: ");
                    scanf("%f", &produtos[qtdProdutos].valor);
                    
                    qtdProdutos++;
                    
                    printf("\nNOVA INCLUSAO? (s - sim)\n");
                    fflush(stdin);
                    opcao = getchar();
                }while((opcao == 's') || (opcao == 'S'));
                break;
            case '2':
                //listar
                printf("\n\nLISTAR PRODUTOS");
                
                printf("\n%-6s  %-20s  %-12s", "Codigo", "Descricao", "Preco(R$)");
                for(indice = 0; indice < qtdProdutos; indice++){
                    printf("\n%06d  %-20s  %9.2f", produtos[indice].codigo, produtos[indice].descricao, produtos[indice].valor);
                }
                
                
                break;
//            case '1':
                //pesquisar
//                break;
                
            case '3':
                //alterar
                printf("\n\nALTERAR PRODUTO");
                printf("INFORME O CODIGO DO PRODUTO");
                break;
                
            case '4':
                //excluir
                
                break;
                
                
            case 'X':
            case 'x':
                printf("\n\n\n\n");
                return 0;
        }
        printf("\n\n");
    }while(opcao != 'x');
}
