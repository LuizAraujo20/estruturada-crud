//
//  main.c
//  estruturada-crud
//
//  Created by Luiz on 06/04/21.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PRODUTOS "bd_produtos.dat"


//DECLARAÇÃO DE TIPOS
struct tProdutos{
    int codigo;
    char nome[20];
    float preco;
};

//PROTÓTIPOS
void mostrarProduto(int pos); //recebe a posicao do produto no arquivo
void incluirProduto(void);
int pesquisarProduto(void);
void alterarProduto(void);

int main(int argc, const char * argv[]) {
//declaracoes
    FILE *arq;
    struct tProdutos produto;
//    int indice;
    char opcao = 'a', opcaoPosPesquisa = ' ';
    int posicaoProduto;
    
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
        
        printf("\nOPCAO: ");
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
                
                arq = fopen(DB_PRODUTOS,"rb");
                
                while(fread(&produto, sizeof(produto),1,arq)){
                    printf("\n%06d %-20s %9.2f", produto.codigo, produto.nome, produto.preco);
                }
                
                fclose(arq);
                printf("\n\n\n");
                break;
                
            case '3':
                do{
                //pesquisar
                    printf("\n\n\n");
                    
                    //procura
                    
                    posicaoProduto = pesquisarProduto();
                    
                    if(posicaoProduto == -1){
                        printf("\n\nProduto nao encontrado\n");
                        
                    }else{
                        //menu após pesquisa
                        
                        printf("\n\n");
                        mostrarProduto(posicaoProduto);
                        printf("\n");
                        
                        printf("\nO QUE DESEJA FAZER COM O PRODUTO ENCONTRADO? ");
                        printf("\n\t1) ALTERAR");
                        printf("\n\t2) EXCLUIR");
                        printf("\n\t3) PESQUISAR OUTRO PRODUTO");
                        printf("\n\t0) SAIR DA PESQUISA\n");
                        printf("\nOPCAO: ");
                        fflush(stdin);
                        scanf("%c", &opcaoPosPesquisa);
                        switch(opcaoPosPesquisa){
                            case '1':
                //                FUNCAO DE ALTERAR
                                
                                break;
                            case '2':
                //                FUNCAO DE EXCLUIR
                                
                                break;
                //            default:
                            case '0':
                                //sair ok
                                break;
                        }
                    }
                }while(opcaoPosPesquisa == '3'); // 3 é para pesquisar novo produto
    //                printf("\n\n\n");
                break;
                
            case '4':
            //alterar
                printf("\n\n\n");
                alterarProduto();
                printf("\n\n\n");
                break;
                
            case '5':
            //excluir
                printf("\n\n\n");
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



void mostrarProduto(int pos){
    struct tProdutos prod;
    int temp = 0;
    FILE *arq = fopen(DB_PRODUTOS, "rb");
//    fseek(arq, (sizeof(prod) * 3), SEEK_CUR);
    while(fread(&prod, sizeof(prod), 1, arq)){
        temp++;
        if(pos == temp){
            printf("\nCODIGO : %06d", prod.codigo);
            printf("\nPRODUTO: %s", prod.nome);
            printf("\nPRECO  : %.2f", prod.preco);
        }
    }
        
    
    fclose(arq);
}

void incluirProduto(){
    struct tProdutos prod;
    int ultimoCodigo = 0;
//    char opcao = 's';
    
    //AUTOINCREMENT COD
    FILE *arq;
    arq = fopen(DB_PRODUTOS, "rb");

    while(fread(&prod, sizeof(prod), 1, arq)){
        ultimoCodigo = prod.codigo + 1;
        printf("\n\n\n\nultimoCodigo+ 1\n\n\n");
//        ultimoCodigo++;
    }
    fclose(arq);//tive que separar read do append, pois não tava "reading" mesmo com a+b
    arq = fopen(DB_PRODUTOS, "ab");
    
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



int pesquisarProduto(){
    FILE *file = fopen(DB_PRODUTOS, "rb");
    struct tProdutos prod;
    int chavePesquisaCodigo = 0;
//    int chavePesquisa = 0;
    int contadorRegistros = 0, posicao = -1;
    char opcao = ' ';
    
    //MENU PESQUISA
    
    printf("\n---> PESQUISAR POR:");
    printf("\n\t1) CODIGO");
//    printf("\n\t2) NOME");
//    printf("\n\t3) PRECO");
    printf("\n\t0) SAIR\n");
    printf("\nOPCAO: ");
    fflush(stdin);
    scanf("%c", &opcao);

    switch(opcao){
        case '1':
            //PESQUISAR POR CODIGO
            printf("\nINFORME O CODIGO: ");
            scanf("%d", &chavePesquisaCodigo);
            
            //pesquisa a posicao do código solicitado
//            do{
//                posicao++;
//            }while((fread(&prod,sizeof(prod), 1, file)) && (prod.codigo != chavePesquisaCodigo));
            while((fread(&prod,sizeof(prod), 1, file))){
                contadorRegistros++;
                if(prod.codigo == chavePesquisaCodigo)
                    posicao = contadorRegistros;
            }
            
            break;
            
        case '2':
            //PESQUISAR POR NOME
//            int codigoPesquisa = 0;
            break;
        case '3':
//            PESQUISAR POR PRECO
            break;
        case '0':
            //SAIR
            break;
    }
    
    return posicao;
}

void alterarProduto(){
    struct tProdutos prod;
//    int ultimoCodigo = 0;
//    char opcao = 's';
    
    //AUTOINCREMENT COD
    int posicaoProduto, temp = 0;
//    arq = fopen("bd_produtos.dat", "rb");

//    while(fread(&prod, sizeof(prod), 1, arq)){
//        ultimoCodigo = prod.codigo + 1;
//        printf("\n\n\n\nultimoCodigo+ 1\n\n\n");
////        ultimoCodigo++;
//    }
//    fclose(arq);//tive que separar read do append, pois não tava "reading" mesmo com a+b
    
    
    printf("\n\nALTERAR PRODUTO\n\n");
    
    posicaoProduto = pesquisarProduto();
    
    
    
    
    
//    if(posicaoProduto > -1){
        //menu após pesquisa
        
        printf("\n\n");
        mostrarProduto(posicaoProduto);
        printf("\n");
        
//        printf("\nCONFIRMAR ALTERACAO? (s - sim)");
//        printf("\nOPCAO: ");
//        fflush(stdin);
//        char confirmarAlteracao;
//        scanf("%c", &confirmarAlteracao);
//        if(confirmarAlteracao == 's' || confirmarAlteracao == 'S'){
//
//        }
        
        
        
//    }
//}while(opcaoPosPesquisa == '3'); // 3 é para pesquisar novo produto
    
    
    

    
    
    printf("\nALTERACAO PRODUTO");
    
    FILE *arq = fopen(DB_PRODUTOS, "rb");
    while(fread(&prod, sizeof(prod), 1, arq)){
        temp++;
        if(posicaoProduto == temp){
            printf("\nCODIGO : %06d", prod.codigo);
        }
    }
    fclose(arq);
    
    printf("\nNOVO NOME: ");
    fflush(stdin);
    gets(prod.nome);
    printf("NOVO PRECO : ");
    scanf("%f", &prod.preco);
    
    if(posicaoProduto > 0)
        posicaoProduto--;
    
    arq = fopen(DB_PRODUTOS, "ab");
    
    
    if(arq != NULL){
        while(fread(&prod, sizeof(prod), 1, arq)){
            temp++;
            if(posicaoProduto  == temp){
                arrumar o alterar
                fwrite(&prod, sizeof(prod), 1, arq);
            }
        }
    //SALVAR NO ARQUIVO
    } else {
        printf("ERRO AO SALllllllVAR");
    }
    
    fclose(arq);
}






