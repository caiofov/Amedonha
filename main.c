#include <stdio.h>
#include <stdlib.h>
#include "amedonha.h"


int main()
{
    jogador *jogadores;
    int N; /*Quantidade de jogadores inserida pelo usuário*/
    int i;
    char letra;
    char categorias[5][18] = {"Nomes de Pessoas", "Nomes de Cidade", "Nomes de Animais", "Nomes de Comida", "Profissões"};
    int *ordem_categorias, *ordem_jogadores;
    int *rodada_1, *rodada_2, *rodada_3, *rodada_4;
    int rodada;
    int tempo_max;
    int continuar;

    N = input_N();

    rodada_1 = malloc(N * sizeof(int));
    rodada_2 = malloc(N * sizeof(int));
    rodada_3 = malloc(N * sizeof(int));
    rodada_4 = malloc(N * sizeof(int));

    jogadores = nomes(N); /*criando o vetor de jogadores*/

    printf("Os jogadores da partida são:\n");
    for (i = 0; i< N; i++) {
        printf("\t%s\n", jogadores[i].nome);
    }
    
    ordem_categorias = ordem(5); /*São sempre 5 categorias*/
    
    rodada = 0;
    while (rodada < 5) {
        letra = sorteia_letra(letra);
        ordem_jogadores = ordem(N);
        printf("A categoria da vez é: %s\n", categorias[(ordem_categorias[rodada])]);
        printf("A letra da rodada é: %c\n", letra);

        tempo_max = 8 + (2 * N); 
        printf("A ordem desta rodada será:\n");
        for (i = 0; i < N; i++) {
            printf("\t%s\n", jogadores[(ordem_jogadores[i])].nome);
            jogadores[ordem_jogadores[i]].tempo_max = tempo_max;
            free(jogadores[ordem_jogadores[i]].resposta);
            tempo_max -= 2;
        }

        printf("Insira 1 para iniciar a rodada:\n");
        scanf("%d", &continuar);
        getchar();
        if (continuar) {
            printf("Vamos lá!\n");
        }

        /*       *INPUT DAS RESPOSTAS - - -*/

        /*Neste loop, teremos como base o vetor "ordem_jogadores". O índice será incrementado, obtendo o número do jogador que dará a reposta.*/
        for(i = 0; i < N; i++){
            system("clear"); /*limpar a tela para a resposta anterior não ser visualizada*/
            /*transformar estas palavras em maiúsculo para facilitar a visualização*/
            deixar_maiusculo(jogadores[(ordem_jogadores[i])].nome);
        
            printf("\n >> É a vez de %s! << \nInsira uma palavra da categoria ||%s|| que inicie com a letra ||%c||: \n", jogadores[(ordem_jogadores[i])].nome , categorias[ordem_categorias[rodada]], letra);

            /*receber e validar a resposta do usuário*/
            get_resposta(&jogadores[(ordem_jogadores[i])], letra, categorias[ordem_categorias[rodada]]);
        }

        /*No final de cada rodada, serão calculadas as pontuações de cada jogador*/
        calcular_pontuacao(jogadores, N);

        for (i = 0; i < N; i++) {
            printf("A resposta do jogador(a): %s, foi: %s\n", jogadores[i].nome, jogadores[i].resposta);
        }

        placar(jogadores, N, rodada, categorias, ordem_categorias, rodada_1, rodada_2, rodada_3, rodada_4);
        free(ordem_jogadores);
        rodada++;
    }

    vencedor(jogadores, N);

    free(rodada_1);
    free(rodada_2);
    free(rodada_3);
    free(rodada_4);
    free(ordem_categorias);
    free(ordem_jogadores);
    for (i = 0; i < N; i++) {
        free(jogadores[i].nome);
        free(jogadores[i].resposta);
    }
    free(jogadores);


}