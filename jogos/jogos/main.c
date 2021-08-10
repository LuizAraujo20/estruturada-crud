#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CriaÁ„o de constante (temporario)
#define WORD "batman vs superman"

//ProtÛtipos das funÁıes
void criarCampos(char[], int);
void removerEspacos(int*, int);
void mostrarForca(char[], int, char, int*, int*);
void desenharForca(int);

//Bloco principal
int main(void){
    int tam = strlen(WORD), acer=0, erro=0;
    char campos[tam], opcao = ' ';

    criarCampos(campos, tam);
    removerEspacos(&acer, tam);
    do{
        if((acer < tam) && (erro < 6)){
            mostrarForca(campos, tam, opcao, &acer, &erro);
            fflush(stdin);
            if(acer == tam)
                printf("\n\tParabens! Voce conseguiu!\n\tPressione ENTER para sair.");
            else if(erro == 6)
                printf("\n\tNao foi dessa vez. Tente novamente!\n\tPressione ENTER para sair.");
            fflush(stdin);
            scanf("%c", &opcao);
        }
    }while((acer < tam) && (erro < 6));
    return 0;
}

//CriaÁ„o dos campos de jogo
void criarCampos(char campos[], int tam){
    int i;
    for(i=0; i<tam; i++)
        campos[i] = '_';
}

//Remover espacos da palavra
void removerEspacos(int *acer, int tam){
    int i;
    for(i=0; i<tam; i++){
        if(WORD[i] == ' ')
            *acer += 1;
    }
}
//ExibiÁ„o do jogo
void mostrarForca(char campos[], int tam, char opcao, int *acer, int *erro){
    int i, j=-1;
    
    system("cls");
    printf("\n\tJogo da forca");
    printf("\n\tDigite uma letra: \n\n\t");
    
    //Contar os erros ou acertos
    if(opcao != ' '){
        for(i=0; i<tam; i++){
            if(opcao == WORD[i]){
                if(opcao == campos[i])
                    j = 1;
                else{
                    j = 0;
                    *acer += 1;
                }
            }
        }
        if(j == -1)
            *erro += 1;
        else if (j == 1)
            printf("Letra ja escolhida.\n\t");
    }
    desenharForca(*erro);
    
    //Escrever os campos na tela
    for(i=0; i<tam; i++){
        if(opcao == WORD[i]){
            if(opcao == campos[i])
                printf("%c ", campos[i]);
            else{
                campos[i] = opcao;
                printf("%c ", campos[i]);
            }
        }else
            printf("%c ", campos[i]);
    }
    printf("\n\t");
}

//Desenhar a forca na tela
void desenharForca(int erro){
    switch(erro)
    {
        //Forca vazia
        case 0:
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\t");
            printf("\xBA        \xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t\n\t");
            break;
        case 1:
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\t");
            printf("\xBA        \xBA\n\t");
            printf("\xBA        O\n\t");
            printf("\xBA\n\t");
            printf("\xBA                  1 erro!\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t\n\t");
            break;
        case 2:
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\t");
            printf("\xBA        \xBA\n\t");
            printf("\xBA        O\n\t");
            printf("\xBA        |\n\t");
            printf("\xBA                  2 erros!\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t\n\t");
            break;
        case 3:
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\t");
            printf("\xBA        \xBA\n\t");
            printf("\xBA        O\n\t");
            printf("\xBA       /|\n\t");
            printf("\xBA                  3 erros!\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t\n\t");
            break;
        case 4:
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\t");
            printf("\xBA        \xBA\n\t");
            printf("\xBA        O\n\t");
            printf("\xBA       /|%c\n\t", 92);
            printf("\xBA                  4 erros!\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t\n\t");
            break;
        case 5:
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\t");
            printf("\xBA        \xBA\n\t");
            printf("\xBA        O\n\t");
            printf("\xBA       /|%c\n\t", 92);
            printf("\xBA       /         5 erros!\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t\n\t");
            break;
        case 6:
                printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\t");
            printf("\xBA        \xBA\n\t");
            printf("\xBA        O\n\t");
            printf("\xBA       /|%c\n\t", 92);
            printf("\xBA       / %c        6 erros!\n\t", 92);
            printf("\xBA\n\t");
            printf("\xBA\n\t");
            printf("\xBA\n\t\n\t");
            break;
    }
}
