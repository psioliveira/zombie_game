# zombie_game
segundo projecto de IC
## Universidade Lusófona
##### Licenciatura em Aplicações Multimédia e Videojogos | Introdução à Computação

### 2º Projeto de Introdução à Computação 2017/2018

	Cristina Pietra nº a21701350
	Pedro Siqueira nº a21705187
  Sara ???
	22 de Janeiro de 2018

#### 1. Introdução

Como segundo projecto da cadeira de Introdução à Computação foi proposta a implementação de um jogo/simulador, em linguagem C, no qual zombies perseguem humanos.
Em grupos de dois ou três alunos, o material a entregar deve conter os ficheiros c. e os seus respectivos h., o ficheiro Doxyfile, o ficheiro .gitignore, a pasta escondida git. e o ficheiro README.md.

O jogo deve desenrolar-se numa grela 2D toroidal de dimensões X e Y e vizinhança de Moore. Em cada célula da grelha é apenas permitido um zombie ou um humano.
A simulação inicia-se com nz zombies e nh humanos, fazendo um total de n (nz + nh) agentes. Os agentes aparecem de forma aleatória pela grelha.

De forma a tonar isto possível, o jogo deve corresponder aos seguintes parametros: 


###### Regras

* O jogo é turn-based e a cada turno os agente podem realizar uma acção;
* Os humanos podem agir da seguinte forma: movimento;
* Os zombies podem agir da seguinte forma: movimento ou infecção de humanos;
* Os agentes podem movimentar-se para uma célula vazia numa vizinhança de Moore de raio 1;
* A infecção de humanos só pode ocorrer quando um zombie está numa célula adjacente na vizinhança de Moore;
* A ordem em que os agentes executam as suas acções é aleatória;
* Os agentes podem ser controlados pelo computador ou podem ser controlados pelo jogador;
* Se o agente for um zombie, infecta um humano ao mover-se para o local deste e se este humano for controlado pelo jogador, deixa de o ser, passando a ser controlado pelo computador;
* O jogo termina quando deixarem de existir agentes humanos na grelha;

###### Funcionamento

* O programa deve aceitar como único parâmetro um ficheiro de configuração em formato INI4 com as especificações incluidas no projecto; 
* A visualização do jogo deve ser feita através de uma biblioteca gráfica à escolha e deve obedecer à interface fornecida pelo ficheiro showworld.h.

###### Modos de jogo

* Modo automático: Acontece quando não existem agentes controlados pelo jogador.
* Modo interativo: Cada vez que um agente é controlado pelo jogador é chamado a agir, o programa espera o input do jogador. Quando deixam de existir agentes controlados pelo jogador, o programa entra em modo automático.


![](./fluxograma.svg)


#### 2. Descrição da solução

O programa é dividido em 7 ficheiros (main.c, a_intelligence.c, free_agent_grid.c, functions.c, functions.h, showworld_simple.c, showworld.h).

No ficheiro main.c (modificação do ficheiro fornecido pelo professor "example.c"), a estrutura que define as propriedades dos agentes (typedef struct AGENT) e a estrutura que define as propriedades do mundo (typedef struct WORLD) foram movidas para o ficheiro showworld.h.

Foi criado um array de todos os números de ID presentes na grelha, para que seja possível gerar aleatoriamente uma ordem de movimento de todos os agentes por turno, sem que existam repetições.

```c
unsigned int *agents_list= NULL;

    agents_list = (unsigned int*) calloc (WORLD_X*WORLD_Y,sizeof(unsigned int));
```

Número de agentes criados:

```c
unsigned int nagents = 0;
unsigned int turns = 0;
unsigned int a = 0;
```

Foram acrescentadas as seguintes linhas de código: 
Função de update da grelha, que desenha o mundo inicial; 
Função de movimento;
Actualização do mundo, imprimindo-o novamente no canvas.

```c
showworld_update(sw, &my_world);
movement(agent_grid, agents_list, nagents, turns);
showworld_update(sw, &my_world);
```

Como fora previamente esclarecido, as estruturas AGENT e WORLD encontram-se agora no ficheiro showworld.h:

```c
typedef struct {
    AGENT_TYPE type;        /**< Agent type.        */
    unsigned char playable; /**< Is agent playable? */
    unsigned short id;      /**< Agent ID.          */
} AGENT;
```


```c
typedef struct {
    AGENT *grid;        /**< World is a grid composed of agents. */
    unsigned int xsize; /**< Horizontal world size.              */
    unsigned int ysize; /**< Vertical world size.                */
} WORLD;
```

O motivo desta alteração permitiu o acesso a estas estruturas através dos outros ficheiros.



#### 4. Conclusão

A realização deste projecto deixou-nos familiarizados com a linguagem C e permitiu-nos aplicar os conceitos dados em aula.

#### 4. Referências

Bibliotecas utilizadas: 

