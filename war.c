#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Tamanho padrao de string sera definido aqui
#define tamStringPadrao 20
#define limitetorr 10
int totalPaises = 0;
int gameover = 0;

struct paises{
    char *nome;
    char *cor;
    int soldados;
    int missao;
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

void menu(int *opcao);
void sistema(int opcaoSistema);
void cadastrar();
void visualizar();
void atacar(); 
void missao();
void verificamissao();

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    int opcaoSistema;
    terra = (struct paises*) calloc(100, sizeof(struct paises));
    do {
        menu(&opcaoSistema);
        sistema(opcaoSistema);
    } while (opcaoSistema != 4 && gameover == 0);

    return 0;
}

//Menu - Decide o que ira fazer
void menu(int *opcao) {
    printf("\n=== MENU ===\n");
    printf("Programa Rodando!\n");
    printf("1 para cadastrar:\n");
    printf("2 para visualizar:\n");
    printf("3 para fazer um ataque:\n");
    printf("4 para fechar o programa:\n");

    printf("\nEscolha:");
    scanf("%d", opcao);
    limpar();
}
//Somente executa o que o usuario escolhei no menu
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

        case 4:
            printf("\n------------------\n");
            printf("Fechando programa!!");
            printf("\n------------------\n");

        default:
            printf("\n------------------\n");
            printf("Opcao invalida!!\n");
            printf("\n------------------\n");
            break;
    }
}
//Cadastra um territorio
void cadastrar() {
    if (totalPaises != 0) {
        printf("Voce ja cadastrou os territorio, nao podera cadastrar novos territorio, feche o programa e abra novamente!!");
        return;
    }
    int numcadastrar;
    printf("Digite a quantidade de territorios a serem cadastrados: ");
    scanf("%d", &numcadastrar);
    limpar();
    if(numcadastrar < 2) {
        printf("Voce nao pode cadastrar menos do que 2 territorios!!");
        return;
    }
    if (numcadastrar > limitetorr) {
        printf("Voce passou do limite de territorios cadastre novamente!!! (Limite: %d)\n", limitetorr);
        return;
    } else {
        for (int i = 0; i < numcadastrar; i++) {
            terra[totalPaises].nome = malloc(tamStringPadrao);
            terra[totalPaises].cor  = malloc(tamStringPadrao);

            printf("\n-----------------------\n");
            printf("ADICIONANDO UM TERRITORIO\n");
            printf("Digite o nome do territorio: ");
            fgets(terra[totalPaises].nome, tamStringPadrao, stdin);
            removeEnter(terra[totalPaises].nome);
            printf("Digite a cor do territorio: ");
            fgets(terra[totalPaises].cor, tamStringPadrao, stdin);
            removeEnter(terra[totalPaises].cor);
            printf("Digite o número de soldados: ");
            scanf("%d", &terra[totalPaises].soldados);
            limpar();

            printf("Territorio cadastrado!\n");
            totalPaises++;
        }
        missao();
    }
}
//Visualizar todos territorio e dados
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
//Ataque de territorios
void atacar() {
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
        
        //verifica se as missao foram compridas
        verificamissao();
    }
}
// Missao - Conquistar territo
void missao() {
    printf("\n---- MISSOES ----\n");

    for (int i = 0; i < totalPaises; i++) {
        int missao;
        do {
            missao = rand() % totalPaises;
        } while (missao == i);
        terra[i].missao = missao;
        printf("O território %d - %s terá que conquistar o território %d - %s.\n", i, terra[i].nome, missao, terra[missao].nome);
    }
}
//Verifica se missao foi concluida, na funcao de ataque
void verificamissao() {
    for (int i = 0; i < totalPaises; i++) {
        int alvo = terra[i].missao;
        if (strcmp(terra[i].nome, terra[alvo].nome) == 0) {
            printf("\n-----------------------------------------------");
            printf("\n-%s concluiu sua missão e VENCEU O GAME!!-\n", terra[i].nome);
            printf("|--- GAME OVER ---|");
            printf("\n-----------------------------------------------\n");
            gameover = 1;
            break;
        }
    }
}