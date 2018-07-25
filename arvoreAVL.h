#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct _ArvoreAVL{
	int iNotaFiscal;
	fpos_t posicao;
	struct _ArvoreAVL *esquerda;
	struct _ArvoreAVL *direita;
	struct _ArvoreAVL *pai;
}ArvoreAVL;

void arvoveAVL(char nomeArquivo[50]);
void insereAVL(int nota, fpos_t posicao);
void imprimeArvoreAVL(ArvoreAVL *raizArvoreAVL);
void pesquisaAVL(FILE *arquivo, int nota, ArvoreAVL *noArvore);
void pesquisaNotaAVL (char nomeArquivo[50]);
void verificaBalanceamento(ArvoreAVL *arvore);
int altura(ArvoreAVL *arvore);
void rotacaoSimplesAVLDireita(ArvoreAVL *arvore);
void rotacaoSimplesAVLEsquerda(ArvoreAVL *arvore);
void rotacaoDuplaAVLDireita(ArvoreAVL *arvore);
void rotacaoDuplaAVLEsquerda(ArvoreAVL *arvore);
void limpaMemoria(ArvoreAVL *arvore);

















/*
void rotacaoSimplesADireita(NoAVL *no);
void rotacaoSimplesAEsquerda(NoAVL *no);
void rotacaoDuplaADireita(NoAVL *no);
void rotacaoDuplaAEsquerda(NoAVL *no);
void verificaBalAncestrais(NoAVL *no);
void arvoveAVL(FILE *arq);
void liberaMemoria(NoAVL *no);
void imprimeEmOrdem(NoAVL *no);
int altura(NoAVL *no);
void insertAVL(int nota, fpos_t posicao);
void pesquisaAVL(FILE *arq, int nota, NoAVL *noAtual, int *comp);
void pesquisaNotaAVL (FILE *arq);
*/
