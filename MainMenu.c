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
    int sel;
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
        system("cls");
        printf("\n\n\t\tTorre de Controle LucI airport\n\n");
        printf("\thorario atual: ");
        showHorario(horarioAtual);
        printMenu();
        scanf("%d", &sel);
        fflush(stdin);
        system("cls");
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
                    fflush(stdin);  //apagar?
                } while (!IDvalido(ID)); // || procura por id igual nas filas   || fila_duplicata(comum, ID) || fila_duplicata(emergencia, ID)
                strcpy(novoVoo.ID, strupr(ID));
                novoVoo.passageiros = setPassageiros();
                novoVoo.hora_prevista = setHoraPrevista(horarioAtual);
                printf("voo %.*s inserido com sucesso na espera ", 4, novoVoo.ID);

                if (ID[4] == '!')
                {
                    printf("emergencial\n");
                   novoVoo.status = -1;
                   fila_inserirVoo(emergencia, novoVoo);
                }
                else
                {
                    printf("comum\n");
                    printf("Status do Voo: ");
                    if (estaAtrasado(horarioAtual, novoVoo.hora_prevista))
                    {
                        novoVoo.status = 0;
                        printf("%d", novoVoo.status);
                    }
                    else
                    {
                        novoVoo.status = 1;
                    }
                    showStatus(novoVoo.status);
                    fila_inserirVoo(comum, novoVoo);
                }
                system("pause");
                break;
            case 2:
                if (!fila_vazia(emergencia))
                {
                    printf("Voo emergencial liberado:\n");
                    fila_printNextInfo(emergencia);
                    fila_inserirVoo(realizados, fila_retirarVoo(emergencia));
                }
                else if (!fila_vazia(comum))
                {
                    printf("Voo comum liberado:\n");
                    fila_printNextInfo(comum);
                    fila_inserirVoo(realizados, fila_retirarVoo(comum));
                }
                else
                {
                    printf("Filas vazias!\n");
                }
                printf("horario de liberação: ");
                    showHorario(horarioAtual);
                horarioAtual = addHora(horarioAtual, 10);
                system("pause");
                break;
            case 3:
                do
                {
                    printf("Que fila deseja visualizar?\n");
                    printf("C - Comum\n");
                    printf("E - Emergencial\n");
                scanf("%c", &whichFila);
                fflush(stdin);
                whichFila = toupper(whichFila);
                } while(whichFila != 'C' && whichFila != 'E');
                switch(whichFila)
                {
                case 'C':
                    if (!fila_vazia(comum))
                    {
                        fila_printAllInfo(comum, 1);
                    }
                    else
                    {
                        printf("Fila comum vazia!\n");
                    }
                    break;
                case 'E':
                    if (!fila_vazia(emergencia))
                    {
                        fila_printAllInfo(emergencia, 1);
                    }
                    else
                    {
                        printf("Fila emergencial vazia!\n");
                    }
                    break;
                default:
                    break;
                }
                system("pause");
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
                system("pause");
                break;
            case 5:
                if (!fila_vazia(realizados))
                {
                    fila_printAllInfo(realizados, 0);
                }
                else
                {
                    printf("Nenhum pouso realizado ainda!\n");
                }
                system("pause");
                break;
            case 6:
                break;
            case 0:
                break;
            default:
                system("cls");
                printf("\nErro de Input\n\n");
                system("pause");
        }
    } while (sel != 0);
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

