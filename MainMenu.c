#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "Filalib.h"

int IDvalido(char ID[]);  //prototipo



int main()
{
    setlocale(LC_ALL,"portuguese");
    srand(SEED);

    int passageiros;
    int sel = 0;
    char ID[6] = {0};
    data horarioAtual = setHorarioAtual();
    data horarioPrevisto;
    fila *comum = fila_criar();
    fila *emergencia = fila_criar();
    //fila *realizados = fila_criar();
    if (comum == NULL || emergencia == NULL /*|| realizados == NULL */)
    {
        printf("filas não inicializadas corretamente! abortando programa!");
        exit(0);
    }
    do
    {
        printMenu();

        scanf("%d", &sel);
        fflush(stdin);
        switch(sel)
        {
            case 1:
                do
                {
                    for (int i=0; i<5; i++)
                    {
                        ID[i] = getchar();
                    }
                    fflush(stdin);
                } while (!IDvalido(ID)); // || procura por id igual nas filas   || fila_duplicata(comum, ID) || fila_duplicata(emergencia, ID)

                passageiros = setPassageiros();
                horarioPrevisto = setHoraPrevista(horarioAtual);

                printf("%d : %d : %d", horarioPrevisto.dias, horarioPrevisto.horas, horarioPrevisto.minutos); //apagar
                showHorario(horarioPrevisto); //apagar

                if (ID[4] == '!')
                {
                   fila_inserirVoo(emergencia, ID, passageiros, -1);
                   printf("emergencia");
                }
                else
                {
                    if (estaAtrasado(horarioAtual, horarioPrevisto))
                    {
                    fila_inserirVoo(comum, ID, passageiros, 0);
                    }
                    else
                    {
                    fila_inserirVoo(comum, ID, passageiros, 1);
                    }
                }
                break;
            case 2:
                 for (int i=0; i<4; i++)
                    {
                        printf("%c\n", ID[i]);
                    }
                fila_printAllInfo(comum);
                fila_printAllInfo(emergencia);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case -1:
                break;
            default:
                system("cls");
                printf("\nErro de Input\n\n");
                system("pause");
        }
    } while (sel != -1);
    fila_liberar(comum);
    fila_liberar(emergencia);
    //fila_liberar(realizados);
    return 0;
}


int IDvalido(char ID[])
{
    for (int i=0; i<4; i++)
    {
        if (!isalnum(ID[i]))
        {
            printf("ID invalido, utilizar 4 caracteres alfanuméricos e finalizar com ! para emergência ou 0 para normal\n");
            return 0;
        }
    }
    return 1;
}

