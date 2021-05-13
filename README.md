# Trabalho Prático 1 - BCC203 (EDII)
---
### **Autores**:
* Carlos Eduardo Gonzaga Romaniello de Souza
* Vinicius Gabriel Angelozzi Verona de Resende

---

### **OBSERVAÇÕES**
Nesse repositório não estão presentes os diretórios `output`, `graficos` e `estatisticas` devido a quantidade de arquivos presentes nessas pastas.
  
---
### **Requisitos**
Para executar os `scripts` de testes, é necessário ter a linguagem de programação `Julia` instalado localmente em sua máquina, para isso, basta acessar [http://julialang.org](https://julialang.org) e seguir os passos de instalação da linguagem.

---

### **Execução**
Tendo os requisitos em ordem, basta executar o seguinte comando baseado no sistema operacional de sua máquina:

>WINDOWS:
```bash
> cd scripts/
```
```bash
> execution.bat
```

>LINUX:
```bash
$ cd scripts/
```
```bash
$ sh execution.sh
```

Caso queira executar o programa manualmente e com os próprios parâmetros, basta seguir o exigido pelo professor Guilherme.

>WINDOWS:
```bash
> cd src/
```
```bash
> gcc *.c -o main.exe -Wall
```
```bash
> main.exe pesquisa quantidade ordem chave [-P]
```

>LINUX:
```bash
$ cd src/
```
```bash
$ gcc *.c -o main -Wall
```
```bash
$ ./main pesquisa quantidade ordem chave [-P]
```

---

### **Estruturação das Pastas**
Conforme mencionado no relatório presente na pasta raiz, os arquivos estão todos organizados em pastas. Para encontrar o arquivo que deseja, basta seguir o caminho abaixo:

> Codigo
* `scripts` - /scripts/ & /scripts/julia
* `código fonte` - /src/metodo_que_deseja.c
* `código header` - /src/metodo_que_deseja.h

> Árquivos
* `Binários` - /output/metodo/quantidade.bin (gerados após uma execução do programa)
* `Chaves aleatórias` - /input/quantidade.txt
* `Estatisticas` - /estatisticas/metodo/metodo_quantidade_ordem_key*.txt -> (* = 1-10)

> Coleta de estatisticas
* `Códigos` - /julia/txtMetodo.jl
* `script` - /julia/geraArqEst.sh
* `Coleta feita` - /julia/metodo.txt

> Gráficos
* `Gráficos criacao` - /graficos/metodo/criterio/criacao/boxplot.html
* `Gráficos pesquisa` - /graficos/metodo/criterio/pesquisa/boxplot.html
* `Gráficos media` - /graficos/media/criterio/boxplot.html
* `Gráficos gerais` - /graficos/metodo/
  * `Acessos ao arquivo` - /acessos/boxplot.html
  * `Comparações de chaves` - /compTotal/boxplot.html
  * `Tempo de execução` - /tempoToal/boxplot.html

---

### **Observação**
No código presente no diretório `/src/construirArquivo.c` há um código comentado no fim do arquivo. Ele representa o código de árvore binária com manipulações totalmente externas.
