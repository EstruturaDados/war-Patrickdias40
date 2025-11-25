#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Tamanho padrao de string sera definido aqui
#define tamStringPadrao 20
int totalPaises = 0;
int opcaoSistema;

struct paises{
    char *nome;
    char *cor;
    int soldados;
};


struct paises *terra;

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limpar(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // limpa buffer
}

void removeEnter(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void cadastrar() {
    if (totalPaises >= 10) {
        printf("Limite de países atingido!\n");
    } else {
        //pergunta quantos quer cadastrar

        // if para verificar se vai passar do limite
        //que é o cadastrados + seraocadastrados tem que ser menor do que limite

        //caso for menor vai para o for 

        //caso for maior, ira passar o limite e break

        printf("\n-----------------------\n");
        printf("ADICIONANDO UM PAIS\n");

        terra[totalPaises].nome = malloc(tamStringPadrao);
        terra[totalPaises].cor  = malloc(tamStringPadrao);

        printf("Digite o nome do país: ");
        fgets(terra[totalPaises].nome, tamStringPadrao, stdin);
        removeEnter(terra[totalPaises].nome);
        printf("Digite a cor do país: ");
        fgets(terra[totalPaises].cor, tamStringPadrao, stdin);
        removeEnter(terra[totalPaises].cor);
        printf("Digite o número de soldados: ");
        scanf("%d", &terra[totalPaises].soldados);
        limpar();

        printf("País cadastrado!\n");
        totalPaises++;
    }
}

void visualizar() {
    if (totalPaises <= 0) {
        printf("\n-----------------------\n");
        printf("Nenhum país cadastrado!");
        printf("\n-----------------------\n");
    } else {
        printf("\n---- PAÍSES ----\n");
        for (int i = 0; i < totalPaises; i++) {
            printf("--- País %d ---\n", i + 1);
            printf("Nome: %s\n", terra[i].nome);
            printf("Cor: %s\n", terra[i].cor);
            printf("Soldados: %d\n", terra[i].soldados);
            printf("-------------------------\n");
        }
    }
}

void atacar(){
    int atacante;
    int defensor;
    if (totalPaises <= 0) {
        printf("\n-----------------------\n");
        printf("Nenhum país cadastrado!");
        printf("\n-----------------------\n");
    } else {
        printf("\nTodos os paises(RELEMBRAR):");
        for  (int i = 0; i < totalPaises; i++) {
            printf("\n%d - %s", i + 1, terra[i].nome);
        }
        //Escolhe quem ataca e quem defende
        printf("\n Digite o numero do pais quem ira atacar: ");
        scanf("%d", &atacante);
        limpar();
        printf("\n Digite quem ira defender: ");
        scanf("%d", &defensor);
        limpar();

        printf("DEBUG: [%s]\n", terra[atacante].nome);

        // ajustar índice do array
        atacante -= 1;
        defensor -= 1;

        // sorteando um numero aleatorio ate a quantia de soldados que cada pais possui
        printf("\n--- STATUS ATAQUE ---\n");
        int ataque = rand() % (terra[atacante].soldados + 1);
        printf("\n%s esta atacando com %d soldados", terra[atacante].nome, ataque);
        int defesa = rand() % (terra[defensor].soldados + 1);
        printf("\n%s esta defendendo com %d soldados \n", terra[defensor].nome, defesa);

        int diferenca = (ataque > defesa) ? (ataque - defesa) : (defesa - ataque);

        if(ataque >= defesa) {
            if (diferenca < defesa) {
                terra[defensor].soldados -= diferenca;
            } else {
                terra[defensor].nome = terra[atacante].nome;
                terra[defensor].cor = terra[atacante].cor;
                terra[defensor].soldados = (ataque - diferenca) / 2;
            }
        } else {
            terra[atacante].soldados -= diferenca;
            printf("\n%s Defendou com sucesso de %s", terra[defensor].nome, terra[atacante].nome);
        }
        visualizar();
    }
}

void sistema(int opcaoSistema) {

    switch (opcaoSistema) {
        //Cadastro
        case 1:
            cadastrar();
            break;

        //Visualizar mapas
        case 2:
            visualizar();
            break;

        case 3:
            atacar();
            break;

        default:
            printf("Fechando programa!!");
            break;
    }
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    terra = (struct paises*) calloc(100, sizeof(struct paises));
    do {
        printf("\n=== MENU ===\n");
        printf("Programa Rodando!\n");
        printf("1 para cadastrar:\n");
        printf("2 para visualizar:\n");
        printf("3 para fazer um ataque:\n");
        printf("4 para fechar o programa:\n");

        printf("\nEscolha:");
        scanf("%d", &opcaoSistema);
        limpar();

        sistema(opcaoSistema);
    } while (opcaoSistema != 4);

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