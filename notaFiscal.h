#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct _NF{
        int iNotaFiscal; // chave primaria      n�mero da nota fiscal
        char sCliente[20]; // chave secundaria       cliente da nota fiscal
        char sDatEmis[11]; // chave secundaria       data de emiss�o da nota fiscal
        char sDesCondPgto[20]; // Descri��o condi��o de pagamento
} NF;
