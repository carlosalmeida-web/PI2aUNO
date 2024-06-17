# UNO Projeto Integrador 2

## Introdução

O projeto visa desenvolver um jogo de cartas chamado UNO para ser jogado em console, seguindo as mesmas regras do jogo original. O desenvolvimento do jogo utilizará listas simplesmente ligadas, listas duplamente ligadas, estruturas e outros conceitos abordados no curso de Estrutura de Dados.

## Estruturas

### Estrutura: NoCarta:
Estrutura que representa uma carta do baralho.

- **numero**: Enumeração que representa o número da carta.
- **categoria**: Caractere que representa a categoria da carta.
- **ant**: Ponteiro para o nó anterior na lista duplamente encadeada.
- **prox**: Ponteiro para o próximo nó na lista duplamente encadeada.

### Estrutura: Manilha:
Estrutura que representa a pilha de cartas de manilha de um jogador.

- **qtd**: Número inteiro que representa a quantidade de cartas na pilha.
- **mAtual**: Ponteiro para a carta atual de manilha na pilha.
- **inicioAzul**: Ponteiro para a carta inicial da cor Azul.
- **inicioVermelho**: Ponteiro para a carta inicial da cor Vermelha.
- **inicioVerde**: Ponteiro para a carta inicial da cor Verde.
- **inicioAmarelo**: Ponteiro para a carta inicial da cor Amarela.
- **inicioCuringa**: Ponteiro para a carta inicial de Curinga.

### Estrutura: Perfil:
Estrutura que armazena o perfil de um jogador.

- **nome**: Array de caracteres que armazena o nome do jogador.
- **wins**: Número inteiro que representa o número de vitórias do jogador.

### Estrutura: Settings:
Estrutura que armazena as configurações do jogo.

- **ordem**: Array de caracteres que representa a ordem das cores das cartas.

### Estrutura: NoJogador:
Estrutura que representa um jogador no jogo.

- **manilha**: Ponteiro para a lista duplamente encadeada circular da manilha do jogador.
- **perfil**: Ponteiro para o perfil do jogador.
- **isBot**: Booleano que indica se o jogador é um bot.
- **ant**: Ponteiro para o jogador anterior na lista circular de jogadores.
- **prox**: Ponteiro para o próximo jogador na lista circular de jogadores.
- **isUno**: Booleano que indica se o jogador disse "Uno".

### Estrutura: ListaJogadorCircular:
Estrutura que representa a lista circular de jogadores.

- **jAtual**: Ponteiro para o jogador atual na lista.
- **qtdJogadores**: Número inteiro que representa a quantidade de jogadores na lista.
- **qtdJogadas**: Número inteiro que representa a quantidade de jogadas realizadas.
- **isInverso**: Booleano que indica se o sentido da lista está invertido.

### Estrutura: Baralho:
Estrutura que representa o baralho de cartas.

- **cartas**: Array de ponteiros para as cartas do baralho.
- **topo**: Índice inteiro que representa o topo do baralho.

### Estrutura: Jogo:
Estrutura principal que representa o estado do jogo.

- **bMesa**: Ponteiro para o baralho de mesa.
- **bCompra**: Ponteiro para o baralho de compra.
- **cicloJogadores**: Ponteiro para a lista circular de jogadores.

## Funções

### Função: criarBaralho

A função `criarBaralho` aloca dinamicamente memória para uma nova estrutura `Baralho` e a inicializa.

#### Retorno
- Retorna um ponteiro para a estrutura `Baralho` recém-criada.

#### Comportamento
Aloca dinamicamente memória para uma nova estrutura `Baralho`.
Verifica se a alocação de memória foi bem-sucedida. Se não, imprime uma mensagem de erro e retorna `NULL`.
Inicializa o campo `topo` da estrutura `Baralho` como -1.
Retorna o ponteiro para a estrutura `Baralho`.

### Função: baralhoVazio

A função `baralhoVazio` verifica se o baralho está vazio.

#### Parâmetros
- `baralho`: Ponteiro para a estrutura `Baralho` que representa o baralho a ser verificado.

#### Retorno
- Retorna `1` se o baralho estiver vazio.
- Retorna `0` caso contrário.

#### Comportamento
Verifica se o valor de `topo` do baralho é igual a -1. Se estiver, indica que o baralho está vazio, retornando `1`. Caso contrário, retorna `0`.


### Função: baralhoCheio

A função `baralhoCheio` verifica se o baralho está cheio.

#### Parâmetros
- `baralho`: Ponteiro para a estrutura `Baralho` que representa o baralho a ser verificado.

#### Retorno
- Retorna `1` se o baralho estiver cheio.
- Retorna `0` caso contrário.

#### Comportamento
Verifica se o valor de `topo` do baralho é igual ao tamanho máximo do baralho menos 1 (ou seja, se o topo do baralho está na última posição). Se estiver, retorna `1` indicando que o baralho está cheio. Caso contrário, retorna `0`.

### Função: adicionarCarta

A função `adicionarCarta` recebe como parâmetros um ponteiro para uma estrutura `Baralho` e um ponteiro para uma estrutura `NoCarta`, representando respectivamente o baralho ao qual a carta será adicionada e a carta a ser adicionada.

#### Parâmetros
- `baralho`: Ponteiro para a estrutura `Baralho` ao qual a carta será adicionada.
- `carta`: Ponteiro para a estrutura `NoCarta` que representa a carta a ser adicionada ao baralho.

#### Comportamento
A função verifica se o baralho está cheio utilizando a função `baralhoCheio`. Se o baralho estiver cheio, imprime uma mensagem de erro indicando que não é possível adicionar mais cartas. Caso contrário, incrementa o valor de `topo` do baralho e adiciona a carta na posição correspondente do baralho, utilizando o valor de `topo` como índice.


### Função: pegarCarta

A função `pegarCarta` é responsável por remover e retornar a carta do topo do baralho especificado na estrutura `Baralho`. 

#### Parâmetros
- `baralho`: Ponteiro para a estrutura `Baralho` que representa o baralho do qual a carta será retirada.

Essa função verifica se o baralho está vazio. Se estiver vazio, imprime uma mensagem de erro e retorna NULL, indicando que não foi possível pegar uma carta. Caso contrário, a função obtém a carta do topo do baralho, atualiza o topo e retorna essa carta. 

Além disso, se a carta retirada for um curinga (+4) ou uma carta de coringa (mudança de cor), a função altera sua categoria para 'J', que representa a categoria especial de carta na implementação.

### Função: checarLista

A função `checarLista` é responsável por verificar e imprimir as informações das cartas presentes na lista circular de manilhas de um jogador específico no jogo.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo, incluindo a lista circular de manilhas do jogador atual.

Essa função percorre a lista circular de manilhas em ambas as direções (próximo e anterior) e imprime na tela as informações de cada carta, incluindo sua categoria e número. Ela é útil para depuração e verificação do estado atual das manilhas durante o jogo.

### Função: listarBaralho

A função `listarBaralho` imprime na saída padrão as informações das cartas presentes no baralho especificado na estrutura `Baralho`. Essa função é utilizada para visualizar as cartas presentes no baralho durante o jogo.

#### Parâmetros
- `cartas`: Ponteiro para a estrutura `Baralho` que contém as cartas a serem listadas.

Essa função percorre o vetor de cartas do baralho e imprime na tela as informações de cada carta, incluindo seu número e categoria.

### Função: listarManilha

A função `listarManilha` imprime na saída padrão as informações das cartas presentes na lista de manilhas de uma estrutura `Manilha`. Essa função é utilizada para visualizar as cartas jogadas durante o jogo, mostrando seus números e categorias.

#### Parâmetros
- `cartas`: Ponteiro para a estrutura `Manilha` que contém as cartas a serem listadas.

Essa função percorre a lista de manilhas e imprime na tela as informações de cada carta, incluindo seu número, categoria e quantidade.

### Função: criarManilha

A função `criarManilha` aloca dinamicamente memória para uma nova estrutura `Manilha`, inicializa seus campos e retorna um ponteiro para ela. Esta função é usada para criar e inicializar uma nova estrutura `Manilha` antes de ser utilizada no jogo.

#### Retorno
Retorna um ponteiro para a nova estrutura `Manilha` inicializada.

### Função: slotOrdemManilha

A função `slotOrdemManilha` retorna o ponteiro para o primeiro nó da lista de manilhas de uma cor específica na estrutura `Manilha`. Essa função é utilizada para acessar a lista de manilhas correspondente à cor especificada durante o jogo.

#### Parâmetros
- `manilha`: Ponteiro para a estrutura `Manilha` que contém a lista de manilhas de uma cor específica à qual se deseja acessar.

#### Retorno
Retorna o ponteiro para o primeiro nó da lista de manilhas da cor específica.


### Função: adicionarManilhaAtualSlotCor

A função `adicionarManilhaAtualSlotCor` adiciona a carta atualmente em jogo à lista de manilhas de uma cor específica na estrutura `Manilha`. Esta função é usada durante o jogo para atribuir a carta atual à lista de manilhas correspondente à sua cor.

#### Parâmetros
- `manilha`: Ponteiro para a estrutura `Manilha` que contém a lista de manilhas de uma cor específica à qual a carta atual será adicionada.
- `cartaAtual`: Ponteiro para a carta que será adicionada à lista de manilhas.

#### Retorno
A função não possui retorno explícito.



### Função: slotCorVazio

A função `slotCorVazio` verifica se a lista de manilhas de uma cor específica na estrutura `Manilha` está vazia. As manilhas representam as cartas jogadas de uma determinada cor durante o jogo. Esta função é útil para determinar se não há cartas de uma cor específica jogadas no momento.

#### Parâmetros
- `manilha`: Ponteiro para a estrutura `Manilha` que contém a lista de manilhas de uma cor específica que será verificada.

#### Retorno
Retorna `true` se a lista de manilhas estiver vazia e `false` caso contrário.

### Função: adicionarNoManilha

A função `adicionarNoManilha` é responsável por adicionar uma nova carta à lista de manilhas de uma cor específica na estrutura `Manilha`. Essa função realiza várias operações, incluindo alocação de memória para um novo nó de manilha, inserção da carta nesse nó, incremento da contagem de cartas na estrutura `Manilha`, e, dependendo do caso, inserção ordenada da nova carta na lista de manilhas.

#### Parâmetros
- `manilha`: Ponteiro para a estrutura `Manilha` à qual a carta será adicionada.
- `carta`: Ponteiro para a carta que será adicionada à manilha.

#### Retorno
A função não retorna nenhum valor explicitamente, mas altera a estrutura `Manilha` passada como parâmetro, adicionando a nova carta à sua lista de manilhas.


### Função: getBaralhoCompra

A função `getBaralhoCompra` retorna o ponteiro para o baralho de compra associado ao jogo especificado na estrutura `Jogo`.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo, incluindo o baralho de compra.

#### Retorno
Retorna um ponteiro para o baralho de compra (`Baralho *`) associado ao jogo.


### Função: getBaralhoMesa

A função `getBaralhoMesa` retorna o ponteiro para o baralho de mesa associado ao jogo especificado na estrutura `Jogo`. Esta função é utilizada para acessar o baralho de mesa durante o jogo, permitindo interações com as cartas que estão na mesa.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo, incluindo o baralho de mesa.

#### Retorno
Retorna um ponteiro para o baralho de mesa (`Baralho *`) associado ao jogo.


### Função: criarJogo

A função `criarJogo` aloca dinamicamente memória para uma nova estrutura `Jogo` e a inicializa com um baralho de compra, um baralho de mesa e um ciclo de jogadores.

#### Retorno
- Retorna um ponteiro para a estrutura `Jogo` recém-criada.

#### Comportamento
Aloca dinamicamente memória para uma nova estrutura `Jogo`.
Verifica se a alocação de memória foi bem-sucedida. Se não, imprime uma mensagem de erro e retorna `NULL`.
Inicializa o campo `bCompra` da estrutura `Jogo` com um baralho de compra gerado pela função `gerarBaralho`.
Inicializa o campo `bMesa` da estrutura `Jogo` com um novo baralho de mesa criado pela função `criarBaralho`.
Inicializa o campo `cicloJogadores` da estrutura `Jogo` com um novo ciclo de jogadores criado pela função `criarCiclo`.
Encontra a posição da última carta normal no baralho de compra.
Troca a última carta normal do baralho de compra com a carta que está na posição encontrada.
Obtém a primeira carta do baralho de compra e a adiciona ao baralho de mesa.
Retorna o ponteiro para a estrutura `Jogo`.


### Função: proximoNoJogador

A função `proximoNoJogador` avança para o próximo nó jogador no ciclo de jogadores associado ao jogo especificado na estrutura `Jogo`.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo, incluindo o ciclo de jogadores.

#### Comportamento
Verifica se o jogo ou o nó jogador atual são inválidos. Se forem, imprime uma mensagem de erro e retorna.
Se o ciclo de jogadores estiver no sentido normal (isInverso == false), avança para o próximo nó jogador no ciclo, atualizando o campo `jAtual` para o próximo nó jogador.
Se o ciclo de jogadores estiver no sentido inverso (isInverso == true), retrocede para o nó jogador anterior no ciclo, atualizando o campo `jAtual` para o nó jogador anterior.

### Função: isPlayer

A função `isPlayer` verifica se o jogador atual no jogo especificado na estrutura `Jogo` é um jogador humano ou um bot.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo, incluindo o ciclo de jogadores.

#### Comportamento
Verifica se o nó jogador atual no ciclo de jogadores está presente. Se não estiver, imprime uma mensagem de erro crítico e encerra o programa.
Verifica se o perfil do jogador atual está presente. Se não estiver, imprime uma mensagem de erro e encerra o programa.
Retorna verdadeiro se o jogador atual for um bot (`isBot == true`), caso contrário, retorna falso.

### Função: distribuirBaralho

A função `distribuirBaralho` distribui um número especificado de cartas de um baralho para um jogador.

#### Parâmetros
- `baralho`: Ponteiro para a estrutura `Baralho` que contém as cartas a serem distribuídas.
- `noJogador`: Ponteiro para a estrutura `NoJogador` que representa o jogador que receberá as cartas.
- `quant`: Número inteiro indicando quantas cartas devem ser distribuídas.

#### Comportamento
- Itera sobre o número especificado de cartas a serem distribuídas.
Obtém uma carta do baralho chamando a função `pegarCarta`.
Verifica se a carta obtida é válida.
Adiciona a carta à manilha do jogador chamando a função `adicionarNoMalinha`.


### Função: getCartaMesa

A função `getCartaMesa` retorna a carta no topo do baralho de mesa associado ao jogo especificado na estrutura `Jogo`.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo, incluindo o baralho de mesa.

#### Retorno
Retorna um ponteiro para a carta no topo do baralho de mesa (NoCarta *) associado ao jogo. Se o baralho de mesa estiver vazio, retorna NULL.

### Função: getManilha

A função `getManilha` retorna o ponteiro para a estrutura `Manilha` associada ao jogador atual no jogo especificado na estrutura `Jogo`.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo, incluindo o ciclo de jogadores.

#### Retorno
Retorna um ponteiro para a estrutura `Manilha` associada ao jogador atual no jogo. Se o jogador atual não estiver definido, uma mensagem de erro crítico é impressa e o programa é encerrado.

### Função: manilhaVazia

A função `manilhaVazia` verifica se a lista de manilhas associada ao jogador atual no jogo especificado na estrutura `Jogo` está vazia.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo, incluindo o ciclo de jogadores.

#### Retorno
Retorna `true` se a lista de manilhas do jogador atual estiver vazia, e `false` caso contrário.

### Função: pegarCartaManilha

A função `pegarCartaManilha` é responsável por remover e retornar a carta do topo da lista de manilhas especificada na estrutura `Manilha`.

#### Parâmetros
- `manilha`: Ponteiro para a estrutura `Manilha` que representa a lista de manilhas da qual a carta será retirada.

#### Retorno
Retorna um ponteiro para a carta removida da lista de manilhas. Se a lista de manilhas estiver vazia, retorna NULL.

#### Comportamento
A função determina a cor da manilha atual e escolhe a lista correspondente para retirar a carta.
Se a carta removida for a última da lista de manilhas, a lista é resetada.
Caso contrário, a carta é removida da lista e seus ponteiros anteriores e posteriores são ajustados.
A função decrementa a contagem de cartas na lista de manilhas e retorna a carta removida.

### Função: enviarManilha

A função `enviarManilha` transfere uma carta da lista de manilhas para um baralho especificado.

#### Parâmetros
- `manilha`: Ponteiro para a estrutura `Manilha` que representa a lista de manilhas da qual a carta será retirada.
- `baralho`: Ponteiro para a estrutura `Baralho` que representa o baralho para o qual a carta será transferida.

#### Retorno
Retorna um ponteiro para a carta transferida para o baralho. Se o baralho estiver vazio ou nulo, a função imprime uma mensagem de erro e encerra o programa.

#### Comportamento
- Verifica se o baralho está vazio ou nulo. Se sim, imprime uma mensagem de erro e encerra o programa.
- Chama a função `pegarCartaManilha` para obter a carta do topo da lista de manilhas.
- Se a carta obtida for NULL, imprime uma mensagem de erro e encerra o programa.
- Adiciona a carta ao baralho especificado usando a função `adicionarCarta`.
- Retorna um ponteiro para a carta transferida para o baralho.

### Função: maiorQtdCor

A função `maiorQtdCor` determina a cor predominante nas cartas da lista de manilhas do jogador atual.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo.

#### Retorno
Retorna a cor predominante nas cartas da lista de manilhas do jogador atual. Se não houver nenhuma carta na lista de manilhas, a função retorna a primeira cor do conjunto de cores: 'R', 'G', 'B', 'Y'.

#### Comportamento
- Obtém a lista de manilhas do jogador atual.
- Inicializa um vetor `numCor` com 4 posições, uma para cada cor ('R', 'G', 'B', 'Y'), e inicializa todas as posições com 0.
- Inicializa as variáveis `maiorQtd` com -1 e `maiorCor` com 0.
- Cria uma string `cor` contendo as cores possíveis: "RGBY".
- Itera sobre as cartas da lista de manilhas:
  - Se a categoria da carta for 'J', passa para a próxima carta.
  - Utiliza a função `strchr` para encontrar a posição da categoria da carta na string `cor`. Se a categoria não estiver na string, a função retorna NULL.
  - Incrementa o contador correspondente à cor encontrada no vetor `numCor`.
- Itera sobre o vetor `numCor` para encontrar a cor com a maior quantidade de cartas.
- Retorna a cor predominante.

### Função: poderCarta

A função `poderCarta` determina o poder associado a uma carta no jogo atual.

#### Parâmetros
- `carta`: Ponteiro para a estrutura `NoCarta` representando a carta cujo poder será determinado.
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo.

#### Retorno
Retorna o poder associado à carta. Se a carta for um número de 0 a 9, retorna 0. Se a carta for um +2, inverte a ordem de jogada, pula o próximo jogador ou altera a cor da carta, retorna 2. Se a carta for um coringa, altera a cor da carta e retorna 4. Se houver algum erro, retorna -1.

#### Comportamento
- Verifica se a carta passada como parâmetro é nula. Se for, imprime uma mensagem de erro e retorna -1.
- Verifica o número da carta:
  - Se for de 0 a 9, retorna 0.
  - Se for 10, retorna 2.
  - Se for 11, inverte a ordem de jogada.
  - Se for 12, pula para o próximo jogador.
  - Se for 13, altera a cor da carta.
  - Se for 14, altera a cor da carta e retorna 4.

### Função: alterarCorCarta

A função `alterarCorCarta` altera a cor de uma carta especificada para uma cor escolhida pelo jogador ou aleatoriamente.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo.
- `carta`: Ponteiro para a estrutura `NoCarta` representando a carta cuja cor será alterada.

#### Comportamento
- Verifica se o jogador é um bot ou um jogador humano:
  - Se for um bot, há 40% de chance de escolher uma cor aleatória com base na cor mais comum das cartas na manilha atual. Caso contrário, escolhe uma cor aleatória entre vermelho (R), verde (G), azul (B) e amarelo (Y).
  - Se for um jogador humano, solicita ao jogador que digite a primeira letra da cor desejada em inglês. O jogador deve escolher entre vermelho (R), verde (G), azul (B) e amarelo (Y).
- Altera a categoria da carta para a cor escolhida.

### Função: listarNoJogador

A função `listarNoJogador` imprime na saída padrão uma representação visual da ordem dos jogadores no ciclo de jogadores do jogo.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo.

#### Comportamento
- Verifica se o ciclo de jogadores está vazio. Se estiver vazio, a função retorna sem imprimir nada.
- Percorre o ciclo de jogadores e imprime na saída padrão a representação visual da ordem dos jogadores:
  - Se o jogador atual for um bot, imprime "(Player) ->".
  - Se o jogador atual for um jogador humano, imprime "(Bot) ->".

Observação: O ciclo de jogadores representa a ordem em que os jogadores estão sentados à mesa e determina a sequência de turnos durante o jogo.

### Função: adicionarNoJogador

A função `adicionarNoJogador` adiciona um novo nó de jogador ao ciclo de jogadores do jogo.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que contém as informações do jogo.
- `noJogador`: Ponteiro para o novo nó de jogador a ser adicionado ao ciclo de jogadores.
- `_isPlayer`: Valor booleano que indica se o novo jogador é um jogador humano (true) ou um bot (false).

#### Comportamento
- Verifica se o jogo ou o nó do jogador estão inicializados. Se algum deles não estiver inicializado, a função imprime uma mensagem de erro e retorna.
- Adiciona o novo nó de jogador ao ciclo de jogadores do jogo:
  - Se o ciclo de jogadores estiver vazio, o novo nó de jogador é atribuído como o jogador atual.
  - Se o ciclo de jogadores já tiver jogadores, o novo nó de jogador é inserido antes do jogador atual e depois do jogador anterior.
- Incrementa o contador de jogadores no ciclo de jogadores do jogo.

### Função: criarNoJogador

A função `criarNoJogador` aloca dinamicamente memória para um novo nó de jogador e inicializa seus campos.

#### Parâmetros
- `_isPlayer`: Valor booleano que indica se o jogador é um jogador humano (true) ou um bot (false).

#### Retorno
Retorna um ponteiro para o novo nó de jogador alocado e inicializado.

#### Comportamento
- Aloca memória para um novo nó de jogador (`NoJogador`).
- Verifica se a alocação de memória foi bem-sucedida. Se falhar, imprime uma mensagem de erro e retorna NULL.
- Inicializa os campos do novo nó de jogador:
  - `prox` e `ant` são definidos como o próprio nó de jogador, já que este será o único nó no início.
  - Aloca memória para o perfil do jogador (`Perfil`).
  - Define se o jogador é um bot ou um jogador humano com base no parâmetro `_isPlayer`.
  - Cria uma nova manilha para o jogador usando a função `criarManilha`.
  - Define que o jogador não está em estado UNO (`isUno` é inicializado como false).
- Retorna o ponteiro para o novo nó de jogador.

### Função: criarCiclo

A função `criarCiclo` aloca dinamicamente memória para uma nova lista circular de jogadores e inicializa seus campos.

#### Parâmetros
Nenhum.

#### Retorno
Retorna um ponteiro para a nova lista circular de jogadores alocada e inicializada.

#### Comportamento
- Aloca memória para uma nova lista circular de jogadores (`ListaJogadorCircular`).
- Verifica se a alocação de memória foi bem-sucedida. Se falhar, imprime uma mensagem de erro e encerra o programa.
- Inicializa os campos da nova lista circular de jogadores:
  - `isInverso` é inicializado como false.
  - `jAtual` é definido como NULL, indicando que não há jogador atualmente.
  - `qtdJogadas` e `qtdJogadores` são inicializados como 0.
- Retorna o ponteiro para a nova lista circular de jogadores.


### Função: embaralharMatriz

A função `embaralharMatriz` embaralha uma matriz de cartas representadas por valores inteiros.

#### Parâmetros
- `matrix`: Uma matriz de caracteres que representa as cartas a serem embaralhadas.

#### Comportamento
- Inicializa a semente para a função de geração de números aleatórios `rand()` usando a hora atual do sistema.
- Itera sobre a matriz de cartas.
- Para cada carta na matriz, gera um índice aleatório `j` dentro do intervalo de [0, i], onde `i` é o índice atual do laço.
- Troca as cartas nas posições `i` e `j` da matriz.
- Este processo embaralha aleatoriamente as cartas na matriz, garantindo uma distribuição aleatória das cartas.

### Função: gerarBaralho

A função `gerarBaralho` cria e inicializa um baralho a partir de um arquivo de texto que contém informações sobre as cartas.

#### Parâmetros
Nenhum.

#### Retorno
Retorna um ponteiro para a estrutura `Baralho` que representa o baralho gerado.

#### Comportamento
- Abre o arquivo "baralho.txt" em modo de leitura.
- Lê as cartas do arquivo e armazena as informações em uma matriz `cartas`, onde cada linha representa uma carta e a primeira linha contém a categoria da carta e a segunda linha contém o número da carta.
- Fecha o arquivo após a leitura.
- Embaralha as cartas na matriz `cartas` usando a função `embaralharMatriz`.
- Aloca dinamicamente memória para um novo baralho (`baralho_principal`).
- Inicializa o topo do baralho como -1.
- Para cada carta na matriz `cartas`, cria um nó de carta (`tempCarta`), preenche suas informações com a categoria e o número da carta correspondente na matriz, e adiciona esse nó ao baralho.
- Imprime as informações das cartas no baralho criado.
- Retorna o ponteiro para o baralho gerado.

### Função: reembaralhar

A função `reembaralhar` embaralha as cartas presentes na mesa e as adiciona de volta ao baralho, mantendo a ordem relativa das cartas na mesa.

#### Parâmetros
- `baralho`: Ponteiro para a estrutura `Baralho` que representa o baralho onde as cartas serão reembaralhadas.
- `mesa`: Ponteiro para a estrutura `Baralho` que representa a mesa onde as cartas estão inicialmente.

#### Comportamento
- Obtém a carta do topo da mesa usando a função `pegarCarta`.
- Cria um vetor de ponteiros para `NoCarta` chamado `vetor`, com tamanho igual ao número de cartas na mesa.
- Itera sobre as cartas na mesa, removendo cada carta da mesa e adicionando ao vetor `vetor`.
- Inicializa um ponteiro temporário `temp`.
- Em um loop, realiza o processo de embaralhamento:
  - Seleciona aleatoriamente dois índices no vetor `vetor` (`i` e `j`) para troca.
  - Troca as informações das cartas nos índices `i` e `j` no vetor `vetor`.
  - Repete o processo para garantir um embaralhamento mais eficaz.
- Adiciona as cartas reembaralhadas de volta ao baralho usando a função `adicionarCarta`.
- Adiciona a carta do topo da mesa de volta à mesa usando a função `adicionarCarta`.


### Função: topoBaralho

A função `topoBaralho` retorna a carta do topo do baralho especificado.

#### Parâmetros
- `baralho`: Ponteiro para a estrutura `Baralho` que representa o baralho.

#### Comportamento
- Verifica se o ponteiro para o baralho é nulo. Se for nulo, exibe uma mensagem de erro e encerra o programa.
- Retorna a carta do topo do baralho, acessando a posição do vetor de cartas correspondente ao topo do baralho.


### Função: jogadaValida

A função `jogadaValida` verifica se uma jogada é válida comparando a carta do jogador com a carta da mesa.

#### Parâmetros
- `pCarta`: Ponteiro para a estrutura `NoCarta` que representa a carta do jogador.
- `mCarta`: Ponteiro para a estrutura `NoCarta` que representa a carta da mesa.

#### Comportamento
- Verifica se a carta do jogador ou a carta da mesa não estão inicializadas. Se alguma delas não estiver inicializada, exibe uma mensagem de erro.
- Exibe as informações da carta do jogador e da carta da mesa.
- Verifica se a categoria da carta do jogador é igual à categoria da carta da mesa, ou se a categoria da carta do jogador é 'J' (coringa), ou se o número da carta do jogador é igual ao número da carta da mesa.
- Se alguma das condições acima for verdadeira, retorna verdadeiro, indicando que a jogada é válida. Caso contrário, retorna falso, indicando que a jogada é inválida.


### Função: playerUnoThread

A função `playerUnoThread` é responsável por gerenciar a ação de gritar "UNO" pelo jogador. 

#### Parâmetros
- `noJogador`: Ponteiro para a estrutura `NoJogador` que representa o jogador atual.

#### Comportamento
- Aguarda a entrada de um comando do jogador.
- Verifica se o jogador atual é um jogador humano.
- Se o jogador tiver apenas uma carta na mão e ainda não tiver gritado "UNO", ele cancela a ação de "UNO" automaticamente.
- Caso contrário, continua o loop.

### Função: unoThread

A função `unoThread` é responsável por gerenciar a ação de gritar "UNO" pelo jogador.

#### Parâmetros
- `noJogador`: Ponteiro para a estrutura `NoJogador` que representa o jogador atual.
- `jogo`: Ponteiro para a estrutura `Jogo` que representa o estado atual do jogo.

#### Comportamento
- Define o estado do jogador atual como "UNO".
- Aguarda um tempo aleatório entre 2 e 5 segundos.
- Verifica se o jogador atual ainda possui apenas uma carta na mão. Se não, cancela a ação de "UNO".
- Se o jogador for um bot, há uma probabilidade de 70% de que ele grite "UNO" automaticamente.
- Se o jogador for um humano e ainda estiver com uma carta na mão, o bot gritará "UNO" e o jogador terá que comprar uma carta.
- Se o jogador atual já tiver gritado "UNO" anteriormente e ainda estiver com uma carta na mão, o bot gritará "UNO" e o jogador terá que comprar uma carta.

### Função: contarComprarMais2

A função `contarComprarMais2` conta o número de cartas de compra (+2) em uma lista circular de cartas.

#### Parâmetros
- `noCarta`: Ponteiro para a estrutura `NoCarta` que representa a lista circular de cartas.

#### Retorno
- Retorna um array dinâmico de estruturas `NoCarta` contendo as cartas de compra (+2) encontradas. Retorna `NULL` em caso de falha ou se não houver cartas de compra.

#### Comportamento
- Percorre a lista circular de cartas e conta o número de cartas de compra encontradas.
- Aloca dinamicamente memória para armazenar as cartas de compra encontradas.
- Retorna o array dinâmico contendo as cartas de compra.

### Função: verificarComprarCarta

A função `verificarComprarCarta` verifica se é necessário comprar cartas devido à presença de cartas de compra (+2) na mesa.

#### Parâmetros
- `jogo`: Ponteiro para a estrutura `Jogo` que representa o estado atual do jogo.
- `compra`: Ponteiro para um inteiro que representa o número de cartas a serem compradas.

#### Retorno
- Retorna `true` se houver uma carta de compra (+4) na mesa, indicando que o próximo jogador deve comprar cartas.
- Retorna `false` caso contrário.

#### Comportamento
- Verifica se a carta no topo da mesa é uma carta de compra (+2).
- Se for uma carta de compra (+2), verifica se há outras cartas de compra (+2) na mão do jogador atual.
- Se houver outras cartas de compra (+2) na mão do jogador, pergunta ao jogador se deseja continuar a corrente de compra (+2).
- Se o jogador desejar continuar, permite que o jogador escolha uma carta para jogar da mesma cor.
- Adiciona as cartas compradas à mão do jogador.
- Se a carta no topo da mesa for uma carta de compra (+4), retorna `true`.
- Se não houver cartas de compra na mesa, compra cartas para o jogador atual até que `compra` seja igual a zero.

### Função: selecionarCarta

A função `selecionarCarta` permite que o jogador selecione uma carta da mão para jogar.

#### Parâmetros
- `tecla`: Tecla pressionada pelo jogador.
- `jogo`: Ponteiro para a estrutura `Jogo` que representa o estado atual do jogo.

#### Retorno
- Retorna o poder da carta jogada, se a jogada for válida. Retorna -1 caso contrário.

#### Comportamento
- Se a tecla pressionada for 'A' ou 'D', permite que o jogador navegue entre as cartas da mão.
- Se a tecla pressionada for 'W', verifica se a carta selecionada pode ser jogada.
  - Se a carta for válida, a joga na mesa e retorna o poder da carta jogada.
  - Se a carta for inválida, exibe uma mensagem informando que a jogada é inválida.
- Se a tecla pressionada for 'S', verifica se há cartas jogáveis na mão do jogador.
  - Se não houver, compra uma carta para o jogador até que ele tenha uma carta jogável.
  - Se a carta comprada não puder ser jogada, exibe uma mensagem informando que a jogada é inválida e permite que o jogador compre outra carta.

### Função: abastercerBaralho

A função `abastercerBaralho` transfere todas as cartas de um baralho doador para um baralho receptor.

#### Parâmetros
- `baralhoReceptor`: Ponteiro para o baralho que receberá as cartas.
- `baralhoDoador`: Ponteiro para o baralho que doará as cartas.

#### Comportamento
- Troca a primeira carta do baralho doador com a última carta do baralho doador.
- Enquanto houver cartas no baralho doador:
  - Remove a carta do topo do baralho doador.
  - Adiciona a carta ao baralho receptor.

### Função: pegarCartaCompra

A função `pegarCartaCompra` tenta pegar uma carta do baralho de compra. Se não houver cartas no baralho de compra, abastece-o com as cartas do baralho da mesa.

#### Parâmetros
- `baralhoMesa`: Ponteiro para o baralho da mesa.
- `baralhoCompra`: Ponteiro para o baralho de compra.

#### Retorno
- Retorna um ponteiro para a carta retirada do baralho de compra.

### Função: comprarCartaBot

A função `comprarCartaBot` permite que um bot compre uma carta, verificando se há cartas jogáveis após a compra.

#### Parâmetro
- `jogo`: Ponteiro para a estrutura `Jogo` que representa o estado atual do jogo.

#### Retorno
- Retorna `true` se a carta comprada puder ser jogada.
- Retorna `false` caso contrário.

### Função: comprarCarta

A função `comprarCarta` permite que um jogador compre uma carta do baralho de compra.

#### Parâmetro
- `jogo`: Ponteiro para a estrutura `Jogo` que representa o estado atual do jogo.

#### Retorno
- Retorna um ponteiro para a carta comprada.

### Função: cartasJogaveis

A função `cartasJogaveis` identifica as cartas jogáveis na mão do jogador com base na carta no topo da mesa e na carta de manilha atual.

#### Parâmetros
- `topo`: Ponteiro para a carta no topo da mesa.
- `atual`: Ponteiro para a estrutura `Manilha` que representa a carta de manilha atual.

#### Retorno
- Retorna um ponteiro para um vetor de ponteiros.
- O primeiro elemento do vetor é um ponteiro para um inteiro que armazena a quantidade de cartas jogáveis.
- Os elementos seguintes do vetor são ponteiros para as cartas de manilha jogáveis.

## Função printCarta

### Descrição:
Esta função imprime os detalhes da carta atual na estrutura `Manilha`.

### Parâmetros:
- `manilha`: Um ponteiro para a estrutura `Manilha` que contém informações sobre a carta atual.

### Retorno:
A função não retorna nenhum valor.

### Comportamento:
- Verifica se o ponteiro `manilha` e a carta atual não são nulos.
- Se ambos não forem nulos, imprime os detalhes da carta atual, incluindo sua categoria e número.
- Se `manilha` ou a carta atual forem nulos, imprime uma mensagem de erro indicando que a carta está vazia.
