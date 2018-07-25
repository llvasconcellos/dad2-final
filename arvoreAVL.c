#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "notaFiscal.h"
#include <time.h>


typedef struct _ArvoreAVL{
	int iNotaFiscal;
	fpos_t posicao;
	struct _ArvoreAVL *esquerda;
	struct _ArvoreAVL *direita;
	struct _ArvoreAVL *pai;
}ArvoreAVL;

ArvoreAVL *raizArvoreAVL;

int qtdComparacaoAVL;

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


void arvoveAVL(char nomeArquivo[50]){
     FILE *arquivo;
     arquivo = fopen(nomeArquivo, "rb");
     fpos_t posicao;
     NF notaFiscal;
     clock_t inicio,fim;
     
     limpaMemoria(raizArvoreAVL);
     raizArvoreAVL = NULL;
     fgetpos (arquivo, &posicao);           
     fread (&notaFiscal, sizeof(notaFiscal), 1, arquivo);
     
     inicio = clock();
     while (!feof(arquivo)){  
           printf("Nota Fiscal: %d\n", notaFiscal.iNotaFiscal);                
           insereAVL(notaFiscal.iNotaFiscal, posicao);   
           fgetpos (arquivo, &posicao);           
           fread (&notaFiscal, sizeof(notaFiscal), 1, arquivo);
     }   
     fim = clock();
     
     printf("Imprimindo arvore AVL EM ORDEM: \n\n");
     imprimeArvoreAVL(raizArvoreAVL); 
     printf("\n\nArvore AVL criada com SUCESSO!\n\n");
     printf("\n\nA criacao da Arvore demorou %f segundos\n", (float)(fim - inicio) / CLOCKS_PER_SEC);  
     fclose(arquivo);
}     


void insereAVL(int nota, fpos_t posicao){

	if (raizArvoreAVL == NULL){
		raizArvoreAVL = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
		memset(raizArvoreAVL, 0, sizeof(ArvoreAVL));
		raizArvoreAVL->iNotaFiscal = nota;
		raizArvoreAVL->posicao = posicao;
		raizArvoreAVL->direita = NULL;
		raizArvoreAVL->esquerda = NULL;
		raizArvoreAVL->pai = NULL;

	}else {
		
        ArvoreAVL *pai;
		ArvoreAVL *filho;
		
		
		pai = raizArvoreAVL;
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
		
		
        filho = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
		memset(filho, 0, sizeof(ArvoreAVL)); 
		filho->iNotaFiscal = nota;
		filho->posicao = posicao;
		filho->direita = NULL;
		filho->esquerda = NULL;

		
		filho->pai = pai;
		if (nota < pai->iNotaFiscal){
			pai->esquerda = filho;
		}else{
			pai->direita = filho;
        }
        
        verificaBalanceamento(pai);
	}
}

void verificaBalanceamento(ArvoreAVL *arvore){
     int alturaDireita, alturaDireita2;
     int alturaEsquerda, alturaEsquerda2;
     int fatorBalanceamento, fatorBalanceamento2;
     while(arvore!= NULL){ 
                          
        alturaDireita = altura(arvore->direita);
        printf("\nAltura Direita: %i",alturaDireita);
        alturaEsquerda = altura(arvore->esquerda);   
        printf("\nAltura Esquerda: %i",alturaEsquerda);     
        fatorBalanceamento = alturaDireita - alturaEsquerda;
        
        if((fatorBalanceamento == 2) || (fatorBalanceamento == -2)){
        
            if(fatorBalanceamento == -2){ 
                alturaEsquerda2 = altura(arvore->esquerda->esquerda);
                alturaDireita2 = altura(arvore->esquerda->direita);
                fatorBalanceamento2 = alturaDireita2 - alturaEsquerda2;
                if(fatorBalanceamento2 == -1){
                    rotacaoSimplesAVLDireita(arvore);
                }
                if(fatorBalanceamento2 == 1){ 
                    rotacaoDuplaAVLDireita(arvore);
                }                      
            }  else{
                alturaEsquerda2 = altura(arvore->direita->esquerda);
                alturaDireita2 = altura(arvore->direita->direita);
                fatorBalanceamento2 = alturaDireita2 - alturaEsquerda2;
                if(fatorBalanceamento2 == 1 ){
                    rotacaoSimplesAVLEsquerda(arvore); 
                }
                if(fatorBalanceamento2 == -1 ){
                    rotacaoDuplaAVLEsquerda(arvore);              
                }           
             }                           
        }
        
        arvore = arvore->pai;                
    }
}

int altura(ArvoreAVL *arvore) {
    int alturaEsquerda = 0, alturaDireita = 0;
    if(arvore == NULL){
              return 0;          
    }else{
          alturaDireita = altura(arvore->direita);
          alturaEsquerda = altura(arvore->esquerda);
          if(alturaDireita>alturaEsquerda){
                                          return alturaDireita + 1;                                
          }else{
                return alturaEsquerda + 1;
          }      
    }
}


void rotacaoSimplesAVLDireita(ArvoreAVL *arvore){
     printf("Entrou DIREITA\n");

     ArvoreAVL *filhoEsquerda = arvore->esquerda;
     ArvoreAVL *netoDireita = filhoEsquerda->direita;
     
     filhoEsquerda->direita = arvore;   

     if(arvore->pai != NULL){
       if(arvore == arvore->pai->esquerda){
          arvore->pai->esquerda = filhoEsquerda;
       }else{
          arvore->pai->direita = filhoEsquerda;
       }     
     }
     
     filhoEsquerda->pai = arvore->pai;
     arvore->pai = filhoEsquerda;
     
     arvore->esquerda = netoDireita;
     
     if(arvore == raizArvoreAVL){
        raizArvoreAVL = filhoEsquerda;
             }
     arvore = filhoEsquerda;
}

void rotacaoSimplesAVLEsquerda(ArvoreAVL *arvore){
     printf("Entrou ESQUERDA \n");
     
     ArvoreAVL *filhoDireita = arvore->direita;
     ArvoreAVL *netoEsquerda = filhoDireita->esquerda;
     
     filhoDireita->esquerda = arvore;

     if(arvore->pai != NULL){
       if(arvore == arvore->pai->esquerda){
          arvore->pai->esquerda = filhoDireita;
       }else{
          arvore->pai->direita = filhoDireita;
       }
     }
     
     filhoDireita->pai = arvore->pai;
     arvore->pai = filhoDireita;
     arvore->direita = netoEsquerda;
     
     if(arvore == raizArvoreAVL){
        raizArvoreAVL = filhoDireita;
        
     }
     arvore = filhoDireita;
}

void rotacaoDuplaAVLDireita(ArvoreAVL *arvore) {
      printf("Entrou DUPLA DIREITA \n");
     rotacaoSimplesAVLEsquerda(arvore->esquerda);
     rotacaoSimplesAVLDireita(arvore);
     
}

void rotacaoDuplaAVLEsquerda(ArvoreAVL *arvore) {
      printf("Entrou DUPLA ESQUERDA \n");
     rotacaoSimplesAVLDireita(arvore->direita);
     rotacaoSimplesAVLEsquerda(arvore);
}

void imprimeArvoreAVL(ArvoreAVL *arvore){
     
	if (arvore != NULL) {
       imprimeArvoreAVL(arvore->esquerda);
       printf("Nota Fiscal=%i \n", arvore->iNotaFiscal);
	   imprimeArvoreAVL(arvore->direita);          
	}    
}



void pesquisaNotaAVL (char nomeArquivo[50]){
     FILE *arquivo;
     arquivo = fopen(nomeArquivo,"rb");          
     int nota;
     clock_t inicio,fim;
     qtdComparacaoAVL = 0;
     printf ("Digite o numero da Nota Fiscal a ser pesquisada com AVL: ");
     scanf ("%i", &nota);
     
     inicio = clock();
     pesquisaAVL(arquivo, nota, raizArvoreAVL);
     fim = clock();  
     printf("\n\nPara a Busca da nota foram necessarias %i comparacoes e demorou %f segundos\n", qtdComparacaoAVL,(float)(fim - inicio) / CLOCKS_PER_SEC);  
     fclose(arquivo);
} 

void pesquisaAVL(FILE *arquivo, int nota, ArvoreAVL *noArvore){
       
       NF notaFiscal;
        
       if(noArvore!=NULL){          
           qtdComparacaoAVL++;
           if(noArvore->iNotaFiscal == nota){                    
               fseek(arquivo, noArvore->posicao, SEEK_SET);
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
                     pesquisaAVL(arquivo, nota, noArvore->esquerda);
                  }
           }
           
           if(nota > noArvore->iNotaFiscal){
               if(noArvore->direita !=NULL){
                   pesquisaAVL(arquivo, nota, noArvore->direita);
               }
           }                
       }
         
       
 }
 
void limpaMemoria(ArvoreAVL *arvore){
     
	if (arvore != NULL) {
		limpaMemoria(arvore->esquerda);
		limpaMemoria(arvore->direita);
        free(arvore);

	}
}

int main(){
          
    arvoveAVL("notaFiscal.bin");
    pesquisaNotaAVL("notaFiscal.bin");
    
    system("pause");
    return 0;    
}
