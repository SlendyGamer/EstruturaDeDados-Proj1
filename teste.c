#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "Filalib.h"

int main()
{
    char id[6] = {'a', 'b', 'c', 'd', '!', 0};
    fila *voo = fila_criar();
    if (voo == NULL)
    {
        printf("filas não inicializadas corretamente! abortando programa!");
    }
    for (int i=0; i<=5; i++)
        printf("%c", id[i]);

    fila_inserirVoo(voo, id, 23, -1);
    fila_printAllInfo(voo);
    fila_liberar(voo);
    return 0;
}
