//
//  main.c
//  estruturada-crud
//
//  Created by Luiz Carlos da Silva Araujo on 06/04/21.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100


int main(int argc, const char * argv[]) {
    int qtdProdutos = 0, indice, codigoEscolha;
    char opcao, flag;
    int inicio, fim, meio;
    
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
                do{
                    //alterar
                    printf("\n\nALTERAR PRODUTO");
                    printf("\nINFORME O CODIGO DO PRODUTO: ");
                    scanf("%d", &codigoEscolha);
                    
                    //algoritmo pesquisa binária
                    inicio = 0;
                    fim = (qtdProdutos - 1);
                    meio = (inicio + fim) / 2;
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
                    
                    if(flag == 'x'){
                        printf("\n\n%-6s  %-20s  %-12s", "Codigo", "Descricao", "Preco(R$)");
                        printf("\n%06d  %-20s  %9.2f", produtos[meio].codigo, produtos[meio].descricao, produtos[meio].valor);
                    
                        printf("\n\nMENU ALTERACAO PRODUTO");
                        printf("\n1 - ALTERAR CODIGO");
                        printf("\n2 - ALTERAR NOME DO PRODUTO");
                        printf("\n3 - ALTERAR PRECO");
                        printf("\n4 - ALTERAR TUDO");
                        printf("\n5 - ESCOLHER OUTRO PRODUTO");
                        printf("\n0 - SAIR DO MENU ALTERACAO");
                        printf("\nOPCAO: ");
                        fflush(stdin);
                        opcao = getchar();
                        
                        if((opcao == '1') || (opcao == '4')){
                                printf("\nNovo codigo: ");
                                scanf("%d", &produtos[meio].codigo);
                        }
                        
                        if((opcao == '2') || (opcao == '4')){
                            if(opcao == '2')
                                printf("\n");
                            printf("Nova descricao: ");
                            fflush(stdin);
                            gets(produtos[meio].descricao);
                        }
                            
                        if((opcao == '3') || (opcao == '4')){
                            printf("\nNovo preco: ");
                            scanf("%f", &produtos[meio].valor);
                        }
                    } else {
                        printf("\n\nNENHUM PRODUTO ENCONTRADO!");
                    }
                }while(opcao == '0');
                
            case '4':
                do{
                    system("clear");
                    //excluir
                    printf("\n\nEXCLUIR PRODUTO");
                    printf("\nINFORME O CODIGO DO PRODUTO: ");
                    scanf("%d", &codigoEscolha);
                    
                    do{
                    //algoritmo pesquisa binária
                        inicio = 0;
                        fim = (qtdProdutos - 1);
                        meio = (inicio + fim) / 2;
                        flag = 'o';
                        
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
                    
                    if(flag == 'x'){
                        printf("\n\n%-6s  %-20s  %-12s", "Codigo", "Descricao", "Preco(R$)");
                        printf("\n%06d  %-20s  %9.2f", produtos[meio].codigo, produtos[meio].descricao, produtos[meio].valor);
                        
                        printf("\nCONFIRMAR EXLUSAO? (s - sim)");
                        printf("\nOPCAO: ");
                        fflush(stdin);
                        opcao = getchar();
                        if((opcao == 's') || (opcao == 'S')){
                            for(indice = meio; indice < qtdProdutos - 1; indice++){
                                produtos[indice] = produtos[indice + 1];
                                produtos[indice].codigo = produtos[indice + 1].codigo;
                                strcpy(produtos[indice].descricao, produtos[indice + 1].descricao);
                                produtos[indice].valor = produtos[indice + 1].valor;
                            }
                            qtdProdutos--;
                        } else {
                            opcao = '0';
                        }
                    } else {
                        printf("\n\nNENHUM PRODUTO ENCONTRADO!");
                    }
                }while(opcao == '0');
                break;
                
                
            case 'X':
            case 'x':
                printf("\n\n\n\n");
                return 0;
        }
        printf("\n\n");
    }while(opcao != 'x');
}
