// Nome: João Victor Álvares
// Matrícula: UC21106304
// Curso: Engenharia de software

#include <stdio.h> // biblioteca principal em linguagem c, contém funções de entrada e saída
#include <locale.h> // biblioteca para usar a língua portuguesa
// Nome: João Victor Álvares
// Matrícula: UC21106304
// Curso: Engenharia de software

#include <stdio.h> // biblioteca principal em linguagem c, contém funções de entrada e saída
#include <locale.h> // biblioteca para usar a língua portuguesa
#include <stdlib.h> // biblioteca para mudar a cor do sistema
#include <string.h> // biblioteca para reconhecer o comando strlen
#include <ctype.h> // biblioteca para reconhecer o comando tolower

int main () { //ínicio do código
    setlocale(LC_ALL, "Portuguese"); // reconhecimento da língua portuguesa
    system("color 05"); // mudança de cor no sistema
    
    int sessoes, idade, espectadores, i, maiorDeIdadeM=0, maiorDeIdadeF=0; // declarações de inteiro
    char filme[40], sexo, pessoas; // declarações de char
    
    printf("Seja bem vindo ao Cinemark!\n"); // boas vindas ao usuário
    printf("Quantas sessões de filme você deseja?"); // perguntar quantas sessões o usuário deseja
    scanf("%d", &sessoes); // reconhecer a pergunta acima e associar a sessões
    
    while(sessoes > 2) { // ínicio do while, ferramenta para bloquear mais de 2 sessões
        printf("Duas sessões é o máximo permitido!\n"); // ferramenta para bloquear mais de 2 sessões
        printf("Quantas sessões de filme você deseja?"); // perguntar quantas sessões o usuário deseja novamente
        scanf("%d", &sessoes); // reconhecer a pergunta acima e associar a sessões
    } // final do while
    system("cls"); // limpar a tela no sistema
    fflush(stdin); // limpar o buffer de memória
    
    printf("Qual o filme?"); // perguntar o filme para o usuário
    fgets(filme,40,stdin); // reconhecer a pergunta acima, o fgets é necessário caso o filme tenha mais de uma palavra
    
    while(strlen(filme) <= 2) { // início do while, se o char filme tiver 2 ou menos caracteres deve perguntar o filme novamente ao usuário
        printf("Digite o nome do filme!\n"); // alertar o usúario
        printf("Qual o filme?"); // digite o nome do filme
        fgets(filme,40,stdin); // reconhecer a pergunta acima, o fgets é necessário caso o filme tenha mais de uma palavra
        } // final do while
        
        fflush(stdin); //limpar o buffer de memória
        system("cls"); // limpar a tela no sistema
    
    printf("Quantas pessoas assistirão ao filme? (Mínimo 10 pessoas)"); // perguntar o número de pessoas que verão o filme
    scanf("%d", &espectadores); // reconhecer a pergunta acima e associar a espectadores
    
    while(espectadores <= 1) { // ínicio do while, definindo que não pode abaixo de 10 pessoas
        printf("Mínimo 10 pessoas\n"); // alertando o usuário sobre o mínimo de pessoas
        printf("Quantas pessoas assistirão ao filme? (Mínimo 10 pessoas)"); // perguntando novamente ao usuário quantas pessoas assistirão ao filme
        scanf("%d", &espectadores); // reconhecer a pergunta acima e associar a espectadores
    } // final do while
    system("cls"); // limpar a tela no sistema
    
        for(i = 1; i <= espectadores; i++){ // ínicio do for, o 'i' vai aumentando em uma unidade até chegar ao número de espectadores
            
            
            do { // ínicio do do while
                printf("Qual o sexo?"); // perguntar ao usuário qual o sexo, depende do número de espectadores
                fflush(stdin); // limpar o buffer de memória
                scanf("%c", &sexo); // reconhecer a pergunta acima e associar a sexo
                sexo = tolower(sexo); // reconhecer a resposta da pergunta sempre como 'm' ou 'f' MÍNUSCULO
            }while(sexo != 'm' && sexo != 'f'); // final do do while, enquanto for diferente de 'm' e 'f' vai perguntar eternamente
            
            do { // ínicio do do while
                printf("Qual a idade?"); // perguntar ao usuário a idade, depende do número de espectadores
                scanf("%d", &idade); // reconhecer a pergunta acima e associar a idade
            } while(idade < 3 || idade > 100); // final do do while, se a idade não estiver entre 3 e 100 irá perguntar eternamente
            
            
            
            if(idade >= 3 && idade <= 13) { // ínicio do if, se a idade for entre 3 e 13
                printf("Criança\n"); // aparece crinça no sistema
            } else if(idade >= 14 && idade <= 17){ // se a idade for entre 14 e 17
                printf("Adolescente\n"); // aparece adolescente no sistema
            }else if(idade >= 18 && idade <= 64){ // se a idade for entre 18 e 64
               printf("Adulto\n"); // aparece adulto no sistema
            }else{ // se a idade for entre 65 e 100
                printf("Idoso\n"); // aparece idoso no sistema
            } // final do if
            
            if(idade >= 18 && sexo == 'm') {
                maiorDeIdadeM++;
            }
            if(idade >= 18 && sexo == 'f') {
                maiorDeIdadeF++;
            }
        }//fim do fooorrrrrr
                     /* Depois da leitura dos dados de cada sessão, deverá ser mostrada, em uma tela limpa a quantidade de pessoas
maiores de idade (idade maior ou igual a 18 anos) do sexo masculino e a quantidade de pessoas maiores de
idade do sexo feminino que estiveram presentes.*/
                             
            
    fflush(stdin); // limpar o buffer
    system("cls"); // limpar a tela no sistema
    
//    do {
//    } while(((idade >= 18) && (sexo == 'f')) || ((idade >= 18) && (sexo == 'm')));
    
    
            // tabela final
        system("cls"); //limpar a tela
        printf("====================================\n"); // design da tabela
        printf("Seus dados:\n"); // aparecer 'Seus dados' e pular uma linha, no sistema
        printf("Filme: %s", filme); //mostrar o nome do filme
        printf("Pessoas que assistiram o filme: %d\n", espectadores); // número de pessoas que assistiram o filme
        fflush(stdin); // limpar o buffer
        printf("Homens maiores de idade: %i\n", maiorDeIdadeM); // indicar o número de homens maiores de idade
        printf("Mulheres maiores de idade: %i\n", maiorDeIdadeF); // indicar o número de mulheres maiores de idade
        printf("===================================="); // design da tabela

return 0; // serve para informar ao compilador que ocorreu tudo certo com a função main()
} // final do código

