#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct _ArvoreBinaria{
       int iNotaFiscal;
       fpos_t posicaoArvore;
       struct _ArvoreBinaria *esquerda;
       struct _ArvoreBinaria *direita;
}ArvoreBinaria;

void arvoreBinaria(char nomeArquivo[50]);
void insereArvoreBinaria(int nota, fpos_t posicao);
void imprimeArvoreBinaria(ArvoreBinaria *arvore);
void pesquisaArvoreBinaria (char nomeArquivo[50]);
void pesquisaNoArvore(FILE *arquivo, int nota, ArvoreBinaria *no);
