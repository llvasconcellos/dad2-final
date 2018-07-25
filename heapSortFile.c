#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "notaFiscal.h"
#include "indiceNota.h"

int qtdNotas;
FILE *arquivo;
 
int left(int index){
    return ((2*index)+1);
}
 
int right(int index){
    return ((2*index)+2);
}
 
void swap(PK_NF a, PK_NF b){
    fseek(arquivo, 0, SEEK_CUR);
    fwrite(&b,sizeof(b),1,arquivo);
    fwrite(&a,sizeof(a),1,arquivo);
}
 
void heapfy(int tamvet, int index){
    int e = left(index);
    int d = right(index);
    int maior = index;
    if(e < tamvet && vet[e].iNotaFiscal> vet[maior].iNotaFiscal)
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
     for(i=tamvet; i > 0; i--){
          fread(&)         
          swap(i,0);
          tamvet--;
          heapfy(tamvet+1, 0);
     }
}
 
int main(){
    int i;
    clock_t inicio,fim;
        
    PK_NF notaFiscal;
    int i;
        
    arquivo = fopen("notaFiscalInd.bin","r+b");
    if(!arquivo){
                  printf("\n\nArquivo nao encontrado.\n\n");
                  system("PAUSE");
    }else{
          fseek(arquivo, 0, SEEK_END);
          tamanho = ftell(arquivo);
          qtdNotas = tamanho / sizeof(notaFiscal);
          
          fseek(arquivo, 0, SEEK_SET);        
          inicio = clock();
          heapSort();
          fim = clock();        
    }  
    
    fclose(arquivo);  
        
    printf("\nForam gastos %f segundos!\n\n", (float)(fim - inicio) / CLOCKS_PER_SEC);    
    system("pause");
    return 0;
}
