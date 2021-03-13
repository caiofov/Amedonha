#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define MAXRESPOSTA 30 /*Tamanho máximo para uma resposta*/
#define MINJOGADORES 2 /*Quantidade mínima de jogadores em uma partida*/
#define MAXJOGADORES 10 /*Quantidade máxima de jogadores em uma partida*/
#define MAXNOME 12 /*Tamanho máximo do nome de um jogador*/

typedef struct _jogador {
    char *nome;
    int pontos_total;
    float tempo_total;
    int pontos_parcial;
    float tempo_parcial;
    char *resposta;
    float tempo_max;
} jogador;

int input_N() 
{
    int N;

    printf("Quantos jogadores participarão dessa partida (podem haver de 2 a 10 participantes):\n"); /*Solicita a quantidade de participantes na partida*/
    scanf("%d", &N); /*Lê o valor inserido pelo usuário*/
    
    while (N < MINJOGADORES || N > MAXJOGADORES) { /*Checa se a quantidade de jogadores inserida pelo usuário está dentro do limite estabelecido*/
        printf("****Deve haver pelo menos 2 e no máximo 10 participantes!****\n");
        printf("Quantos jogadores participarão dessa partida (podem haver de 2 a 10 participantes):\n"); /*Solicita a quantidade de participantes na partida*/
        scanf("%d", &N); /*Lê o valor inserido pelo usuário*/
    }
    return N;
}

jogador* nomes(int N)
{
    jogador *jogadores; /*Declara um ponteiro para uma variável do tipo jogador */
    char nome[30];
    
    int i = 0; /*Variável para controle de loop*/
    

    /*A inicialização da variável depois que sabemos o valor de N, permite a alocação de memória
    para a quantidade exata de jogadores que irão participar*/
    jogadores = malloc(N * sizeof(jogador)); /*Faz com com que a variável jogadores seja capaz de armazenas um vetor com N jogadores*/

    while (i < N) { /*Irá excecutar uma vez para cada jogador a ser cadastrado*/
        printf("Insira o nome do jogador %d\n", i + 1); /*Jogador (i+1): Jogador 1, Jogador 2, Jogador 3...*/
        scanf("%s", nome);
        while (strlen(nome) > MAXNOME) { /*Garante que o usuário só irá progredir se colocar um nome do tamanho aceito pelo programa*/
            printf("\nO nome deve ter no máximo 12 caracteres, por favor insira novamente:\n");
            scanf("%s", nome);
        }

        /*Faz com com que o parâmetro nome (ponteiro para char) do i-ésimo jogador,
        ocupe apenas o espaço necessário para comportar o nome do jogador*/
        
        jogadores[i].nome = malloc(strlen(nome) * sizeof(char));
        
        /*A variável 'nome' é sobrescrita a cada iteração com o próximo nome inserido, por isso, é prudente realizar uma cópia
        do atual valor da variável 'nome' para a cadeia de caracteres na posição 'i' do vetor, pois, se a associação, for diretamente
        com o ponteiro da variável nome, todos os jogadores acabarão com o mesmo nome*/
        
        strcpy(jogadores[i].nome, nome);
        
        i++;
    }
    return jogadores;
}

char sorteia_letra(char letra_anterior)
{
    char MIN, MAX, letra;
    srand(time(NULL)); /*Inicializa uma seed aleatória para que a função rand() possa sortear números diferentes */
    MIN ='A'; 
    MAX = 'Z'; 
    letra = rand() % (MAX + 1 - MIN) + MIN; 
    /* Sorteia novamente se por acaso uma das letras que não deve aparecer seja sorteada, ou se a letra sorteada
    for igual a letra sorteada anteriormente*/
    while (letra == 75 || letra == 87 || letra == 89 || letra == letra_anterior) { 
        letra = rand() % (MAX + 1 - MIN) + MIN;
    }
    return letra;
}

int* ordem(int N)
{
    int *vetor, i, temp, num;

    vetor = malloc(N * sizeof(int));
    
    for (i = 0; i < N; i++) { /*Preenche um vetor com N inteiros entre 1 e N, em ordem*/
        vetor[i] = i;
    }
    srand(time(NULL));
    for (i = 0; i < N; i++) { /*Embaralha o vetor de forma aleatória*/
        temp = vetor[i];
        num  = (rand() % (N - 1)) + 1;
        vetor[i] = vetor[num]; 
        vetor[num] = temp;
    }
    return vetor;
}

/*função de apoio que conta os elementos resposta no array de jogadores*/
int contar_elementos(char elemento[100], jogador *vetor, int N) 
{
    /*algumas variaveis...*/
    int i; /*para o loop*/
    int comparar; /*guarda o retorno da funcao strcmp da biblioteca string*/
    int count; /*armazena a quantidade de strings iguais encontrada*/
    i=0;
    count=0;

    while(i < N) {
        comparar = strcmp(vetor[i].resposta, elemento); /*função da biblioteca string.h que comparar duas strings: se retornar 0, é porque sao iguais*/

        /*caso as duas strings sejam iguais, ira incrementar a variavel count, que sera o retorno da funcao*/
        if(comparar == 0){
            count++;
        }
        i++;
        }

    return count;
}

/*função que transforma uma string para maiúsculo*/
void deixar_maiusculo(char *frase) 
{

    int i; /*utlizada no loop*/
    i=0;

    while (i < strlen(frase)){

    /*Analisando a tabela ASCII, podemos ver que o intervalo de caracteres minusculos é este que está escrito abaixo.
    Também podemos ver que subtraindo 32 desses valores obteremos o caractere correspondente maiusculo*/
    if (frase[i] >= 97 && frase[i] <= 122){
        frase[i] = frase[i] - 32;
        }

    i++;
    }
}

int index_espaco(char* string) 
{
    int index;

    for(index = 0 ; index < strlen(string); index++){
        if (string[index] == ' '){
            return index;
        }
    }
    return -1;
}

/*função que irá receber a resposta do jogador e verificar se a mesma é válida. Deverá ser chamada a cada round*/
void get_resposta(jogador *jogador, char letra_sorteada, char categoria[18]) 
{

    /*algumas variaveis...*/
    char resposta[100];/*guardara temporariamente a resposta inserida pelo usuario.*/
    struct timeval inicio, fim; /*servirão de marcações para o calculo do tempo*/
    float tempo; /*será a diferença do inicio e do fim, calculando, assim, o tempo total*/
    int x, i, idx; /*apoio*/
    char c; /*apoio*/
    

    gettimeofday(&inicio, 0); /*calcula o inicio do tempo*/

    /*esta é a seção principal da função: um loop que só irá para de ser executado quando o jogador inserir uma reposta válida*/
    while(1){
        printf("\nResposta = ");

        /*receber caractere por caractere do usuário e relacionar a uma posição do vetor resposta até que seja pressionada a tecla ENTER. Note que, no momento, não há nenhum tipo de analise da reposta. Isso será feito posteriormente*/
        i=0;

        /*É necessário esvaziar a string, pois, caso não seja a primera execução do loop, haverá uma resposta armazenada no vetor*/
        resposta[0]='\0'; 

        while(1){
            c = getchar();
            if(c=='\n'){
            break;
            }
            else{
                resposta[i] = c;
                i++;
                continue;
            }
        }
        
        /*É necessário manter todas as letras da resposta na mesma -case-, pois, quando formos fazer a avaliação de repetição, não poderão ser diferentes. Foi escolhido maiúsculo por conta da facilidade de visualização no prompt*/
        deixar_maiusculo(resposta); 

        /*inicio da validaçao da resposta*/

        /*se o primeiro caractere da resposta não for a letra sorteada, não será válida*/
        if(resposta[0] != letra_sorteada){

            printf("\nInsira uma resposta que comece com %c.\n", letra_sorteada);
            continue;
        }
        /*se a resposta possuir mais de 30 caracteres, não será válida*/
        else if (strlen(resposta) > MAXRESPOSTA){

            printf("\nInsira uma resposta até 30 caracteres.\n");
            continue;
        }
        /*caso contrário, a resposta é válida*/
        else{
            break;
        }
    }

    gettimeofday(&fim, 0); /*calcula o fim do tempo*/

    tempo = (fim.tv_sec - inicio.tv_sec); /*calcula o tempo total*/

    /*observe que, apesar de termos validado a inserção da resposta, não validamos o tempo. Devemos fazer isso agora*/
    if(tempo > jogador->tempo_max){
        printf("\nVocê não conseguiu responder a tempo, sua resposta não será considerada.\n");
        
        /*apagar todos os elementos do vetor "resposta", pois o jogador não respondeu dentro do tempo máximo, então a resposta não deverá ser considerada*/
        resposta[0]='\0';
    }
    /*agora, devemos verificar se a palavra inserida pelo jogador foi composta, ou seja, se possui um espaço (' ') no input*/
    else if (strcmp(categoria,"Nomes de Pessoas") == 0){
        idx = index_espaco(resposta); 
        if(idx>0){

        printf("\nVocê inseriu um nome composto. Será considerada apenas a primeira palavra \n");
        
        /*faremos um slicing ate o primeiro espaco*/
        resposta[idx] = '\0';
        }
    }

    /*E, por fim, deveremos armazenar as informações obtidas na struct do jogador, para que possam ser acessadas posteriormente por outras partes do código*/

    /*passar a resposta inserida para a struct do jogador*/
    jogador->resposta = malloc(strlen(resposta) * sizeof(char));
    strcpy(jogador->resposta, resposta);

    /*passar o tempo da jogada para a struct*/
    jogador->tempo_parcial = tempo; 
}

/*funcao que calcula a pontuação e registra no vetor de jogadores. Deverá ser chamado no final de cada round*/
void calcular_pontuacao(jogador *jogadores, int N) 
{
    /*algumas variaveis...*/
    int i; /*de apoio para o loop*/
    int pontuacao_final;
    double pontuacao; /*armazera temporariamente a pontuacao parcial do jogador*/
    double count;/*armazenara a quantidade de jogadores que inseriram a mesma resposta*/
    /*a função consiste de um loop que analisará jogador por jogador do vetor principal do programa*/
    for(i = 0 ; i < N ; i++){
    pontuacao = strlen(jogadores[i].resposta);/*calcula a quantidade de caracteres da resposta que será equivalente à pontuação*/
    /*observe que, caso o jogador tenha passado o tempo, sua resposta terá sido vazia, ou seja, não terá feito pontos*/
    /*outro fator do calculo da pontuação é a repetição de respostas. Para analisar isso, usaremos a função "contar_elementos", que irá verificar a ocorrência da resposta do jogador que está sendo analisado no loop*/
    count = contar_elementos(jogadores[i].resposta,jogadores,N); /*calcula quantos jogadores inseriram a mesma reposta*/
    
    /*caso a função tenha achado algum valor maior que um (ou seja, além da própria resposta), terá que ser realizada uma modificação na contagem feita previamente*/
    pontuacao = pontuacao / count; /*divide a pontuacao pelo numero de respostas iguais. Observe que se count = 1, o valor não irá mudar, pois só ha uma ocorrencia*/
    /*apos os calculos, é necessário passar todas as informações obtidas para a struct*/
    pontuacao_final = (int) ceil(pontuacao);
    /*resultados parciais*/
    jogadores[i].pontos_parcial = pontuacao_final;
    /*a variavel tempo_parcial é definida na funcao get_resposta*/
    /*resultados totais (incrementam-se as variaveis totais com as parciais)*/
    jogadores[i].pontos_total += pontuacao_final;
    jogadores[i].tempo_total += jogadores[i].tempo_parcial;

    }
    
}

int vencedor(jogador *jogadores, int N) 
{
	/*inicialização das variáveis de suporte*/
	char *nome;
	float menor_tempo = 0;
	int maior_pontuacao = 0;
	int i = 0;

	nome = malloc(MAXNOME * sizeof(char));
	/*loop para percorrer a lista de jogadores*/
	for(i = 0; i < N; i++) {  
     /*Se o jogador tem uma pontuação mais alta, as variáveis de suporte são atualizadas com as informações desse jogador*/
		if (jogadores[i].pontos_total > maior_pontuacao) {
      maior_pontuacao = jogadores[i].pontos_total;
    	menor_tempo = jogadores[i].tempo_total;
    	strcpy(nome, jogadores[i].nome);
    	}
    	/*Caso haja empate, devemos considerar o menor tempo*/
		else if(jogadores[i].pontos_total== maior_pontuacao && jogadores[i].tempo_total< menor_tempo)
		{
      maior_pontuacao = jogadores[i].pontos_total;
    	menor_tempo = jogadores[i].tempo_total;
  		strcpy(nome, jogadores[i].nome);
    	}
	}
	printf("\nO ganhador é: %s\n", nome);
	return 0;
}

int placar(jogador *jogadores, int N, int rodada, char categorias[5][18], int *ordem_categorias, int *rodada_1, int *rodada_2, int *rodada_3, int *rodada_4){
	int i;
	/*vetores que armazenam a pontuação parcial de cada rodada. Dentro de cada vetor existem N inteiros que correspondem à pontuação do enésimo jogador*/
	/*Ex: uma rodada com 3 jogadores, os vetores serão da seguinte forma [x, y, z], onde x corresponde ao jogador[0], y ao jogador[1] e z ao jogador[2]*/
	


	if (rodada == 0){
		printf("\nConcluida a rodada, esta eh a tabela de escores:\n\n");
		printf("\t%s|Placar Parcial\n", categorias[ordem_categorias[0]]);
		for(i = 0; i < N; i++){
			/*loop para printar o nome de cada jogador e a quantidade de pontos na rodada atual e nas anteriores, além do total parcial, usando informações da struct e dos vetores de apoio*/
			printf("%s\t\t%d\t\t%d\n", jogadores[i].nome, jogadores[i].pontos_parcial, jogadores[i].pontos_total);
			rodada_1[i] = jogadores[i].pontos_parcial; /*Armazenando a quantidade de pontos da rodada no vetor de apoio que servirá para as rodadas seguintes*/
		}
	}
    /*lógica análoga a da rodada 1, e assim para as demais rodadas*/
	else if(rodada == 1){
		printf("\nConcluida a rodada, esta eh a tabela de escores:\n\n");
		printf("\t%s|%s|Placar Parcial\n", categorias[ordem_categorias[0]], categorias[ordem_categorias[1]]);
		for(i = 0; i < N; i++){
			printf("%s\t\t%d\t\t%d\t\t%d\n", jogadores[i].nome, rodada_1[i], jogadores[i].pontos_parcial, jogadores[i].pontos_total);
			rodada_2[i] = jogadores[i].pontos_parcial;
		}
	}
	else if(rodada == 2){
		printf("\nConcluida a rodada, esta eh a tabela de escores:\n\n");
		printf("\t%s|%s|%s|Placar Parcial\n", categorias[ordem_categorias[0]], categorias[ordem_categorias[1]],categorias[ordem_categorias[2]]);
		for(i = 0; i < N; i++){
			printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\n", jogadores[i].nome, rodada_1[i], rodada_2[i], jogadores[i].pontos_parcial, jogadores[i].pontos_total);
			rodada_3[i] = jogadores[i].pontos_parcial;
		}
	}
	else if(rodada == 3){
		printf("\nConcluida a rodada, esta eh a tabela de escores:\n\n");
		printf("\t%s|%s|%s|%s|Placar Parcial\n", categorias[ordem_categorias[0]], categorias[ordem_categorias[1]], categorias[ordem_categorias[2]], categorias[ordem_categorias[3]]);
		for(i = 0; i < N; i++){
			printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", jogadores[i].nome, rodada_1[i], rodada_2[i], rodada_3[i], jogadores[i].pontos_parcial, jogadores[i].pontos_total);
			rodada_4[i] = jogadores[i].pontos_parcial;
		}
	}
	else if(rodada == 4){
		printf("\nRESULTADO FINAL:\n\n");
		printf("\t%s|%s|%s|%s|%s|Placar Final\n", categorias[ordem_categorias[0]], categorias[ordem_categorias[1]], categorias[ordem_categorias[2]], categorias[ordem_categorias[3]], categorias[ordem_categorias[4]]);
		for(i = 0; i < N; i++){
			printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", jogadores[i].nome, rodada_1[i], rodada_2[i], rodada_3[i], rodada_4[i], jogadores[i].pontos_parcial, jogadores[i].pontos_total);
			rodada_4[i] = jogadores[i].pontos_parcial;
		}
	}
	return 0;
}