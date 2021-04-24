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
    char deletado;
    int codigo;
    char nome[20];
    float preco;
};

//PROTÓTIPOS
void mostrarProduto(int pos); //recebe a posicao do produto no arquivo
void incluirProduto(void);
int receberCodigo(void);
int pesquisarProduto(void);
void alterarProduto(int cod);
void excluirProduto(int cod);

int main(int argc, const char * argv[]) {
//declaracoes
    FILE *arq;
    struct tProdutos produto;
//    int indice;
    char opcao = 'a', opcaoPosPesquisa = ' ';
    int posicaoProduto, cod;
    
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
                
                while((fread(&produto, sizeof(produto),1,arq))){
                    if(produto.deletado != '*')
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
                    
                    cod = pesquisarProduto();
                    
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
                                alterarProduto(cod);
                                break;
                            case '2':
                //                FUNCAO DE EXCLUIR
                                excluirProduto(cod);
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
                alterarProduto(cod);
                printf("\n\n\n");
                break;
                
            case '5':
            //excluir
                printf("\n\n\n");
                excluirProduto(cod);
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



void mostrarProduto(int cod){
    struct tProdutos prod;
    FILE *arq = fopen(DB_PRODUTOS, "rb");
    while(fread(&prod, sizeof(prod), 1, arq)){
        if((prod.codigo == cod) && (prod.deletado == ' ')) {
            printf("\nCODIGO : %06d", prod.codigo);
            printf("\nDElETADO : %c", prod.deletado);
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
//        printf("\n\n\n\nultimoCodigo+ 1\n\n\n");
//        ultimoCodigo++;
    }
    fclose(arq);//tive que separar read do append, pois não tava "reading" mesmo com a+b
    arq = fopen(DB_PRODUTOS, "ab");
    
    printf("\nCODIGO: %d", ultimoCodigo);
    prod.codigo = ultimoCodigo;
    
    prod.deletado = ' ';
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


// Receber codigo ******************************************************************
int receberCodigo(void) {
    int codigo;
    printf("Digite o codigo...: ");
    scanf("%d", &codigo);
    return codigo;
}


int pesquisarProduto(){
    struct tProdutos prod;
//    int chavePesquisa = 0;
    int cod;
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
            scanf("%d", &cod);
            
            int achei=0;
            FILE *arq = fopen(DB_PRODUTOS, "rb");
            if (arq == NULL) {
                printf("Erro de abertura!");
                return -1;
            }
            while (fread(&prod, sizeof(prod), 1, arq)) {
                if ((prod.codigo == cod) && (prod.deletado != '*')) {
                    mostrarProduto(cod);
                    achei = 1;
                }
            }
            if (!achei)
                printf("Codigo nao encontrado!!!\n\n");
            fclose(arq);
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
    
    return cod;
}

void alterarProduto(int cod){
    struct tProdutos prod;
    int achei=0;
    FILE *arq = fopen(DB_PRODUTOS, "r+b");
    if (arq == NULL) {
        printf("Erro de abertura!");
        return;
    }
    cod = receberCodigo();
    
    while (fread(&prod, sizeof(prod), 1, arq)) {
        if ((prod.codigo == cod) && (prod.deletado != '*')) {
            mostrarProduto(cod);
            achei = 1;
//            receberProduto(&prod);
            printf("\nNOME: ");
            fflush(stdin);
            gets(prod.nome);
            printf("PRECO : ");
            scanf("%f", &prod.preco);
            
            fseek(arq, (sizeof(prod) * -1), SEEK_CUR);
            fwrite(&prod, sizeof(prod), 1, arq);
            fseek(arq, 0, SEEK_CUR); // ATENCAO = foi colocado devido ao ponteiro ficar perdido entre leitura e grava��o. NAO REMOVA ESTA LINHA!
        }
    }
    if (!achei)
        printf("Codigo nao encontrado!!!\n\n");
    fclose(arq);
}

void excluirProduto(int cod) {
    struct tProdutos prod;
    int achei=0;
    FILE *arq = fopen(DB_PRODUTOS, "r+b");
    if (arq == NULL) {
        printf("Erro de abertura!");
        return;
    }
    cod = receberCodigo();
    while (fread(&prod, sizeof(prod), 1, arq)) {
        if ((prod.codigo == cod) && (prod.deletado != '*')) {
            mostrarProduto(cod);
            achei = 1;
            prod.deletado = '*';
            fseek(arq, (sizeof(prod) * -1), SEEK_CUR);
            fwrite(&prod, sizeof(prod), 1, arq);
//            fseek(arq, 0, SEEK_CUR); // ATENCAO = foi colocado devido ao ponteiro ficar perdido entre leitura e grava��o. NAO REMOVA ESTA LINHA!
            printf("Excluido com sucesso!\n");
        }
    }
    if (!achei)
        printf("Codigo nao encontrado!!!\n\n");
    fclose(arq);
}




