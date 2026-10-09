// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Gustavo Soares de Jesus Anunciação
//  email: 20261160012@ifba.edu.br
//  Matrícula: 20261160012
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
 // Usa a função que o professor criou para separar dia, mês e ano
    DataQuebrada dq = quebraData(data);

    // Se o formato da string não tinha as barras ou tamanho correto
    if (dq.valido == 0) {
        return 0;
    }

    int dia = dq.iDia;
    int mes = dq.iMes;
    int ano = dq.iAno;

    // Se o ano veio com apenas 2 dígitos (ex: 15 para 2015)
    if (ano < 100) {
        ano += 2000;
    }

    // Validações básicas de mês e ano
    if (mes < 1 || mes > 12) {
        return 0;
    }
    if (dia < 1 || dia > 31) {
        return 0;
    }

    // Descobre quantos dias o mês tem
    int diasNoMes;

    if (mes == 2) {
        // Regra do Ano Bissexto
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
            diasNoMes = 29;
        } else {
            diasNoMes = 28;
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasNoMes = 30; // Meses de 30 dias
    } else {
        diasNoMes = 31; // Meses de 31 dias
    }

    // Checa se o dia respeita o limite daquele mês
    if (dia > diasNoMes) {
        return 0; 
    }

    return 1; 
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    DiasMesesAnos dma;

    //Valida data inicial
    if (q1(datainicial) == 0) {
        dma.retorno = 2; // Data inicial inválida
        return dma;
    } 

    // Valida data final
    if (q1(datafinal) == 0) {
        dma.retorno = 3; // Data final inválida
        return dma;
    }

    // Extrai os valores numéricos das datas usando quebraData
    DataQuebrada dqIni = quebraData(datainicial);
    DataQuebrada dqFin = quebraData(datafinal);

    int dIni = dqIni.iDia, mIni = dqIni.iMes, aIni = dqIni.iAno;
    int dFin = dqFin.iDia, mFin = dqFin.iMes, aFin = dqFin.iAno;

    // Ajusta o ano se ele tiver apenas 2 dígitos
    if (aIni < 100) aIni += 2000;
    if (aFin < 100) aFin += 2000;

    // Testa se datainicial > datafinal
    if (aIni > aFin || 
       (aIni == aFin && mIni > mFin) || 
       (aIni == aFin && mIni == mFin && dIni > dFin)) {
        dma.retorno = 4; // datainicial é maior que datafinal
        return dma;
    }

    // Cálculo da diferença de Dias, Meses e Anos
    int qtdDias, qtdMeses, qtdAnos;

    // Se o dia final for menor que o inicial, pede emprestado do mês anterior
    if (dFin < dIni) {
        int mAnterior = mFin - 1;
        int aAnterior = aFin;
        if (mAnterior == 0) {
            mAnterior = 12;
            aAnterior--;
        }

        // Descobre os dias do mês anterior
        int diasNoMesAnterior;
        if (mAnterior == 2) {
            if ((aAnterior % 4 == 0 && aAnterior % 100 != 0) || (aAnterior % 400 == 0))
                diasNoMesAnterior = 29;
            else
                diasNoMesAnterior = 28;
        } else if (mAnterior == 4 || mAnterior == 6 || mAnterior == 9 || mAnterior == 11) {
            diasNoMesAnterior = 30;
        } else {
            diasNoMesAnterior = 31;
        }

        dFin += diasNoMesAnterior;
        mFin--;
    }

    qtdDias = dFin - dIni;

    // Se o mês final ficou menor que o inicial, pede emprestado do ano
    if (mFin < mIni) {
        mFin += 12;
        aFin--;
    }

    qtdMeses = mFin - mIni;
    qtdAnos = aFin - aIni;

    // Preenche o resultado na struct
    dma.qtdDias = qtdDias;
    dma.qtdMeses = qtdMeses;
    dma.qtdAnos = qtdAnos;
    dma.retorno = 1; // Sucesso!

    return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    int i = 0;

    char charBusca = c;

    // Se n for Case Sensitive e for maiúscula (A-Z), converte para minuscula
    if (isCaseSensitive != 1) {
        if (charBusca >= 'A' && charBusca <= 'Z') {
            charBusca = charBusca + 32;
        }
    }

    // Varre o texto caractere por caractere
    while (texto[i] != '\0') {
        char charAtual = texto[i];

        // Se n for Case Sensitive e for maiúscula (A-Z), converte para minuscula
        if (isCaseSensitive != 1) {
            if (charAtual >= 'A' && charAtual <= 'Z') {
                charAtual = charAtual + 32;
            }
        }

        // Se encontrou o caractere correspondente
        if (charAtual == charBusca) {
            qtdOcorrencias++;
        }

        i++;
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int idxPosicoes = 0;

    int tamTexto = 0;
    while (strTexto[tamTexto] != '\0') {
        tamTexto++;
    }

    int tamBusca = 0;
    while (strBusca[tamBusca] != '\0') {
        tamBusca++;
    }

    if (tamBusca == 0 || tamBusca > tamTexto) {
        return 0;
    }

    int posCharVisivel = 1;

    for (int i = 0; i <= tamTexto - tamBusca; i++) {
        // Ignora bytes de continuação de caracteres UTF-8 acentuados(unica maneira que encontrei para tratar erros do windows)
        if ((unsigned char)strTexto[i] >= 0x80 && (unsigned char)strTexto[i] <= 0xBF) {
            continue;
        }

        int achou = 1;
        for (int j = 0; j < tamBusca; j++) {
            if (strTexto[i + j] != strBusca[j]) {
                achou = 0;
                break;
            }
        }

        if (achou == 1) {
            int tamBuscaVisivel = 0;
            for (int k = 0; k < tamBusca; k++) {
                if (!((unsigned char)strBusca[k] >= 0x80 && (unsigned char)strBusca[k] <= 0xBF)) {
                    tamBuscaVisivel++;
                }
            }

            posicoes[idxPosicoes] = posCharVisivel;
            posicoes[idxPosicoes + 1] = posCharVisivel + tamBuscaVisivel - 1;

            idxPosicoes += 2;
            qtdOcorrencias++;
        }

        posCharVisivel++;
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
int numInvertido = 0;

    while (num > 0) {
        int digito = num % 10;                     // Pega o último dígito
        numInvertido = (numInvertido * 10) + digito; // Adiciona o dígito ao número invertido
        num = num / 10;                            // Remove o último dígito do número original
    }

    return numInvertido;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias;
    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
 {
     int achou;
     return achou;
 }



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}