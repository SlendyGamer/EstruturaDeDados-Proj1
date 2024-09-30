#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "filalib.h"

int main()
{
    int minutos;

    srand(SEED);

        minutos = rand()%1440;

        //printf("Minutos: %d\n", minutos); Horario em minutos

        if(minutos % 60 < 10){
            printf("Horario: %0.fh0%d\n\n", floor(minutos/60), minutos % 60); //printar o 0 antes do minuto se ele for entre 0 e 9 (pra ficar bonitinho)
        }else{
            printf("Horario: %0.fh%d\n\n", floor(minutos/60), minutos % 60);
        }
    return 0;
}
