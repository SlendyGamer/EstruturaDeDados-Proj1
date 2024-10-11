#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "Filalib.h"


int IDvalido(char ID[]);



int main()
{
    setlocale(LC_ALL,"portuguese");
    srand(SEED);

    int passageiros;
    int sel, time;
    char ID[6] = {0};
    char whichFila;
    voo novoVoo;
    fila *comum = fila_criar();
    fila *emergencia = fila_criar();
    fila *realizados = fila_criar();
    if (comum == NULL || emergencia == NULL || realizados == NULL)
    {
        printf(RED "\tfilas não inicializadas corretamente! abortando programa!" CRESET);
        exit(0);
    }
    data horarioAtual = setHorarioAtual();
    do
    {
        sel = -1;
        system("cls");
        printf("\n\thorario atual: "); showHorario(horarioAtual);
        printf("\n\n\tTorre de Controle Luc.I airport\n\n");
        printMenu();
        printf(CYAN "\n     /: ");
        scanf("%d", &sel);
        printf(CRESET);
        fflush(stdin);
        system("cls");
        switch(sel)
        {
            case 1:
                do
                {
                    printf("\tDIGITE O CÓDIGO DO VOO(4 CARACTERES ALFANUMÉRICOS)\n"
                           YELLOW "\tEM CASO DE EMERGÊNCIA, INSIRA '!' NO FINAL:\n" CRESET);
                           printf(CYAN "\n     /: ");
                    for (int i=0; i<5; i++)
                    {
                        ID[i] = getchar();
                    }
                    fflush(stdin);
                    printf(CRESET);
                } while (!IDvalido(ID) || fila_duplicata(comum, ID) || fila_duplicata(emergencia, ID));
                strcpy(novoVoo.ID, strupr(ID));
                novoVoo.passageiros = setPassageiros();
                novoVoo.hora_prevista = setHoraPrevista(horarioAtual);
                printf(GREEN "\n\tVOO %.*s INSERIDO COM SUCESSO NA FILA ", 4, novoVoo.ID);

                if (ID[4] == '!')
                {
                   printf("EMERGENCIAL\n\n");
                   novoVoo.status = -1;
                   fila_inserirVoo(emergencia, novoVoo);
                }
                else
                {
                    printf("COMUM\n\n");
                    if (estaAtrasado(horarioAtual, novoVoo.hora_prevista))
                    {
                        novoVoo.status = 0;
                    }
                    else
                    {
                        novoVoo.status = 1;
                    }
                    fila_inserirVoo(comum, novoVoo);
                }
                printf(CRESET);
                printf("\tSTATUS DO VOO: ");
                showStatus(novoVoo.status);
                printf(MAGENTA);
                system("pause");
                printf(CRESET);
                break;
            case 2:
                if (!fila_vazia(emergencia))
                {
                    printf(GREEN "\tVOO DE EMERGÊNCIA LIBERADO PARA ATERRISSAGEM!\n\n" CRESET);
                    fila_printNextInfo(emergencia, 0);
                    fila_inserirVoo(realizados, fila_retirarVoo(emergencia));
                    printf("\tHORÁRIO DE LIBERAÇÃO: ");
                        showHorario(horarioAtual);
                    horarioAtual = addHora(horarioAtual, (10 + rand() % 5));
                }
                else if (!fila_vazia(comum))
                {
                    printf(GREEN "\tVOO COMUM LIBERADO PARA ATERRISSAGEM!\n\n" CRESET);
                    fila_printNextInfo(comum, 0);
                    fila_inserirVoo(realizados, fila_retirarVoo(comum));
                    printf("\tHORÁRIO DE LIBERAÇÃO: ");
                        showHorario(horarioAtual);
                    horarioAtual = addHora(horarioAtual, (10 + rand() % 5));
                }
                else
                {
                    printf(YELLOW "\tNÃO HÁ VOOS PARA LIBERAR!\n" CRESET);
                }
                printf("\n");
                printf(MAGENTA);
                system("pause");
                printf(CRESET);
                break;
            case 3:
                do
                {
                    printf("\tQue fila deseja visualizar?\n");
                    printf("\tC - Comum\n");
                    printf("\tE - Emergencial\n");
                    printf(CYAN "\n     /: ");
                scanf("%c", &whichFila);
                printf(CRESET);
                fflush(stdin);
                whichFila = toupper(whichFila);
                switch(whichFila)
                {
                case 'C':
                    if (!fila_vazia(comum))
                    {
                        printf("\n\tFILA COMUM:\n\n");
                        fila_printAllInfo(comum, 2);
                    }
                    else
                    {
                        printf(YELLOW "\n\tFILA COMUM VAZIA!\n\n" CRESET);
                    }
                    break;
                case 'E':
                    if (!fila_vazia(emergencia))
                    {
                        printf("\n\tFILA EMERGENCIAL:\n\n");
                        fila_printAllInfo(emergencia, 2);
                    }
                    else
                    {
                        printf(YELLOW "\n\tFILA EMERGENCIAL VAZIA!\n\n" CRESET);
                    }
                    break;
                default:
                    system("cls");
                    printf(RED "\tErro de Input\n\n" CRESET);
                    printf(MAGENTA);
                    system("pause");
                    printf(CRESET);
                    system("cls");
                    break;
                }
                } while(whichFila != 'C' && whichFila != 'E');
                printf(MAGENTA);
                system("pause");
                printf(CRESET);
                break;
            case 4:
                if (!fila_vazia(emergencia))
                {
                    printf("\tPRÓXIMA AERONAVE A SER LIBERADA:\n\n");
                    fila_printNextInfo(emergencia, 1);
                }
                else if (!fila_vazia(comum))
                {
                    printf("\tPRÓXIMA AERONAVE A SER LIBERADA:\n\n");
                    fila_printNextInfo(comum, 1);
                }
                else
                {
                    printf(YELLOW "\tTODAS AS FILAS ESTÃO VAZIAS!\n\n" CRESET);
                }
                printf(MAGENTA);
                system("pause");
                printf(CRESET);
                break;
            case 5:
                if (!fila_vazia(realizados))
                {
                    printf("\n\tPOUSOS REALIZADOS:\n\n");
                    fila_printAllInfo(realizados, 0);
                }
                else
                {
                    printf(YELLOW "\tNENHUM POUSO REALIZADO AINDA!\n\n" CRESET);
                }
                printf(MAGENTA);
                system("pause");
                printf(CRESET);
                break;
            case 6:
                if (fila_vazia(comum) && fila_vazia(emergencia))
                {
                    printf(YELLOW "\tNÃO HÁ VOOS AGUARDANDO LIBERAÇÃO\n\n" CRESET);
                }
                else
                {
                    do
                    {
                        time = 0;
                        printf("\tDIGITE O TEMPO(MINUTOS) PARA A SIMULAÇÃO DE POUSO\n\n");
                        printf(CYAN "\n     /: ");
                        scanf("%d", &time);
                        printf(CRESET);
                        fflush(stdin);
                        if (time <= 0)
                        {
                            system("cls");
                            printf(RED "\tErro de Input\n\n" CRESET);
                            printf(MAGENTA);
                            system("pause");
                            printf(CRESET);
                            system("cls");
                        }
                    } while (time <= 0);
                        printf("\n\tVOOS LIBERADOS EM %d MINUTOS:\n\n", time);
                        time /= (int) 10;
                        //time++;
                        printQuant(comum, emergencia, time);
                }
                printf(MAGENTA);
                system("pause");
                printf(CRESET);
                break;
            case 0:
                printf(YELLOW "\n\tSaindo" CRESET);
                break;
            default:
                system("cls");
                printf(RED "\tErro de Input\n\n" CRESET);
                printf(MAGENTA);
                system("pause");
                printf(CRESET);
                system("cls");
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
            printf(YELLOW "\n\tID invalido, utilizar 4 caracteres alfanuméricos e finalizar 5º com '!' para emergência!\n\n" CRESET);
            return 0;
        }
    }
    return 1;
}

