#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    float preco;
} ItemMenu;


typedef struct {
    ItemMenu itens[20];
    int quantidade[20];
    int totalItens;
} Pedido;

int gerarProximoID(): //Savio
void cadastrarItem(); //Savio
void consultarItens(); //Savio
void atualizarItem(); //Savio
void excluirItem(); //Savio
void fazerPedido(Pedido *pedido); //Davi
void adicionarPedido(Pedido *pedido); //Davi
void exibirResumoPedido(Pedido *pedido); //Davi
void salvarPedido(Pedido *pedido); //Davi
void menuFuncionario(); //Savio
void menuCliente(); //Davi

void main() {
    int opcao;
    do {
        system("cls");
        printf("\n--- Sistema de Restaurante ---\n\n");
        printf("1. Funcionario\n");
        printf("2. Cliente\n");
        printf("3. Sair\n");
        printf(">> ");
        fflush(stdin);
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuFuncionario();
                break;
            case 2:
                menuCliente();
                break;
            case 3:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n\n");
                system("pause");
        }
    } while (opcao != 3);

}// fim do main

void menuFuncionario() {
    int opcao;
    do {
    	system("cls");
        printf("\n--- Menu Funcionario ---\n\n");
        printf("1. Cadastrar Item no Menu\n");
        printf("2. Consultar Itens do Menu\n");
        printf("3. Atualizar Item do Menu\n");
        printf("4. Excluir Item do Menu\n");
        printf("5. Voltar ao Menu Principal\n");
        printf(">> ");
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                cadastrarItem();
                break;
            case 2:
                system("cls");
                consultarItens();
                system("pause");
                break;
            case 3:
                system("cls");
                atualizarItem();
                break;
            case 4:
                system("cls");
                excluirItem();
                break;
            case 5:
                printf("\nVoltando ao menu principal...\n");
                break;
            default:
                printf("\nOpcao invalida!\n\n");
                system("pause");
        }
    } while (opcao != 5);
}// fim do menu do Funcionario


void menuCliente() {
    Pedido pedido = {.totalItens = 0};
    int opcao;
    do {
    	system("cls");
        printf("\n--- Menu Cliente ---\n\n");
        printf("1. Fazer Pedido\n");
        printf("2. Voltar ao Menu Principal\n");
        printf(">> ");
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                fazerPedido(&pedido);
                break;
            case 2:
                printf("\nVoltando ao menu principal...\n");
                break;
            default:
                printf("\nOpcao invalida!\n\n");
                system("pause");
        }
    } while (opcao != 2);
}// fim do menu do cliente


int gerarProximoID() {
    FILE *arquivo = fopen("menu.txt", "r");
    if (arquivo == NULL) {
        return 1;
    }

    ItemMenu item;
    int ultimoID = 0;

    while (fscanf(arquivo, "%d %s %f", &item.id, &item.nome, &item.preco) != EOF) {
        ultimoID = item.id;
    }

    fclose(arquivo);
    return ultimoID + 1;
}// fim do gerarProximoID

void cadastrarItem() {
    FILE *arquivo = fopen("menu.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n\n");
        system("pause");
        return;
    }

    ItemMenu item;
    item.id = gerarProximoID();
    printf("Digite o nome do item: ");
    fflush(stdin);
    scanf("%s", &item.nome);
    printf("Digite o preço do item: ");
    fflush(stdin);
    scanf("%f", &item.preco);

    fprintf(arquivo, "%d %s %.2f\n", item.id, item.nome, item.preco);
    fclose(arquivo);

    printf("Item cadastrado com sucesso! ID gerado: %d\n\n", item.id);
    system("pause");
}// fim do cadastrarItem

void consultarItens() {
    FILE *arquivo = fopen("menu.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum item encontrado!\n\n");
        system("pause");
        return;
    }

    ItemMenu item;
    printf("\n--- Itens do Menu ---\n");
    while (fscanf(arquivo, "%d %s %f", &item.id, item.nome, &item.preco) != EOF) {
        printf("ID: %d | Nome: %s | Preço: %.2f\n", item.id, item.nome, item.preco);
    }
    fclose(arquivo);
}// fim do consultarItens

void atualizarItem() {
    FILE *arquivo = fopen("menu.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n\n");
        system("pause");
        return;
    }

    ItemMenu itens[100];
    int totalItens = 0;
    while (fscanf(arquivo, "%d %s %f", &itens[totalItens].id, itens[totalItens].nome, &itens[totalItens].preco) != EOF) {
        totalItens++;
    }
    fclose(arquivo);

    int id;
    consultarItens();
    printf("\nDigite o ID do item que deseja atualizar: ");
    fflush(stdin);
    scanf("%d", &id);

    int encontrado = 0;
    int i;
    for (i = 0; i < totalItens; i++) {
        if (itens[i].id == id) {
            encontrado = 1;
            printf("Item encontrado: %s | Preço: %.2f\n", itens[i].nome, itens[i].preco);

            printf("\nDigite o novo nome do item: ");
            fflush(stdin);
            scanf("%s", itens[i].nome);
            printf("Digite o novo preço do item: ");
            fflush(stdin);
            scanf("%f", &itens[i].preco);

            break;
        }
    }

    if (!encontrado) {
        printf("Item com ID %d não encontrado!\n\n", id);
        system("pause");
        return;
    }

    arquivo = fopen("menu.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n\n");
        system("pause");
        return;
    }

    for (i = 0; i < totalItens; i++) {
        fprintf(arquivo, "%d %s %.2f\n", itens[i].id, itens[i].nome, itens[i].preco);
    }
    fclose(arquivo);

    printf("Item atualizado com sucesso!\n\n");
    system("pause");
} // fim do atualizarItem

void excluirItem() {
    FILE *arquivo = fopen("menu.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n\n");
        system("pause");
        return;
    }

    ItemMenu itens[100];
    int totalItens = 0;
    while (fscanf(arquivo, "%d %s %f", &itens[totalItens].id, itens[totalItens].nome, &itens[totalItens].preco) != EOF) {
        totalItens++;
    }
    fclose(arquivo);

    int id;
    consultarItens();
    printf("\nDigite o ID do item que deseja excluir: ");
    fflush(stdin);
    scanf("%d", &id);

    int encontrado = 0;
    int i,j;
    for (i = 0; i < totalItens; i++) {
        if (itens[i].id == id) {
            encontrado = 1;
            printf("Item excluído: %s | Preço: %.2f\n", itens[i].nome, itens[i].preco);
            for (j = i; j < totalItens - 1; j++) {
                itens[j] = itens[j + 1];
            }
            totalItens--;
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado!\n\n");
        system("pause");
        return;
    }

    arquivo = fopen("menu.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        system("pause");
        return;
    }

    for (i = 0; i < totalItens; i++) {
        fprintf(arquivo, "%d %s %.2f\n", itens[i].id, itens[i].nome, itens[i].preco);
    }
    fclose(arquivo);

    printf("Item excluído com sucesso!\n");
    system("pause");
}// fim do excluirItem


void fazerPedido(Pedido *pedido) {
    FILE *p = fopen("menu.txt", "r");
    if(p == NULL){
        printf("O menu esta vazio, volte mais tarde...\n\n");
        system("pause");
    }else{
        int opcao;
        do {
            system("cls");
            consultarItens();
            exibirResumoPedido(pedido);
            adicionarPedido(pedido);

            printf("\nDeseja adicionar mais itens?\n");
            printf("1. Sim\n2. Finalizar Pedido\n");
            scanf("%d", &opcao);


        } while (opcao != 2);

    salvarPedido(pedido);
    system("cls");
    }

}// fim do fazerPedido

void adicionarPedido(Pedido *pedido) {

    if (pedido->totalItens >= 20) {
        printf("Pedido já contem o numero máximo de itens!\n");
        return;
    }

    int id;
    printf("Digite o ID do item que deseja adicionar ao pedido: ");
    scanf("%d", &id);

    FILE *arquivo = fopen("menu.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        system("pause");
        return;
    }

    ItemMenu item;
    int encontrado = 0;
    while (fscanf(arquivo, "%d %s %f", &item.id, item.nome, &item.preco) != EOF) {
        if (item.id == id) {
            printf("Digite a quantidade: ");
            int quantidade;
            scanf("%d", &quantidade);

            pedido->itens[pedido->totalItens] = item;
            pedido->quantidade[pedido->totalItens] = quantidade;
            pedido->totalItens++;
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Item com ID %d nao encontrado!\n", id);
    } else {
        printf("Item adicionado ao pedido!\n");
    }
}// fim do adicionarPedido

void exibirResumoPedido(Pedido *pedido) {
    if (pedido->totalItens == 0) {
        printf("Nenhum item no pedido!\n");
        return;
    }

    float total = 0;
    printf("\n--- Resumo do Pedido ---\n");
    int i;
    for (i = 0; i < pedido->totalItens; i++) {
        printf("Item: %s | Quantidade: %d | Preco: %.2f\n",
               pedido->itens[i].nome,
               pedido->quantidade[i],
               pedido->itens[i].preco * pedido->quantidade[i]);
        total += pedido->itens[i].preco * pedido->quantidade[i];
    }
    printf("Total do Pedido: %.2f\n", total);
}// fim do exibirResumoPedido

void salvarPedido(Pedido *pedido) {
    if (pedido->totalItens == 0) {
        printf("Nenhum item no pedido para salvar!\n");
        system("pause");
        return;
    }

    FILE *arquivo = fopen("pedidos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pedidos!\n");
        system("pause");
        return;
    }

    fprintf(arquivo, "\n--- Novo Pedido ---\n");
    int i;
    for (i = 0; i < pedido->totalItens; i++) {
        fprintf(arquivo, "Item: %s | Quantidade: %d | Preco: %.2f\n",
                pedido->itens[i].nome,
                pedido->quantidade[i],
                pedido->itens[i].preco * pedido->quantidade[i]);
    }

    float total = 0;
    for (i = 0; i < pedido->totalItens; i++) {
        total += pedido->itens[i].preco * pedido->quantidade[i];
    }
    fprintf(arquivo, "Total do Pedido: %.2f\n", total);

    fclose(arquivo);
    printf("Pedido salvo com sucesso!\n");
    system("pause");


}// fim do salvarPedido
