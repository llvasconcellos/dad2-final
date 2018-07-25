#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "notaFiscal.h"
#include "indiceNota.h"

void geraBinario(char nomeArquivoImportacao[50], char nomeArquivoGravacao[50]){
     clock_t inicio,fim;
     FILE *arquivoImportacao, *arquivoGravacao;
     arquivoImportacao = fopen(nomeArquivoImportacao,"r");
     arquivoGravacao = fopen(nomeArquivoGravacao,"a+b");
     NF notaFiscal;
     char nota[4][20];
     int contador=0;
     char caracter[100], numeroNota[100];
     int numero;
     int qtdNotas = 0;
     char *dadosNotaFiscal;
          
     if(!arquivoImportacao){
                            printf("Erro ao abrir arquivo (importaDadosArquivo)");
                            system("PAUSE");
                            }else{
     inicio = clock();
     while(!feof(arquivoImportacao)){
                                     
                  //Realiza a leitura de 1 linha no arquivo de importacao
                  fgets(caracter, 100, arquivoImportacao);
                  dadosNotaFiscal = strtok (caracter,"|");
                    do
                    {
                          
                          switch(contador){
                                          case 0:                     
                                                numero = atoi(dadosNotaFiscal);
                                                notaFiscal.iNotaFiscal = numero;                
                                          break;
                                          case 1:
                                               
                                               memcpy(notaFiscal.sCliente,dadosNotaFiscal, sizeof(notaFiscal.sCliente));  
                                          case 2:
                                               
                                               memcpy(notaFiscal.sDatEmis,dadosNotaFiscal, sizeof(notaFiscal.sDatEmis));
                                          break;
                                          case 3:
                                               
                                               memcpy(notaFiscal.sDesCondPgto, dadosNotaFiscal, sizeof(notaFiscal.sDesCondPgto));
                                               
                                               fwrite(&notaFiscal,sizeof(notaFiscal),1,arquivoGravacao);  
                                               printf("\nNota Fiscal nr. %i INCLUIDA com sucesso!!!\n\n",notaFiscal.iNotaFiscal);
                                               system("cls");
                                          break;
                                          case 4:
                                               contador = -1;
                                          break;                                    
                     }
                     contador++;
                     dadosNotaFiscal = strtok (NULL, "|");
                  }while (dadosNotaFiscal != NULL);
                  qtdNotas++;
     }
     fim = clock();
     printf("O tempo necessario para importar as %i notas foi de %.2f segundos\n\n", qtdNotas, (float)(fim - inicio) / CLOCKS_PER_SEC );
     
     fclose(arquivoImportacao);
     fclose(arquivoGravacao);
     }
}

void geraBinarioIndice(char nomeArquivoImportacao[50], char nomeArquivoGravacao[50]){

     clock_t inicio,fim;
     FILE *arquivoImportacao, *arquivoGravacao;
     arquivoImportacao = fopen(nomeArquivoImportacao,"r");
     arquivoGravacao = fopen(nomeArquivoGravacao,"a+b");
     PK_NF notaFiscal;
     char nota[4][20];
     int contador=0;
     char caracter[100], numeroNota[100];
     int numero;
     fpos_t posicao;
     int qtdNotas = 0;
     char *dadosNotaFiscal;
     
     if(!arquivoImportacao){
                            printf("Erro ao abrir arquivo (importaDadosArquivo)");
                            system("PAUSE");
     }
     else{
         inicio = clock();
         while(!feof(arquivoImportacao)){
                                     
                  fgets(caracter, 100, arquivoImportacao);
                  fgetpos(arquivoImportacao, &posicao);
                  
                  notaFiscal.iNotaFiscal = atoi(caracter);
                  notaFiscal.pos = posicao;
                  
                  fseek(arquivoGravacao, 0, SEEK_END);
                  fwrite(&notaFiscal,sizeof(PK_NF),1,arquivoGravacao);
                  
                  qtdNotas++;
         }
         fim = clock();
         printf("O tempo necessario para importar os indices de %i notas foi de %.2f segundos\n\n", qtdNotas, (float)(fim - inicio) / CLOCKS_PER_SEC );
         fclose(arquivoImportacao);
         fclose(arquivoGravacao);
     }
     
}


int main(){

    geraBinario("NF.txt", "notaFiscal.bin");    
    geraBinarioIndice("NF_BUSCAS.txt", "notaFiscalInd.bin");
    
    system("pause");
    return 0;    
}
