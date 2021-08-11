

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

