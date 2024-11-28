#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define ARQUIVO "adocoes.txt"
#define TAM_MAX 100 

typedef struct {
    char nome[50];
    int idade;
    char endereco[100];
} Usuario;

typedef struct {
    char raca[30];
} Cachorro;


typedef struct {
    Usuario usuario;
    Cachorro cachorro;
} Historico;


typedef struct {
    Historico historico[TAM_MAX];
    int topo;
} Pilha;


void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->topo == TAM_MAX - 1;
}

void empilhar(Pilha *pilha, Historico registro) {
    if (pilhaCheia(pilha)) {
        printf("A pilha de ado��es est� cheia.\n");
        return;
    }
    pilha->historico[++(pilha->topo)] = registro;
}

Historico desempilhar(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("A pilha de ado��es est� vazia.\n");
        Historico vazio = {{"", 0, ""}, {""}};
        return vazio;
    }
    return pilha->historico[(pilha->topo)--];
}

void listarRacas() {
    printf("Ra�as dispon�veis para ado��o:\n");
    printf("1. Labrador\n");
    printf("2. Poodle\n");
    printf("3. Bulldog\n");
    printf("4. Golden Retriever\n");
    printf("5. Pastor Alem�o\n");
    printf("6. Vira Lata\n");
    printf("7. Husky Siberiano\n");
}

void cadastrarUsuario(Usuario *usuario) {
    printf("Digite seu nome: \n");
    scanf(" %[^\n]", usuario->nome);
    printf("Digite sua idade: \n");
    scanf("%d", &usuario->idade);
    printf("Digite seu endere�o:\n");
    scanf(" %[^\n]", usuario->endereco);

    printf("Cadastro realizado com sucesso!\n");
}

void adotarCachorro(Usuario usuario, Pilha *historicoPilha) {
    Cachorro cachorro;
    int opcao;

    listarRacas();
    printf("Escolha uma ra�a para adotar: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            strcpy(cachorro.raca, "Labrador");
            break;
        case 2:
            strcpy(cachorro.raca, "Poodle");
            break;
        case 3:
            strcpy(cachorro.raca, "Bulldog");
            break;
        case 4:
            strcpy(cachorro.raca, "Golden Retriever");
            break;
        case 5:
            strcpy(cachorro.raca, "Pastor Alem�o");
            break;
        case 6:
            strcpy(cachorro.raca, "Vira Lata");
            break;
        case 7:
            strcpy(cachorro.raca, "Husky Siberiano");
            break;
        default:
            printf("Op��o inv�lida!\n");
            return;
    }

    FILE *arquivo = fopen(ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "Nome: %s\nIdade: %d\nEndere�o: %s\nRa�a do Cachorro: %s\n\n",
            usuario.nome, usuario.idade, usuario.endereco, cachorro.raca);
    fclose(arquivo);


    Historico registro;
    registro.usuario = usuario;
    registro.cachorro = cachorro;
    empilhar(historicoPilha, registro);

    printf("Parab�ns, voc� adotou um %s!\n", cachorro.raca);
}

void desfazerAdocao(Pilha *historicoPilha) {
    if (pilhaVazia(historicoPilha)) {
        printf("N�o h� ado��es para desfazer.\n");
        return;
    }

    Historico ultimo = desempilhar(historicoPilha);
    printf("Ado��o desfeita com sucesso!\n");
    printf("Usu�rio: %s\nCachorro: %s\n", ultimo.usuario.nome, ultimo.cachorro.raca);
}

void listarAdocoes() {
    char linha[200];
    FILE *arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        printf("Nenhuma ado��o registrada.\n");
        return;
    }

    printf("Ado��es Registradas:\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }
    fclose(arquivo);
}

int main() {
    setlocale(LC_ALL, "portuguese");
    Usuario usuario;
    Pilha historicoPilha;
    inicializarPilha(&historicoPilha);

    int opcao;
    int cadastroFeito = 0;

    printf("Ol�, tudo bem? Vamos adotar um doguinho!\n");

    do {
        printf("\n============== Menu ==============\n");
        printf("1. Listar Ra�as para Ado��o\n");
        printf("2. Cadastrar Usu�rio\n");
        printf("3. Adotar um Cachorro\n");
        printf("4. Listar Ado��es\n");
        printf("5. Desfazer �ltima Ado��o\n");
        printf("6. Sair\n");
        printf("=================================\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarRacas();
                break;
            case 2:
                cadastrarUsuario(&usuario);
                cadastroFeito = 1;
                break;
            case 3:
                if (cadastroFeito) {
                    adotarCachorro(usuario, &historicoPilha);
                } else {
                    printf("� necess�rio cadastrar um usu�rio antes de adotar.\n");
                }
                break;
            case 4:
                listarAdocoes();
                break;
            case 5:
                desfazerAdocao(&historicoPilha);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}

