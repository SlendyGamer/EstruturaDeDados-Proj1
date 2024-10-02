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
    char whichFila;
    data horarioAtual = setHorarioAtual();
    voo novoVoo;
    //data horarioPrevisto;       //ao inves disso tudo, criar um struct voo
    fila *comum = fila_criar();
    fila *emergencia = fila_criar();
    fila *realizados = fila_criar();
    if (comum == NULL || emergencia == NULL /*|| realizados == NULL */)
    {
        printf("filas não inicializadas corretamente! abortando programa!");
        exit(0);
    }
    do
    {
        printf("\n\n\t\tTorre de Controle LucI airport\n\n");
        printf("\thorario atual: ");
        showHorario(horarioAtual);
        printMenu();
        scanf("%d", &sel);
        fflush(stdin);
        switch(sel)
        {
            case 1:
                do
                {
                    printf("\ninsira codigo alfanumerico do voo (4 caracteres) e insira '!' no fim se for emergencial: ");
                    for (int i=0; i<5; i++)
                    {
                        ID[i] = getchar();
                    }
                    fflush(stdin);
                } while (!IDvalido(ID)); // || procura por id igual nas filas   || fila_duplicata(comum, ID) || fila_duplicata(emergencia, ID)

                strcpy(novoVoo.ID, ID);
                novoVoo.passageiros = setPassageiros();
                novoVoo.hora_prevista = setHoraPrevista(horarioAtual);
                printf("voo %.*s\n"
                       "passageiros: %d\n"
                       "hora_prevista: ", 4, novoVoo.ID, novoVoo.passageiros);
                       showHorario(novoVoo.hora_prevista);
                printf("status: ");

                if (ID[4] == '!')
                {
                   novoVoo.status = -1;
                   fila_inserirVoo(emergencia, novoVoo);
                   printf("emergencia");
                }
                else
                {
                    if (estaAtrasado(horarioAtual, novoVoo.hora_prevista))
                    {
                        novoVoo.status = 0;
                        fila_inserirVoo(comum, novoVoo);
                        printf("no horario");
                    }
                    else
                    {
                        novoVoo.status = 1;
                        fila_inserirVoo(comum, novoVoo);
                        printf("atrasado");
                    }
                }
                break;
            case 2:
                if (!fila_vazia(emergencia))
                {
                    fila_printNextInfo(emergencia);
                    fila_inserirVoo(realizados, fila_retirarVoo(emergencia));
                }
                else
                {
                    fila_printNextInfo(comum);
                    fila_inserirVoo(realizados, fila_retirarVoo(comum));
                }
                horarioAtual = addHora(horarioAtual, 10);
                break;
            case 3:

                do
                {
                scanf("%c", &whichFila);
                whichFila = toupper(whichFila);
                } while(whichFila != 'C' && whichFila != 'E');
                switch(whichFila)
                {
                case 'C':
                    fila_printAllInfo(comum);
                    break;
                case 'E':
                    fila_printAllInfo(emergencia);
                    break;
                default:
                    break;
                }
                break;
            case 4:
                if (!fila_vazia(emergencia))
                {
                    fila_printNextInfo(emergencia);
                }
                else if (!fila_vazia(comum))
                {
                    fila_printNextInfo(comum);
                }
                else
                {
                    printf("todas as filas estão vazias!\n");
                }
                break;
            case 5:
                if (!fila_vazia(realizados))
                {
                    fila_printAllInfo(realizados);
                }
                else
                {
                    printf("nenhum pouso ocorreu");
                }
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
    fila_liberar(realizados);
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

