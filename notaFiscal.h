#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct _NF{
        int iNotaFiscal; // chave primaria      número da nota fiscal
        char sCliente[20]; // chave secundaria       cliente da nota fiscal
        char sDatEmis[11]; // chave secundaria       data de emissão da nota fiscal
        char sDesCondPgto[20]; // Descrição condição de pagamento
} NF;
