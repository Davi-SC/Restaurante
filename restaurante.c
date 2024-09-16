#include<stdio.h>
#include<stdio.h>
#include<string.h>

typedef struct{
    int codigo;
    char descricao[100];
    float preco;
    int qtd;
}Produto;

typedef struct{
    Produto produtos[100];
    int qtd;
}Cardapio;

void cadastrar(Cardapio *cardapio);
void imprimir(Cardapio *cardapio);
void excluir(Cardapio *cardapio);
char opcoes();
void fazerPedido(Cardapio *cardapio);

void main(){
    Cardapio cardapio;
    cardapio.qtd = 0;

    while(1){
        fflush(stdin);
        char op = opcoes();
        if(op == '0'){
            break;
        }
        switch(op){
            case '1':
                cadastrar(&cardapio);
                system("pause");
                break;
            case '2':
                imprimir(&cardapio);
                system("pause");
                break;
            case '3':
                excluir(&cardapio);
                system("pause");
                break;
            case '4':
                fazerPedido(&cardapio);
                system("pause");
                break;
            default:
                printf("\nOpcao Invalida!\n");
                system("pause");
        }
    }//Fim do While

}//Fim do Main



char opcoes(){
    system("cls");
    char op;
    printf("============ RESTAURANTE ============\n\n");
    printf("1 - CADASTRAR PRODUTO\n");
    printf("2 - IMPRIMIR cardapio\n");
    printf("3 - EXCLUIR\n");
    printf("4 - FAZER PEDIDO\n");
    printf("0 - SAIR\n");
    printf(">> ");
    scanf("%c", &op);
    return op;
}

void cadastrar(Cardapio *cardapio){
    char descricao[100];
    float preco;
    int qtd;
    system("cls");
    fflush(stdin);
    printf("========== CADASTRAR PRODUTOS ==========\n\n");
    printf("NOME: ");
    gets(descricao);
    printf("PRECO: ");
    scanf("%f", &preco);
    printf("QTD: ");
    scanf("%d", &qtd);

    int codigo;
    if(cardapio->qtd == 0){
        codigo = 1;
    }else{
        codigo = cardapio->produtos[cardapio->qtd - 1].codigo + 1;
    }

    cardapio->produtos[cardapio->qtd].codigo = codigo;
    strcpy(cardapio->produtos[cardapio->qtd].descricao, descricao);
    cardapio->produtos[cardapio->qtd].preco = preco;
    cardapio->produtos[cardapio->qtd].qtd = qtd;
    cardapio->qtd++;

    printf("\nProduto cadastrado com sucesso!\n");
}//Fim do cadastrar

void imprimir(Cardapio *cardapio){
    system("cls");
    printf("========== cardapio ==========\n\n");
    printf("------------------------------------");
    int i;
    for(i=0 ; i<cardapio->qtd ; i++){
        printf("\nCODIGO: %d", cardapio->produtos[i].codigo);
        printf("\nDESCRICAO: ");
        puts(cardapio->produtos[i].descricao);
        printf("PRECO: R$ %.2f", cardapio->produtos[i].preco);
        printf("\nQTD: %d", cardapio->produtos[i].qtd);
        printf("\n------------------------------------");
    }
    printf("\n");
}//fim do Imprimir

void excluir(Cardapio *cardapio){
    system("cls");
    printf("========== EXCLUIR ==========\n\n");
    imprimir(cardapio);
    int c;
    printf("Qual produto deseja excluir?: ");
    scanf("%d", &c);
    int certeza = 0;
    printf("Tem certeza que deseja excluir o produto %d? (1 - SIM; 0 - NAO):", c);
    scanf("%d", &certeza);
    if(certeza == 1){
        int i,j, encontrado = 0;
        for(i = 0; i < cardapio->qtd; i++){
            if(cardapio->produtos[i].codigo == c){
                for(j = i; j < cardapio->qtd - 1; j++){
                    cardapio->produtos[j] = cardapio->produtos[j + 1];
                }
                cardapio->qtd--;
                encontrado = 1;
                break;
            }
        }
        if(encontrado == 0){
            printf("\nProduto nao encontrado!");
        }else{
            printf("\nProduto excluido com sucesso!");
        }
        printf("\n");
    }
}//Fim do Excluir

void fazerPedido(Cardapio *cardapio){
	
}