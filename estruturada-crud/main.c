//
//  main.c
//  estruturada-crud-usuario
//
//  Created by Luiz on 06/04/21.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "produtos.h"

//DECLARACAO DE TIPO
struct tUsuario {
    char deletado; //deletado == '*'
    int id;
    char nome[20];
    float preco;
};

//PROTÓTIPOS
char menu(void);
FILE *abrirArquivo(char[]);
int consultarUltimoId(FILE*);
void gravarUsuario(struct tUsuario, int, FILE*);
void listarUsuarios(FILE*);
int consultarUsuario(int, FILE*);
void excluirUsuario(int, FILE*);
struct tUsuario lerUsuario(int, FILE*);
void excluirFisicamenteUsuario(FILE**, char[]);
void excluirCadastroUsuarios(FILE**, char[]);

int main(void) {
    int id, pos;
    char opcao;
    struct tUsuario usuario;
    FILE *arqUsuario = abrirArquivo("usuarios.dat");
    
    if (arqUsuario == NULL) {
        printf("ERRO de abertura do arquivo de usuarios!");
        return 1;
    }
    printf("SGP - SISTEMA DE GERENCIAMENTO DE USUARIOS\n");
    do {
        
        opcao = menu();
        switch (opcao) {
               case '1':
                    printf("\n\nCADASTRAR USUARIO\n\n");
                
                    id = consultarUltimoId(arqUsuario);
                
                    printf("ID: %06d", id  + 1);
                    usuario.id = id + 1;
                
                    printf("\nNOME: ");
                    fflush(stdin);
                    gets(usuario.nome);
                    printf("PRECO: R$ ");
                    scanf("%f", &usuario.preco);
                    gravarUsuario(usuario, -1, arqUsuario);
                    break;
               case '2':
                    printf("\n\nLISTA COMPLETA\n\n");
                    listarUsuarios(arqUsuario);
                    break;
               case '3':
                    printf("\n\nCONSULTAR USUARIO\n");
                printf("\nInforme o id: ");
                    scanf("%d", &id);
                    pos = consultarUsuario(id, arqUsuario);
                    if (pos > 0) {
                        usuario = lerUsuario(pos, arqUsuario);
//                        printf("ID: %d\n",  usuario.id);
                        printf("NOME: %s\n",  usuario.nome);
                        printf("PRECO    : R$ %.2f\n", usuario.preco);
                    }
                    else
                        printf("ID NAO ENCONTRADO!\n");
                    printf("\n\n");
                    break;
               case '4':
                    printf("\n\nALTERAR USUARIO\n\n");
                    printf("\nInforme o id: ");
                    scanf("%d", &id);
                    pos = consultarUsuario(id, arqUsuario);
                    if (pos > 0) {
                        usuario = lerUsuario(pos, arqUsuario);
                        printf("NOME: %s\n", usuario.nome);
                        printf("Novo nome: ");
                        fflush(stdin);
                        gets(usuario.nome);
                        printf("PRECO: R$ %.2f\n", usuario.preco);
                        printf("Novo preco: R$ ");
                        scanf("%f", &usuario.preco);
                        gravarUsuario(usuario, pos, arqUsuario);
                        printf("\nUSUARIO ALTERADO COM SUCESSO.\n");
                    }
                    else
                        printf("ID NAO ENCONTRADO!\n\n");
                
                    break;
               case '5':
                    printf("\n\nEXCLUIR USUARIO\n\n");
                    printf("Digite o id...: ");
                    scanf("%d", &id);
                    pos = consultarUsuario(id, arqUsuario);
                    if (pos > 0)
                        excluirUsuario(pos, arqUsuario);
                    else
                        printf("ID NAO ENCONTRADO!\n\n");
                    break;
                case '6':
                     printf("\n\nESVAZIAR LIXEIRA COM USUARIOS EXCLUIDOS\n\n");
                     excluirFisicamenteUsuario(&arqUsuario, "usuarios.dat");
                    break;
                case '7':
                     printf("\n\nESVAZIAR CADASTRO\n\n");
                     excluirCadastroUsuarios(&arqUsuario,"usuarios.dat");
        }
    } while(opcao != '0');
    fclose(arqUsuario);
    return 0;
}


char menu(void) {
    char opc;
    printf("\nMENU PRINCIPAL");
    printf("\n1) CADASTRAR USUARIO");
    printf("\n2) LISTA COMPLETA");
    printf("\n3) CONSULTAR USUARIO");
    printf("\n4) ALTERAR USUARIO");
    printf("\n5) EXCLUIR USUARIO");
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



int consultarUltimoId(FILE *arq){
    struct tUsuario user;
    int id = 0, cont = 0;
    
    fseek(arq, 0, SEEK_SET);
    
    while(fread(&user,sizeof(user),1,arq)){
        id = user.id;
        cont++;
    }
    return id;
}

// reg <= 0 grava no final do arquivo
void gravarUsuario(struct tUsuario user, int reg, FILE *arq) {
    if (reg <= 0) {
        user.deletado = ' ';
        fseek(arq, 0, SEEK_END);
    }
    else
        fseek(arq, (reg-1)*sizeof(user), SEEK_SET);
    fwrite(&user, sizeof(user), 1, arq);
}


void listarUsuarios(FILE *arq) {
    struct tUsuario user;
    fseek(arq, 0, SEEK_SET);
       printf(" ID   NOME            VALOR(R$)\n");
       printf("----- -------------------- ----------\n");
    while (fread(&user, sizeof(user), 1, arq))
        if (user.deletado != '*')
            printf("%05d %-20s %10.2f\n", user.id, user.nome, user.preco);
}


int consultarUsuario(int id, FILE *arq) {
    struct tUsuario user;
    int reg=0;
    fseek(arq, 0, SEEK_SET);
    while (fread(&user, sizeof(user), 1, arq)) {
        reg++;
        if ((user.id == id) && (user.deletado != '*'))
            return reg;
    }
    return -1;
}


struct tUsuario lerUsuario(int reg, FILE *arq) {
    struct tUsuario user;
    fseek(arq, (reg-1)*sizeof(user), SEEK_SET);
    fread(&user, sizeof(user), 1, arq);
     return user;
}


void excluirUsuario(int reg, FILE *arq) {
    struct tUsuario user;
    fseek(arq, (reg-1)*sizeof(user), SEEK_SET);
    fread(&user, sizeof(user), 1, arq);
    user.deletado = '*';
    fseek(arq, -sizeof(user), SEEK_CUR);
    fwrite(&user, sizeof(user), 1, arq);
    printf("\nUSUARIO EXCLUIDO COM SUCESSO.\n");
}


void excluirFisicamenteUsuario(FILE **arq, char arquivo[]) {
    struct tUsuario user;
    FILE *arqAux = fopen("usuarios.aux", "wb");
    if (arqAux == NULL)
        printf("\nERRO AO ESVAZIAR LIXEIRA.\n");
        return;
    fseek(*arq, 0, SEEK_SET);
    while (fread(&user, sizeof(user), 1, *arq))
        if (user.deletado != '*')
            fwrite(&user, sizeof(user), 1, arqAux);
    fclose(*arq);
    fclose(arqAux);
    remove(arquivo);
    rename("usuarios.aux", arquivo);
    *arq = abrirArquivo(arquivo);
    printf("\nUSUARIOS EXCLUIDOS APAGADOS COM SUCESSO.\n");
}

void excluirCadastroUsuarios(FILE **arq, char arquivo[]) {
    FILE *arqAux = fopen("usuarios.aux", "wb");
    if (arqAux == NULL){
        printf("\nERRO AO EXCLUIR TODO O CADASTRO.\n");
        return;
    }
    fclose(*arq);
    fclose(arqAux);
    remove(arquivo);
    rename("usuarios.aux", arquivo);
    *arq = abrirArquivo(arquivo);
    printf("\nCADASTRO EXCLUIDO COM SUCESSO.\n");
}











