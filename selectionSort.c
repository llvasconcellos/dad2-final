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


int main(){
    lerBinario();
    int tamvet = qtdNotas;
    int inivet = 1;
    int posmenor = 0;
    int aux = 0, i;
    clock_t inicio,fim;
    
    inicio = clock();
    for(aux = 0; aux<tamvet-1; aux++){
        for(i = inivet; i<tamvet; i++){
            if(vet[posmenor].iNotaFiscal>vet[i].iNotaFiscal)
                posmenor = i;
        }
        inivet++;
        PK_NF value = vet[posmenor];
        vet[posmenor] = vet[aux];
        vet[aux] = value;
        posmenor = inivet;
    }
    fim = clock();
    
    for(i=0;i<tamvet;i++){
        printf("%i\n",vet[i].iNotaFiscal);
    }
    
    printf("\nForam gastos %f segundos!\n\n", (float)(fim - inicio) / CLOCKS_PER_SEC); 
    
    free(vet);
    system("pause");
    return 0;
}
