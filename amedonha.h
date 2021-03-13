typedef struct _jogador {
    char *nome;
    int pontos_total;
    float tempo_total;
    int pontos_parcial;
    float tempo_parcial;
    char *resposta;
    float tempo_max;
} jogador;

int input_N();

jogador* nomes(int N);

char sorteia_letra(char letra_anterior);

int* ordem(int N);

int contar_elementos(char elemento[100], jogador *vetor, int N);

void deixar_maiusculo(char *frase);

int index_espaco(char* string);

void get_resposta(jogador *jogador, char letra_sorteada, char categoria[18]);

void calcular_pontuacao(jogador *jogadores, int N);

int vencedor(jogador *jogadores, int N);

int placar(jogador *jogadores, int N, int rodada, char categorias[5][18], int *ordem_categorias, int *rodada_1, int *rodada_2, int *rodada_3, int *rodada_4);