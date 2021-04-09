//
//  main.c
//  estruturada-crud
//
//  Created by Luiz Carlos da Silva Araujo on 06/04/21.

#include <stdio.h>
#include <stdlib.h>

#define MAX 100


int main(int argc, const char * argv[]) {
    int qtdProdutos = 0, indice, codigoEscolha;
    char opcao, flag;
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
                printf("\nINFORME O CODIGO DO PRODUTO: ");
                scanf("%d", &codigoEscolha);
                
                //algoritmo pesquisa binária
                int inicio = 0, fim = (qtdProdutos - 1);
                int meio = (inicio + fim) / 2;
                flag = 'o';
                do{
                    if(codigoEscolha == produtos[meio].codigo){
                        flag = 'x';
                    } else if(codigoEscolha < produtos[meio].codigo){
                        inicio = 0;
                        fim = meio - 1;
                        meio = (inicio + fim) / 2;
                    } else {
                        inicio = meio + 1;
                        fim = (qtdProdutos - 1);
                        meio = (inicio + fim) / 2;
                    }
                }while((inicio <= fim) && (flag == 'o'));
            
                printf("\n\n%-6s  %-20s  %-12s", "Codigo", "Descricao", "Preco(R$)");
                printf("\n%06d  %-20s  %9.2f", produtos[meio].codigo, produtos[meio].descricao, produtos[meio].valor);
                
                printf("\nMENU ALTERACAO PRODUTO");
                printf("\n1 - ALTERAR CODIGO");
                printf("\n2 - ALTERAR NOME DO PRODUTO");
                printf("\n3 - ALTERAR PRECO");
                printf("\n4 - ALTERAR TUDO");
                printf("\n5 - ESCOLHER OUTRO PRODUTO");
                printf("\n6 - SAIR DO MENU ALTERACAO");
                printf("\nOPCAO: ");
                fflush(stdin);
                opcao = getchar();
                
                switch (opcao) {
                    case '1':
                    case '4':
                        printf("\nNovo codigo: ");
                        scanf("%d", &produtos[meio].codigo);
                        break;
                        
                    case '2':
                    case '4':
                        
                        printf("\nNova descricao: ");
                        fflush(stdin);
                        gets(produtos[meio].descricao);
                        break;
                        
                    case '3':
                    case '4':
                        
                        printf("\nNovo preco: ");
                        scanf("%f", &produtos[meio].valor);
                        break;
                        
                    case '4':
                        
                        break;
                        
                    case '5':
                        
                        break;
                        
                    case '6':
                        
                        break;
                }
                
                
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
