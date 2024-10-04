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
    srand(SEED);                                                        //semeia as funções rand com a SEED definida em Filalib.h

    int passageiros;                                                    //inicia variáveis
    int sel, time;
    char ID[6] = {0};
    char whichFila;
    voo novoVoo;                                                        //incia variavel do tipo Struct Voo
    fila *comum = fila_criar();
    fila *emergencia = fila_criar();                                    //inicia as 3 filas
    fila *realizados = fila_criar();
    if (comum == NULL || emergencia == NULL || realizados == NULL)
    {
        printf("filas não inicializadas corretamente! abortando programa!");    //se alguma fila não for inicializada, aborta o programa
        exit(0);
    }
    data horarioAtual = setHorarioAtual();                              //define um horário atual aleatório
    do
    {
        system("cls");                                                  //limpa terminal toda vez que uma função é executada e o menu precisa ser impresso novamente
        printf("\n\thorario atual: "); showHorario(horarioAtual);       //mostra o horario atual
        printf("\n\n\tTorre de Controle Luc.I airport\n\n");
        printMenu();                                                    //printa o menu de seleção principal
        printf("\n/: ");
        scanf("%d", &sel);
        fflush(stdin);
        system("cls");
        switch(sel)
        {
            case 1:
                do
                {
                    printf("\nDIGITE O CÓDIGO DO VOO(4 CARACTERES ALFANUMÉRICOS)\n"
                           "EM CASO DE EMERGÊNCIA, INSIRA '!' NO FINAL:\n");
                           printf("\n/: ");
                    for (int i=0; i<5; i++)
                    {
                        ID[i] = getchar();                              //le os proximos 5 caracteres digitados
                    }
                    fflush(stdin);
                } while (!IDvalido(ID) || fila_duplicata(comum, ID) || fila_duplicata(emergencia, ID)); //checa se ID é valido e se ele não é repetido nas filas de voos que ainda não pousaram
                strcpy(novoVoo.ID, strupr(ID));                         //atribui valores do voo e transforma os caracteres alfabeticos em MAIUSCULO
                novoVoo.passageiros = setPassageiros();
                novoVoo.hora_prevista = setHoraPrevista(horarioAtual);
                printf("\nVOO %.*s INSERIDO COM SUCESSO NA FILA ", 4, novoVoo.ID);     //%.*s   recebe o argumento 4 e imprime os primeiros 4 caracteres do char[] ID

                if (ID[4] == '!')                                                    //se 5 elemento for '!', define como voo de emergencia
                {
                   printf("EMERGENCIAL\n\n");
                   novoVoo.status = -1;
                   fila_inserirVoo(emergencia, novoVoo);
                }
                else                                                                 //se 5 elemento for qualquer outra coisa, ignorar
                {
                    printf("COMUM\n\n");
                    if (estaAtrasado(horarioAtual, novoVoo.hora_prevista))
                    {
                        novoVoo.status = 0;         //atrasado
                    }
                    else
                    {
                        novoVoo.status = 1;         //não atrasado
                    }
                    fila_inserirVoo(comum, novoVoo);
                }
                printf("STATUS DO VOO: ");
                showStatus(novoVoo.status);         //imprime se esta atrasado, se é emergencia ou se esta no horario
                system("pause");
                break;
            case 2:
                if (!fila_vazia(emergencia))
                {
                    printf("VOO DE EMERGÊNCIA LIBERADO PARA ATERRISSAGEM!\n\n");
                    fila_printNextInfo(emergencia, 0);
                    fila_inserirVoo(realizados, fila_retirarVoo(emergencia));
                    printf("HORÁRIO DE LIBERAÇÃO: ");
                        showHorario(horarioAtual);
                    horarioAtual = addHora(horarioAtual, (10 + rand() % 5));
                }
                else if (!fila_vazia(comum))
                {
                    printf("VOO COMUM LIBERADO PARA ATERRISSAGEM!\n\n");
                    fila_printNextInfo(comum, 0);
                    fila_inserirVoo(realizados, fila_retirarVoo(comum));
                    printf("HORÁRIO DE LIBERAÇÃO: ");
                        showHorario(horarioAtual);
                    horarioAtual = addHora(horarioAtual, (10 + rand() % 5));
                }
                else
                {
                    printf("NÃO HÁ VOOS PARA LIBERAR!\n");
                }
                printf("\n");
                system("pause");
                break;
            case 3:
                do
                {
                    printf("Que fila deseja visualizar?\n");
                    printf("C - Comum\n");
                    printf("E - Emergencial\n");
                    printf("\n/: ");
                scanf("%c", &whichFila);
                fflush(stdin);
                whichFila = toupper(whichFila);
                if (whichFila != 'C' && whichFila != 'E')
                {
                    system("cls");
                    printf("Erro de Input\n\n");
                    system("pause");
                    system("cls");
                }
                } while(whichFila != 'C' && whichFila != 'E');
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
                        printf("\nFILA COMUM VAZIA!\n\n");
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
                        printf("\nFILA EMERGENCIAL VAZIA!\n\n");
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
                    printf("TODAS AS FILAS ESTÃO VAZIAS!\n\n");
                }
                system("pause");
                break;
            case 5:
                if (!fila_vazia(realizados))
                {
                    printf("\n\tPOUSOS REALIZADOS:\n\n");
                    fila_printAllInfo(realizados, 0);
                }
                else
                {
                    printf("NENHUM POUSO REALIZADO AINDA!\n\n");
                }
                system("pause");
                break;
            case 6:
                if (fila_vazia(comum) && fila_vazia(emergencia))
                {
                    printf("NÃO HÁ VOOS AGUARDANDO LIBERAÇÃO\n\n");
                }
                else
                {
                    do
                    {
                        time = 0;
                        printf("DIGITE O TEMPO(MINUTOS) PARA A SIMULAÇÃO DE POUSO\n");
                        scanf("%d", &time);
                        fflush(stdin);
                        if (time <= 0)
                        {
                            system("cls");
                            printf("Erro de Input\n\n");
                            system("pause");
                            system("cls");
                        }
                    } while (time <= 0);
                        printf("\n\tVOOS LIBERADOS EM %d MINUTOS:\n", time);
                        time /= (int) 10;
                        printQuant(comum, emergencia, time);
                }
                system("pause");
                break;
            case 0:
                break;
            default:
                system("cls");
                printf("Erro de Input\n\n");
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
    for (int i=0; i<4; i++)      //percorre primeiros 4 caracteres
    {
        if (!isalnum(ID[i]))     //se nao for puramente alfanumerico, é invalido
        {
            printf("ID invalido, utilizar 4 caracteres alfanuméricos e finalizar com ! para emergência ou 0 para normal\n");
            return 0;
        }
    }
    return 1;                    //id aceito
}

