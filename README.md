# Amedonha
Este repositório consiste em um jogo chamado <b>amedonha</b>, similiar ao clássico "adedonha". Foi desenvolvido em equipe na linguagem C para cumprir com o trabalho intermediário da disciplica de <a href="https://cc.ufc.br/curso/matriz-curricular/?cod=CK0226">Programação</a> do curso de Ciência da Computação na Universidade Federal do Ceará (UFC).
<br>
> <b>Equipe:</b> <a href="https://github.com/caiofov">Caio Oliveira</a>, <a href="">João Pedro de Almeida</a> e <a href="https://github.com/pedrosfa">Pedro Amaral</a>

<h2>Instruções: </h2>
<ul>
<li>Para jogar, execute o arquivo <b>main.c</b></li>
<li>Para ler sobre as requisitos de desenvolvimento do programa, leia o arquivo <b>trabalho.pdf</b></li>
</ul>
  
<h2>Sobre o jogo: </h2>
<ul>
  
<li>No total, serão 5 rodadas. Cada uma correspondente a uma categoria (em ordem aleatória), são elas: “nomes de pessoas”, “nomes de cidade”, “nomes de animais”, “nomes de
comida” e “profissões”. Também será sorteada uma letra</li><br>
<li>A ordem de jogada de cada jogador mudará a cada rodada e será definida de maneira aleatória</li><br>
<li>Cada jogador possuirá um tempo especifico com base na ordem definida para responder:<b> (8 + 2 * N) - 2*i  </b>, sendo <b>N</b> o número total de jogadores registrados no início do jogo e <b>i</b> a ordem de reposta do jogador na rodada</li><br>
<li>Caso o usuário não responda a tempo, sua resposta não será considerada</li><br>
<li>Em específico para a categoria de “nomes de pessoas”, caso ocorra a inserção de nomes compostos, só será considerado o primeiro nome</li><br>
<li>Caso a resposta inserida possua mais de 30 caracteres ou não inicie com a letra sorteada, o programa irá pedir para o usuário inserir novamente uma resposta</li><br>
<li>O número de pontos obtido pelo jogador será equivalente ao número de caracteres da resposta inserida</li><br>
<li>Caso ocorra um empate, o vencedor será aquele que possui o menor tempo de jogadas</li><br>
</ul>
