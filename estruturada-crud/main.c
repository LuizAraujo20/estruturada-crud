//
//  main.c
//  estruturada-crud
//
//  Created by Luiz on 06/04/21.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DECLARAÇÃO DE TIPOS
struct tProdutos{
    int codigo;
    char nome[20];
    float preco;
};

//PROTÓTIPOS
void mostrarProduto(struct tProdutos prod);
void incluirProduto();

int main(int argc, const char * argv[]) {
//declaracoes
    struct tProdutos produto;
//    int indice;
    char opcao = 'a';
    
//instrucoes
    //menu
    printf("  SGP - SISTEMA GERENCIADOR DE PRODUTOS \n");
    
    do{
        printf("\n-> MENU PRINCIPAL");
        printf("\n\t1) INCLUIR");
        printf("\n\t2) LISTAR TUDO");
        printf("\n\t3) PESQUISAR");
        printf("\n\t4) ALTERAR");
        printf("\n\t5) EXCLUIR");
        printf("\n\t0) SAIR\n");
        
        printf("\nOPCAO: \n");
        fflush(stdin);
        scanf("%c", &opcao);
    
        switch(opcao){
            case '1':
            //incluir
                
                
                
                printf("\n\n\n");
                printf("--> INCLUIR PRODUTO");
                
                incluirProduto();
                
                
                break;
                
            case '2':
            //listar tudo
                printf("\n\n\n");
                printf("--> LISTAR TUDO \n");
                printf("\n%-6s %-20s %-12s", "CODIGO", "NOME", "PRECO(R$)");
                
                FILE *arq = fopen("bd_produtos.dat","rb");
                
                while(fread(&produto, sizeof(produto),1,arq)){
                    printf("\n%06d %-20s %9.2f", produto.codigo, produto.nome, produto.preco);
                }
                
                fclose(arq);
                
                printf("\n\n\n");
                break;
                
            case '3':
            //pesquisar
                printf("\n\n\n");
                break;
                
            case '4':
            //alterar
                printf("\n\n\n");
                break;
                
            case '5':
            //excluir
                printf("\n\n\n");
                break;
                
            case '0':
            //sair precisa??????????
                printf("\n\n\n");
                return 0;
                break;
        
        }//fim switch: opcoes menu principal
    }while(1);//do usuario menu principal
}



void mostrarProduto(struct tProdutos prod){
    printf("\n\n%-6s %-20s %-12s", "CODIGO", "NOME", "PRECO(R$)");
    printf("\n%06d %-20s %9.2f", prod.codigo, prod.nome, prod.preco);
}

void incluirProduto(){
    struct tProdutos prod;
    int ultimoCodigo = 0;
    char opcao = 's';
    
    //AUTOINCREMENT COD
    FILE *arq;
    arq = fopen("bd_produtos.dat", "rb");

    while(fread(&prod, sizeof(prod), 1, arq)){
        ultimoCodigo = prod.codigo + 1;
        printf("\n\n\n\nultimoCodigo+ 1\n\n\n");
//        ultimoCodigo++;
    }
    fclose(arq);//tive que separar read do append, pois nao "read" mesmo com a+b
    arq = fopen("bd_produtos.dat", "ab");
    
    printf("\nCODIGO: %d", ultimoCodigo);
    prod.codigo = ultimoCodigo;
    printf("\nNOME: ");
    fflush(stdin);
    gets(prod.nome);
    printf("PRECO : ");
    scanf("%f", &prod.preco);
    
    //SALVAR NO ARQUIVO
    if(arq != NULL){
        fwrite(&prod, sizeof(prod), 1, arq);
    }
    
    fclose(arq);
}


