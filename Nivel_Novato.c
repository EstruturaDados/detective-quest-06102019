#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura da sala (nó da árvore binária)
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Função que cria uma nova sala dinamicamente
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Função que permite o jogador explorar as salas
void explorarSalas(Sala* salaAtual) {
    char opcao;

    while (1) {
        printf("\nVocê está em: %s\n", salaAtual->nome);

        // Se a sala não tiver caminhos, o jogo termina
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Você chegou a um cômodo sem saídas. Fim da exploração!\n");
            break;
        }

        // Mostra as opções de navegação disponíveis
        printf("Para onde deseja ir?\n");
        if (salaAtual->esquerda != NULL) printf("(e) Esquerda: %s\n", salaAtual->esquerda->nome);
        if (salaAtual->direita != NULL) printf("(d) Direita: %s\n", salaAtual->direita->nome);
        printf("(s) Sair do jogo\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        // Controle da navegação
        if (opcao == 'e' && salaAtual->esquerda != NULL) {
            salaAtual = salaAtual->esquerda;
        } else if (opcao == 'd' && salaAtual->direita != NULL) {
            salaAtual = salaAtual->direita;
        } else if (opcao == 's') {
            printf("Exploração encerrada pelo jogador.\n");
            break;
        } else {
            printf("Caminho inválido! Escolha novamente.\n");
        }
    }
}

// Função principal: cria a árvore (mapa da mansão)
int main() {
    // Habilita caracteres acentuados de acordo com o sistema
    setlocale(LC_ALL, "");
    // Criação das salas
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");
    Sala* porao = criarSala("Porão");

    // Conectando os cômodos (estrutura da mansão)
    hallEntrada->esquerda = salaEstar;
    hallEntrada->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = porao;

    printf("Bem-vindo ao jogo Detective Quest!\n");
    printf("Explore a mansão e descubra seus mistérios...\n");

    // Inicia a exploração
    explorarSalas(hallEntrada);

    // Libera a memória (boas práticas)
    free(hallEntrada);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);
    free(jardim);
    free(porao);

    printf("\nJogo finalizado com sucesso.\n");
    return 0;
}
