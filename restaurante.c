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
}Menu;

void cadastrar(Menu *menu);
void imprimir(Menu *menu);
void excluir(Menu *menu);
char opcoes();

void main(){
    Menu menu;
    menu.qtd = 0;

    while(1){
        fflush(stdin);
        char op = opcoes();
        if(op == '0'){
            break;
        }
        switch(op){
            case '1':
                cadastrar(&menu);
                system("pause");
                break;
            case '2':
                imprimir(&menu);
                system("pause");
                break;
            case '3':
                excluir(&menu);
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
    printf("2 - LISTAR\n");
    printf("3 - EXCLUIR\n");
    printf("0 - SAIR\n");
    printf(">> ");
    scanf("%c", &op);
    return op;
}

void cadastrar(Menu *menu){
    char descricao[100];
    float preco;
    int qtd;
    system("cls");
    fflush(stdin);
    printf("========== CADASTRAR ==========\n\n");
    printf("DESCRICAO: ");
    gets(descricao);
    printf("PRECO: ");
    scanf("%f", &preco);
    printf("QTD: ");
    scanf("%d", &qtd);

    int codigo;
    if(menu->qtd == 0){
        codigo = 1;
    }else{
        codigo = menu->produtos[menu->qtd - 1].codigo + 1;
    }

    menu->produtos[menu->qtd].codigo = codigo;
    strcpy(menu->produtos[menu->qtd].descricao, descricao);
    menu->produtos[menu->qtd].preco = preco;
    menu->produtos[menu->qtd].qtd = qtd;
    menu->qtd++;

    printf("\nProduto cadastrado com sucesso!\n");
}//Fim do cadastrar

void imprimir(Menu *menu){
    system("cls");
    printf("========== MENU ==========\n\n");
    printf("------------------------------------");
    int i;
    for(i=0 ; i<menu->qtd ; i++){
        printf("\nCODIGO: %d", menu->produtos[i].codigo);
        printf("\nDESCRICAO: ");
        puts(menu->produtos[i].descricao);
        printf("PRECO: R$ %.2f", menu->produtos[i].preco);
        printf("\nQTD: %d", menu->produtos[i].qtd);
        printf("\n------------------------------------");
    }
    printf("\n");
}//fim do Imprimir

void excluir(Menu *menu){
    system("cls");
    printf("========== EXCLUIR ==========\n\n");
    imprimir(menu);
    int c;
    printf("Qual produto deseja excluir?: ");
    scanf("%d", &c);
    int certeza = 0;
    printf("Tem certeza que deseja excluir o produto %d? (1 - SIM; 0 - NAO):", c);
    scanf("%d", &certeza);
    if(certeza == 1){
        int i,j, encontrado = 0;
        for(i = 0; i < menu->qtd; i++){
            if(menu->produtos[i].codigo == c){
                for(j = i; j < menu->qtd - 1; j++){
                    menu->produtos[j] = menu->produtos[j + 1];
                }
                menu->qtd--;
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