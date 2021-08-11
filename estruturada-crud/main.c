//
//  main.c
//  estruturada-crud
//
//  Created by Luiz on 06/04/21.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "produtos.h"

//#define DB_PRODUTOS "bd_produtos.dat"

//DECLARACAO DE TIPO
struct tProduto {
    char deletado; //deletado == '*'
    int codigo;
    char nome[20];
    float preco;
};

//PROTÓTIPOS
char menu(void);
FILE *abrirArquivo(char[]);
int consultarUltimoCodigo(FILE*);
void gravarProduto(struct tProduto, int, FILE*);
void listarProdutos(FILE*);
int consultarProduto(int, FILE*);
void excluirProduto(int, FILE*);
struct tProduto lerProduto(int, FILE*);
void excluirFisicamenteProduto(FILE**, char[]);
void excluirCadastroProdutos(FILE**, char[]);

int main(void) {
    int codigo, pos;
    char opcao;
    struct tProduto produto;
    FILE *arqProduto = abrirArquivo("produtos.dat");
    
    if (arqProduto == NULL) {
        printf("ERRO de abertura do arquivo de produtos!");
        return 1;
    }
    printf("SGP - SISTEMA DE GERENCIAMENTO DE PRODUTOS\n");
    do {
        
        opcao = menu();
        switch (opcao) {
               case '1':
                    printf("\n\nCADASTRAR PRODUTO\n\n");
                
                    codigo = consultarUltimoCodigo(arqProduto);
                
                    printf("CODIGO: %06d", codigo  + 1);
                    produto.codigo = codigo + 1;
                
                    printf("\nNOME: ");
                    fflush(stdin);
                    gets(produto.nome);
                    printf("PRECO: R$ ");
                    scanf("%f", &produto.preco);
                    gravarProduto(produto, -1, arqProduto);
                    break;
               case '2':
                    printf("\n\nLISTA COMPLETA\n\n");
                    listarProdutos(arqProduto);
                    break;
               case '3':
                    printf("\n\nCONSULTAR PRODUTO\n");
                printf("\nInforme o codigo: ");
                    scanf("%d", &codigo);
                    pos = consultarProduto(codigo, arqProduto);
                    if (pos > 0) {
                        produto = lerProduto(pos, arqProduto);
//                        printf("CODIGO: %d\n",  produto.codigo);
                        printf("DESCRICAO: %s\n",  produto.nome);
                        printf("PRECO    : R$ %.2f\n", produto.preco);
                    }
                    else
                        printf("CODIGO NAO ENCONTRADO!\n");
                    printf("\n\n");
                    break;
               case '4':
                    printf("\n\nALTERAR PRODUTO\n\n");
                    printf("\nInforme o codigo: ");
                    scanf("%d", &codigo);
                    pos = consultarProduto(codigo, arqProduto);
                    if (pos > 0) {
                        produto = lerProduto(pos, arqProduto);
                        printf("DESCRICAO: %s\n", produto.nome);
                        printf("Novo nome: ");
                        fflush(stdin);
                        gets(produto.nome);
                        printf("PRECO: R$ %.2f\n", produto.preco);
                        printf("Novo preco: R$ ");
                        scanf("%f", &produto.preco);
                        gravarProduto(produto, pos, arqProduto);
                        printf("\nPRODUTO ALTERADO COM SUCESSO.\n");
                    }
                    else
                        printf("CODIGO NAO ENCONTRADO!\n\n");
                
                    break;
               case '5':
                    printf("\n\nEXCLUIR PRODUTO\n\n");
                    printf("Digite o codigo...: ");
                    scanf("%d", &codigo);
                    pos = consultarProduto(codigo, arqProduto);
                    if (pos > 0)
                        excluirProduto(pos, arqProduto);
                    else
                        printf("CODIGO NAO ENCONTRADO!\n\n");
                    break;
                case '6':
                     printf("\n\nESVAZIAR LIXEIRA COM PRODUTOS EXCLUIDOS\n\n");
                     excluirFisicamenteProduto(&arqProduto, "produtos.dat");
                    break;
                case '7':
                     printf("\n\nESVAZIAR CADASTRO\n\n");
                     excluirCadastroProdutos(&arqProduto,"produtos.dat");
        }
    } while(opcao != '0');
    fclose(arqProduto);
    return 0;
}


char menu(void) {
    char opc;
    printf("\nMENU PRINCIPAL");
    printf("\n1) CADASTRAR PRODUTO");
    printf("\n2) LISTA COMPLETA");
    printf("\n3) CONSULTAR PRODUTO");
    printf("\n4) ALTERAR PRODUTO");
    printf("\n5) EXCLUIR PRODUTO");
    printf("\n6) ESVAZIAR LIXEIRA");
    printf("\n7) EXCLUIR TODO CADASTRO");
    printf("\n0) SAIR");
    printf("\nOPCAO: ");
    fflush(stdin);
    scanf("%c", &opc);
    return opc;
}


FILE *abrirArquivo(char arquivo[]) {
    FILE *arq = fopen(arquivo, "r+b");
    if (arq == NULL)
        arq = fopen(arquivo, "w+b");
    return arq;
}



int consultarUltimoCodigo(FILE *arq){
    struct tProduto prod;
    int cod = 0, cont = 0;
    
    fseek(arq, 0, SEEK_SET);
    
    while(fread(&prod,sizeof(prod),1,arq)){
        cod = prod.codigo;
        cont++;
    }
    return cod;
}

// reg <= 0 grava no final do arquivo
void gravarProduto(struct tProduto prod, int reg, FILE *arq) {
    if (reg <= 0) {
        prod.deletado = ' ';
        fseek(arq, 0, SEEK_END);
    }
    else
        fseek(arq, (reg-1)*sizeof(prod), SEEK_SET);
    fwrite(&prod, sizeof(prod), 1, arq);
}


void listarProdutos(FILE *arq) {
    struct tProduto prod;
    fseek(arq, 0, SEEK_SET);
       printf(" COD   DESCRICAO            VALOR(R$)\n");
       printf("----- -------------------- ----------\n");
    while (fread(&prod, sizeof(prod), 1, arq))
        if (prod.deletado != '*')
            printf("%05d %-20s %10.2f\n", prod.codigo, prod.nome, prod.preco);
}


int consultarProduto(int cod, FILE *arq) {
    struct tProduto prod;
    int reg=0;
    fseek(arq, 0, SEEK_SET);
    while (fread(&prod, sizeof(prod), 1, arq)) {
        reg++;
        if ((prod.codigo == cod) && (prod.deletado != '*'))
            return reg;
    }
    return -1;
}


struct tProduto lerProduto(int reg, FILE *arq) {
    struct tProduto prod;
    fseek(arq, (reg-1)*sizeof(prod), SEEK_SET);
    fread(&prod, sizeof(prod), 1, arq);
     return prod;
}


void excluirProduto(int reg, FILE *arq) {
    struct tProduto prod;
    fseek(arq, (reg-1)*sizeof(prod), SEEK_SET);
    fread(&prod, sizeof(prod), 1, arq);
    prod.deletado = '*';
    fseek(arq, -sizeof(prod), SEEK_CUR);
    fwrite(&prod, sizeof(prod), 1, arq);
    printf("\nPRODUTO EXCLUIDO COM SUCESSO.\n");
}


void excluirFisicamenteProduto(FILE **arq, char arquivo[]) {
    struct tProduto prod;
    FILE *arqAux = fopen("produtos.aux", "wb");
    if (arqAux == NULL)
        printf("\nERRO AO ESVAZIAR LIXEIRA.\n");
        return;
    fseek(*arq, 0, SEEK_SET);
    while (fread(&prod, sizeof(prod), 1, *arq))
        if (prod.deletado != '*')
            fwrite(&prod, sizeof(prod), 1, arqAux);
    fclose(*arq);
    fclose(arqAux);
    remove(arquivo);
    rename("produtos.aux", arquivo);
    *arq = abrirArquivo(arquivo);
    printf("\nPRODUTOS EXCLUIDOS APAGADOS COM SUCESSO.\n");
}

void excluirCadastroProdutos(FILE **arq, char arquivo[]) {
    FILE *arqAux = fopen("produtos.aux", "wb");
    if (arqAux == NULL){
        printf("\nERRO AO EXCLUIR TODO O CADASTRO.\n");
        return;
    }
    fclose(*arq);
    fclose(arqAux);
    remove(arquivo);
    rename("produtos.aux", arquivo);
    *arq = abrirArquivo(arquivo);
    printf("\nCADASTRO EXCLUIDO COM SUCESSO.\n");
}











