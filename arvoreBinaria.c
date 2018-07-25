#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "arvoreBinaria.h"
#include "notaFiscal.h"
#include<time.h>
#include <stdlib.h>

ArvoreBinaria *raizArvoreBinaria;

int qtdComparacaoArvore;

void arvoreBinaria(char nomeArquivo[50]){
     FILE *arquivo;
     arquivo = fopen(nomeArquivo, "rb");
     fpos_t posicao;
     NF notaFiscal;
     clock_t inicio,fim;
     
     fseek(arquivo,0,SEEK_SET);
     fgetpos (arquivo, &posicao);           
     fread (&notaFiscal, sizeof(NF), 1, arquivo);
     
     inicio = clock();
     while (!feof(arquivo)){  
               printf("Nota Fiscal: %d\n", notaFiscal.iNotaFiscal);                
               insereArvoreBinaria(notaFiscal.iNotaFiscal, posicao);
               fgetpos (arquivo, &posicao);           
               fread (&notaFiscal, sizeof(NF), 1, arquivo);
     }   
     fim = clock();
     
      printf("\n\nArvore Binaria criada com SUCESSO\n");
      printf("Arvore Binaria Criada em ORDEM: \n");
      imprimeArvoreBinaria(raizArvoreBinaria);
      printf("\n\nA criacao da arvore demorou %f segundos\n", (float)(fim - inicio) / CLOCKS_PER_SEC); 
      printf("\n\n");
      fclose(arquivo);
      
} 

void insereArvoreBinaria(int nota, fpos_t posicao){
     
	if (raizArvoreBinaria == NULL){
		raizArvoreBinaria = (ArvoreBinaria*)malloc(sizeof(ArvoreBinaria));
		memset(raizArvoreBinaria, 0, sizeof(ArvoreBinaria));
		raizArvoreBinaria->iNotaFiscal = nota;
		raizArvoreBinaria->posicaoArvore = posicao;
	} else {
		ArvoreBinaria *pai;
		ArvoreBinaria *filho;
		int encontrou;
		

		pai = raizArvoreBinaria;
		while (((nota > pai->iNotaFiscal) && (pai->direita != NULL)) || ((nota < pai->iNotaFiscal) && (pai->esquerda != NULL))) {
			if (nota < pai->iNotaFiscal) {
				if (pai->esquerda != NULL){
					pai = pai->esquerda;
                }
			} else {
				if (pai->direita != NULL){
					pai = pai->direita;
                }
			}
		}
		
        filho = (ArvoreBinaria*)malloc(sizeof(ArvoreBinaria));
		memset(filho, 0, sizeof(ArvoreBinaria)); 
		filho-> iNotaFiscal= nota;
		filho-> posicaoArvore = posicao;

		if (nota < pai->iNotaFiscal)
			pai->esquerda = filho;
		else
			pai->direita = filho;
	}     
     
     
}

void imprimeArvoreBinaria(ArvoreBinaria *arvore){
     
	if (arvore != NULL) {
       if(arvore->esquerda != NULL) 
           imprimeArvoreBinaria(arvore->esquerda);

		printf("\nValor=%d", arvore->iNotaFiscal);
		
		if (arvore->direita != NULL)
           imprimeArvoreBinaria(arvore->direita);          
	}
	
	else
	    printf ("Arvore sem nenhum elemento");
    
}

void pesquisaArvoreBinaria (char nomeArquivo[50]){
     FILE *arquivo;
     arquivo = fopen(nomeArquivo,"rb");
     int nota;
     clock_t inicio,fim;
     qtdComparacaoArvore = 0;
     
     printf ("Digite o numero da Nota Fiscal a ser pesquisada: ");
     scanf ("%i", &nota);
     
     inicio = clock(); 
     pesquisaNoArvore(arquivo, nota, raizArvoreBinaria);
     fim = clock();
     
     printf("\n\nPara a Busca da nota foram necessarias %i comparacoes e demorou %f segundos\n", qtdComparacaoArvore,(float)(fim - inicio) / CLOCKS_PER_SEC); 
     fclose(arquivo);
     
} 

void pesquisaNoArvore(FILE *arquivo, int nota, ArvoreBinaria *noArvore){
       
       NF notaFiscal;
        
        
       if(noArvore!=NULL){          
           qtdComparacaoArvore++;
           if(noArvore->iNotaFiscal == nota){                    
               fseek(arquivo, noArvore->posicaoArvore, SEEK_SET);
               fread (&notaFiscal, sizeof(notaFiscal), 1, arquivo);    
               printf ("Nota Fiscal Encontrada:\n\n"); 
               printf("Numero nota fiscal: %i\n",notaFiscal.iNotaFiscal);
               printf("Nome do Cliente: %s\n",notaFiscal.sCliente);
               printf("Data de emissao: %s\n",notaFiscal.sDatEmis);
               printf("Condicao de Pagamento: %s\n",notaFiscal.sDesCondPgto);  
               return;
           }
           
           if(nota < noArvore->iNotaFiscal){
                  if (noArvore->esquerda != NULL){
                     pesquisaNoArvore(arquivo, nota, noArvore->esquerda);
                  }
           }
           
           if(nota > noArvore->iNotaFiscal){
               if(noArvore->direita !=NULL){
                   pesquisaNoArvore(arquivo, nota, noArvore->direita);
               }
           }                
       }
}

int main(){
    
    arvoreBinaria("notaFiscal.bin");
    pesquisaArvoreBinaria("notaFiscal.bin");
        
    system("pause");
    return 0;    
}
