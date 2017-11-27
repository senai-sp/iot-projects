# Componentização e Módulos

Neste exercício vamos aprender como separar o código de um Sketch do Arduino em múltiplos arquivos


## Criando um Sketch com vários `.ino`

Para separar um Sketch do Arduino entre múltiplos arquivos `.ino`, basta adicionar mais arquivos ao mesmo diretório.

O arquivo que possuir o mesmo nome do diretório do sketch é considerado o arquivo 'principal', e portanto deve ter os métodos `setup()` e `loop()`.

O restante dos arquivos são concatenados em ordem alfabética, portando podem haver problemas relacionados a arquivos anteriores referenciando entidades definidas somente em arquivos posteriores nessa ordem.

Exemplo:

```c++
// principal/extra.ino
void minhaFuncao() {
	Serial.println("Olá de outro arquivo!");
}
```

```c++
// principal/principal.ino
void setup() {
	Serial.begin(9600);
}

void loop() {
	minhaFuncao();
}
```

## Utilizando arquivos de Header e C++

Outra alternativa mais complexa é utilizar uma combinação de arquivos `.h + .cpp` para introduzir um outro módulo ao seu sketch.

Esta é a estrutura mais tradicional de projetos em C++, e pode-se mostrar necessária em cenários fora da IDE do Arduino.

O arquivo Header deve conter as definições das entidades definidas pelo arquivo C Plus Plus, que deve conter as implementações.

Exemplo:

```c++
// soma.h

// A definição de uma função não necessita de nomes de parâmetros, somente seus tipos
int somar2(int, int);
```

```c++
int somar2(int x, int y) {
	return x + y;
}
```

# Cenários propostos

Para a execução desse cenário você necessita somente de um pushbutton conectado a seu Arduino.

- 1 Pushbutton
- 1 Resistor 300 Ohm

## 1 - Básico

Faça que a porta serial informe se o botão está pressionado ou não num intervalo razoável.

Para isto, crie funções em um arquivo secundário e as invoque das funções `setup()` e `loop()` do arquivo principal.

## 2 - Módulo de Botão

Neste passo opcional, leia na seção de [Links](#links) a documentação de como criar classes no C++ e crie uma classe para manipular com maior conveniência um Pushbutton.

Ela deve receber como parâmetros:

- Um pino no qual o pushbutton que deve manejar está conectado
- Um pointer para uma função de callback que seja chamada quando o botão é pressionado
- Opcionalmente um tempo mínimo entre detectar dois pressionamentos do botão

**Desafio extra**: Adicionar suporte a "múltiplos cliques", passando a quantidade de pressionamentos detectados no intervalo de tempo para o callback.

Quer dizer, ao invés da assinatura do callback ser `void (*callback)()`, torná-la `void (*callback)(int clicks)`.

## Código

- [Básico](../exercicios/11-componentizacao/basico/)
- [Botão](../exercicios/11-componentizacao/classes/)

## Links

- [Header files no C](http://www.cprogressivo.net/2013/09/Header-cabecalho-o-que-sao-para-que-servem-como-criar-e-usar-seus-arquivos-.h.html)
- [Básico de classes em C++](http://www.inf.pucrs.br/~pinho/PRGSWB/OO/oocpp.html)
- [Ponteiros em C](https://www.ime.usp.br/~pf/algoritmos/aulas/pont.html)
