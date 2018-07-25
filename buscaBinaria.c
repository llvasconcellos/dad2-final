#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "notaFiscal.h"
#include "indiceNota.h"

int qtdNotas;
PK_NF *vet;

void lerBinario(){
     
     FILE *arquivo;
     PK_NF notaFiscal;
     int i;
     int tamanho, contador;
     
     arquivo = fopen("notaFiscalInd.bin","r+b");
     if(!arquivo){
           printf("\n\nArquivo nao encontrado.\n\n");
           system("PAUSE");
     }else{
           
           fseek(arquivo, 0, SEEK_END);
           tamanho = ftell(arquivo);
           qtdNotas = tamanho / sizeof(notaFiscal);
           vet = (PK_NF*)malloc(sizeof(PK_NF)*qtdNotas);
           memset(vet, 0, sizeof(PK_NF));
                          
           fseek(arquivo, 0, SEEK_SET);               
           for(i=0; i<qtdNotas-1 ; i++){
                    fread(&notaFiscal,sizeof(notaFiscal),1,arquivo);
                    vet[i] = notaFiscal;                                    
           }
     }  
     fclose(arquivo);        
}

void buscaBinaria(char nomeArquivoIndice[50], char nomeArquivo[50]){
     qtdComparacao = 0; 
     clock_t inicio,fim;
     int notaFiscal, posicao, i, qtdRegistros;
     qtdRegistros = contaRegistros("notaFiscal.bin");
     PK_NF *indice;
     indice = (PK_NF*) malloc (contaRegistros("notaFiscal.bin") * sizeof(PK_NF));
     PK_NF indiceAuxiliar;
     FILE *arquivoIndice;
     arquivoIndice = fopen (nomeArquivoIndice,"r+b");
     if(!arquivoIndice){
                 printf("Não foi possivel abrir o arquivo de indice(buscaBinaria)");
                 system("pause");
     }else{
           for (i=0;i<qtdRegistros;i++){
               fread(&indiceAuxiliar,sizeof(indiceAuxiliar),1,arquivoIndice);
               indice[i].iNotaFiscal = indiceAuxiliar.iNotaFiscal;
               indice[i].pos = indiceAuxiliar.pos;   
           }
           printf("Digite o codigo da Nota Fiscal: ");
           scanf("%i", &notaFiscal);
           inicio = clock();
           realizaBuscaBinaria(indice, notaFiscal, 0, qtdRegistros - 1, nomeArquivo);
           fim = clock();
           printf("Para realizar a busca foram necessarias %i comparacoes\n",qtdComparacao);
           printf("Foram gastos %f segundos!\n\n", (float)(fim - inicio) / CLOCKS_PER_SEC);
     }
     fclose(arquivoIndice);
     system("PAUSE");
}


void realizaBuscaBinaria(PK_NF *indice, int notaFiscal, int inicio, int final, char nomeArquivo[50]){
     
     int posicao;
     qtdComparacao++;
     posicao = (inicio + final) / 2;
     if(inicio > final){
                       printf("\n\nNota Fiscal nao encontrada!!!\n\n");
                       }else{
     if(indice[posicao].iNotaFiscal == notaFiscal){
                                    FILE *arquivo;
                                    NF nota;
                                    arquivo = fopen (nomeArquivo,"rb");
                                    fseek(arquivo, indice[posicao].pos * sizeof(nota), SEEK_SET);
                                    fread(&nota, sizeof(nota), 1, arquivo);
                                    printf("Nota Fiscal Encontrada!!! \n\n");
                                    printf("Numero: %i\n", nota.iNotaFiscal);
                                    printf("Cliente: %s\n", nota.sCliente); 
                                    printf("Data de Emissao: %s\n", nota.sDatEmis);
                                    printf("Condicao de Pagamento: %s\n\n", nota.sDesCondPgto) ;
                                    fclose(arquivo);
     }
     if(indice[posicao].iNotaFiscal > notaFiscal){
                                    realizaBuscaBinaria(indice, notaFiscal, inicio, posicao - 1, nomeArquivo);                                                                                          
     }
     if(indice[posicao].iNotaFiscal < notaFiscal){
                                    realizaBuscaBinaria(indice, notaFiscal, posicao + 1, final, nomeArquivo);                                                                                          
     }
     }
     free(indice);
}

int main(){
    
    
    
    system("pause");
    return 0;    
}
