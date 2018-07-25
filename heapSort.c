#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "notaFiscal.h"
#include "indiceNota.h"

int qtdNotas;
NF *vet;

void lerBinario(){
     
     FILE *arquivo;
     NF notaFiscal;
     int i;
     int tamanho, contador;
               
     arquivo = fopen("notaFiscal.bin","r+b");
     if(!arquivo){
                  printf("\n\nArquivo nao encontrado.\n\n");
                  system("PAUSE");
     }else{
           
           fseek(arquivo, 0, SEEK_END);
           tamanho = ftell(arquivo);
           contador = tamanho / sizeof(notaFiscal);
           qtdNotas = contador;
           
           vet = (NF*)malloc(sizeof(NF) * qtdNotas);
           memset(vet, 0, sizeof(NF));
                          
           fseek(arquivo, 0, SEEK_SET);               
           for(i=0; i < qtdNotas-1 ; i++){
                    fread(&notaFiscal,sizeof(notaFiscal),1,arquivo);
                    vet[i] = notaFiscal;                                
           }
     }  
     fclose(arquivo);        
}
 
int left(int index){
    return ((2*index)+1);
}
 
int right(int index){
    return ((2*index)+2);
}
 
void swap(int a, int b){
    NF aux = vet[a];
    vet[a] = vet[b];
    vet[b] = aux;
}
 
void heapfy(int tamvet, int index){
    int e = left(index);
    int d = right(index);
    int maior = index;
    if(e < tamvet && vet[e].iNotaFiscal > vet[maior].iNotaFiscal)
        maior = e;
    if(d < tamvet && vet[d].iNotaFiscal > vet[maior].iNotaFiscal)
        maior = d;
    if(maior != index){
        swap(index, maior);
        heapfy(tamvet, maior);
    }
}
 
void buildHeap(){
     int i;
     int aux = (10/2)-1;
     for(i=aux; i >= 0; i--)
         heapfy(10, i);
}
 
void heapSort(){
     int i;
     buildHeap();
     int tamvet = qtdNotas-2;
     for(i = tamvet; i > 0; i--){
          swap(i,0);
          tamvet--;
          heapfy(tamvet+1, 0);
     }
}
 
int main(){
    int i;
    clock_t inicio,fim;

    lerBinario();
    
    inicio = clock();
    heapSort();
    fim = clock();
    
    for(i = 0; i < qtdNotas; i++)
        printf("Nota: %i \n", vet[i].iNotaFiscal);
        
    printf("\nForam gastos %f segundos!\n\n", (float)(fim - inicio) / CLOCKS_PER_SEC);    
    system("pause");
    return 0;
}
