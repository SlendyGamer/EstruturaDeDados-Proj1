#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "Filalib.h"


int IDvalido(char ID[]);  //prototipo



int main()
{
    setlocale(LC_ALL,"portuguese");                                     //identifica linguagem
    srand(SEED);                                                        //semeia as fun��es rand com a SEED definida em Filalib.h

    int passageiros;                                                    //inicia vari�veis
    int sel, time;
    char ID[6] = {0};
    char whichFila;
    voo novoVoo;                                                        //incia variavel do tipo Struct Voo
    fila *comum = fila_criar();
    fila *emergencia = fila_criar();                                    //inicia as 3 filas
    fila *realizados = fila_criar();
    if (comum == NULL || emergencia == NULL || realizados == NULL)
    {
        printf(RED "\tfilas n�o inicializadas corretamente! abortando programa!" CRESET);    //se alguma fila n�o for inicializada, aborta o programa
        exit(0);
    }
    data horarioAtual = setHorarioAtual();                              //define um hor�rio atual aleat�rio
    do
    {
        sel = -1;
        system("cls");                                                  //limpa terminal toda vez que uma fun��o � executada e o menu precisa ser impresso novamente
        printf("\n\thorario atual: "); showHorario(horarioAtual);       //mostra o horario atual
        printf("\n\n\tTorre de Controle Luc.I airport\n\n");
        printMenu();                                                    //printa o menu de sele��o principal
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
                    printf("\tDIGITE O C�DIGO DO VOO(4 CARACTERES ALFANUM�RICOS)\n"
                           YELLOW "\tEM CASO DE EMERG�NCIA, INSIRA '!' NO FINAL:\n" CRESET);
                           printf(CYAN "\n     /: ");
                    for (int i=0; i<5; i++)
                    {
                        ID[i] = getchar();                              //le os proximos 5 caracteres digitados
                    }
                    fflush(stdin);
                    printf(CRESET);
                } while (!IDvalido(ID) || fila_duplicata(comum, ID) || fila_duplicata(emergencia, ID)); //checa se ID � valido e se ele n�o � repetido nas filas de voos que ainda n�o pousaram
                strcpy(novoVoo.ID, strupr(ID));                         //atribui valores do voo e transforma os caracteres alfabeticos em MAIUSCULO
                novoVoo.passageiros = setPassageiros();
                novoVoo.hora_prevista = setHoraPrevista(horarioAtual);
                printf(GREEN "\n\tVOO %.*s INSERIDO COM SUCESSO NA FILA ", 4, novoVoo.ID);     //%.*s   recebe o argumento 4 e imprime os primeiros 4 caracteres do char[] ID

                if (ID[4] == '!')                                                    //se 5 elemento for '!', define como voo de emergencia
                {
                   printf("EMERGENCIAL\n\n");
                   novoVoo.status = -1;
                   fila_inserirVoo(emergencia, novoVoo);
                }
                else                                                                 //se 5 elemento for qualquer outra coisa, ignora-lo
                {
                    printf("COMUM\n\n");
                    if (estaAtrasado(horarioAtual, novoVoo.hora_prevista))
                    {
                        novoVoo.status = 0;         //atrasado
                    }
                    else
                    {
                        novoVoo.status = 1;         //n�o atrasado
                    }
                    fila_inserirVoo(comum, novoVoo);
                }
                printf(CRESET);
                printf("\tSTATUS DO VOO: ");
                showStatus(novoVoo.status);         //imprime se esta atrasado, se � emergencia ou se esta no horario
                printf(MAGENTA);
                system("pause");    //espera input
                printf(CRESET);
                break;
            case 2:
                if (!fila_vazia(emergencia))
                {
                    printf(GREEN "\tVOO DE EMERG�NCIA LIBERADO PARA ATERRISSAGEM!\n\n" CRESET);
                    fila_printNextInfo(emergencia, 0);
                    fila_inserirVoo(realizados, fila_retirarVoo(emergencia));       //libera prox voo emergencial
                    printf("\tHOR�RIO DE LIBERA��O: ");
                        showHorario(horarioAtual);
                    horarioAtual = addHora(horarioAtual, (10 + rand() % 5));        //soma valor entre 10|-14 nos minutos(para variar um pouco o tempo)
                }
                else if (!fila_vazia(comum))
                {
                    printf(GREEN "\tVOO COMUM LIBERADO PARA ATERRISSAGEM!\n\n" CRESET);
                    fila_printNextInfo(comum, 0);
                    fila_inserirVoo(realizados, fila_retirarVoo(comum));            //libera prox voo emergencial
                    printf("\tHOR�RIO DE LIBERA��O: ");
                        showHorario(horarioAtual);
                    horarioAtual = addHora(horarioAtual, (10 + rand() % 5));        //soma valor entre 10|-14 nos minutos(para variar um pouco o tempo)
                }
                else
                {
                    printf(YELLOW "\tN�O H� VOOS PARA LIBERAR!\n" CRESET);
                }
                printf("\n");
                printf(MAGENTA);
                system("pause");    //espera input
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
                        fila_printAllInfo(comum, 2);        //printa fila comum toda
                    }
                    else
                    {
                        printf(YELLOW "\n\tFILA COMUM VAZIA!\n\n" CRESET);
                    }
                    break;
                case 'E':
                    if (!fila_vazia(emergencia))
                    {
                        printf("\n\tFILA EMERGENCIAL:\n\n");    //printa fila emergencial toda
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
                system("pause");    //espera input
                printf(CRESET);
                break;
            case 4:
                if (!fila_vazia(emergencia))
                {
                    printf("\tPR�XIMA AERONAVE A SER LIBERADA:\n\n");
                    fila_printNextInfo(emergencia, 1);                  //printa proximo voo emergencial
                }
                else if (!fila_vazia(comum))
                {
                    printf("\tPR�XIMA AERONAVE A SER LIBERADA:\n\n");
                    fila_printNextInfo(comum, 1);                       //printa proximo voo comum
                }
                else
                {
                    printf(YELLOW "\tTODAS AS FILAS EST�O VAZIAS!\n\n" CRESET);
                }
                printf(MAGENTA);
                system("pause");    //espera input
                printf(CRESET);
                break;
            case 5:
                if (!fila_vazia(realizados))
                {
                    printf("\n\tPOUSOS REALIZADOS:\n\n");
                    fila_printAllInfo(realizados, 0);                   //printa fila de voos realizados toda
                }
                else
                {
                    printf(YELLOW "\tNENHUM POUSO REALIZADO AINDA!\n\n" CRESET);
                }
                printf(MAGENTA);
                system("pause");    //espera input
                printf(CRESET);
                break;
            case 6:
                if (fila_vazia(comum) && fila_vazia(emergencia))
                {
                    printf(YELLOW "\tN�O H� VOOS AGUARDANDO LIBERA��O\n\n" CRESET);
                }
                else
                {
                    do
                    {
                        time = 0;
                        printf("\tDIGITE O TEMPO(MINUTOS) PARA A SIMULA��O DE POUSO\n\n");
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
                        printf("\n\tVOOS LIBERADOS EM %d MINUTOS:\n\n", time);        //se tempo for maior que 0, printa pelo menos um voo que sera liberado "imediatamente" e mais 1 para cada 10 min
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
    fila_liberar(emergencia);   //libera as filas
    fila_liberar(realizados);
    return 0;
}


int IDvalido(char ID[])
{
    for (int i=0; i<4; i++)      //percorre primeiros 4 caracteres
    {
        if (!isalnum(ID[i]))     //se nao for puramente alfanumerico, � invalido
        {
            printf(YELLOW "\n\tID invalido, utilizar 4 caracteres alfanum�ricos e finalizar 5� com '!' para emerg�ncia!\n\n" CRESET);
            return 0;
        }
    }
    return 1;                    //id aceito
}

