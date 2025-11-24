#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tamanho padrao de string sera definido aqui
#define tamStringPadrao 15
int totalPaises = 0;
int opcaoSistema;

struct paises{
    char nome[tamStringPadrao];
    char cor[tamStringPadrao];
    int soldados;
};

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limpar(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // limpa buffer
}

struct paises terra[10];

void sistema(int opcaoSistema) {

    switch (opcaoSistema) {

        case 1:
            if (totalPaises >= 10) {
                printf("Limite de países atingido!\n");
                break;
            }

            //pergunta quantos quer cadastrar

            // if para verificar se vai passar do limite
            //que é o cadastrados + seraocadastrados tem que ser menor do que limite

            //caso for menor vai para o for 

            //caso for maior, ira passar o limite e break

            printf("\n-----------------------\n");
            printf("ADICIONANDO UM PAIS\n");

            printf("Digite o nome do país: ");
            fgets(terra[totalPaises].nome, tamStringPadrao, stdin);

            printf("Digite a cor do país: ");
            fgets(terra[totalPaises].cor, tamStringPadrao, stdin);

            printf("Digite o número de soldados: ");
            scanf("%d", &terra[totalPaises].soldados);
            limpar();

            printf("País cadastrado!\n");
            totalPaises++;
            break;

        case 2:
            if (totalPaises == 0) {
                printf("\n-----------------------\n");
                printf("Nenhum país cadastrado!");
                printf("\n-----------------------\n");
                break;
            }

            printf("\n---- PAÍSES ---\n");
            for (int i = 0; i < totalPaises; i++) {
                printf("País %d:\n", i + 1);
                printf("Nome: %s", terra[i].nome);
                printf("Cor: %s", terra[i].cor);
                printf("Soldados: %d\n", terra[i].soldados);
                printf("-------------------------\n");
            }
            break;


        default:
            printf("Opção inválida.\n");
            printf("Fechando programa!!");
            break;
    }
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    do {
        printf("\n=== MENU ===\n");
        printf("Programa Rodando!\n");
        printf("1 para cadastrar:\n");
        printf("2 para visualizar:\n");
        printf("3 para enserar programa:\n");

        printf("\nEscolha:");
        scanf("%d", &opcaoSistema);
        limpar();

        sistema(opcaoSistema);
    } while (opcaoSistema != 3);

    return 0;
}

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// 1. Configuração Inicial (Setup):
// - Define o locale para português.
// - Inicializa a semente para geração de números aleatórios com base no tempo atual.
// - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
// - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
// - Define a cor do jogador e sorteia sua missão secreta.

// 2. Laço Principal do Jogo (Game Loop):
// - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
// - A cada iteração, exibe o mapa, a missão e o menu de ações.
// - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
//   - Opção 1: Inicia a fase de ataque.
//   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
//   - Opção 0: Encerra o jogo.
// - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

// 3. Limpeza:
// - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ==========

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.