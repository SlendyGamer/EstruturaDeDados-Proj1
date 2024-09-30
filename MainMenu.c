#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include "Filalib.h"
int IDvalido(char ID[]);



int main()
{
    setlocale(LC_ALL,"portuguese");
    //fila *comum = fila_criar();
    //fila *emergencia = fila_criar();
    //fila *realizados = fila_criar();
    //if (comum == NULL || emergencia == NULL || realizados == NULL)
    //{
    //    printf("filas não inicializadas corretamente! abortando programa!");
    //    exit(0);
    //}
    int sel = 0;
    char ID[6] = {0};
    do
    {
        printf("\n\n\t\tTorre de Controle LucI airport");
        printf("\n\nEscolha uma das opções abaixo:");

        printf("\n\n\t1- Registrar nova requisição de pouso");
        printf("\n\n\t2- Autorizar próximo avião");
        printf("\n\n\t3- Observar filas atuais");
        printf("\n\n\t4- Indicar próximo a pousar");
        printf("\n\n\t5- Observar pousos já realizados");
        printf("\n\n\t6- Estimar pousos que ainda serão feitos");
        printf("\n\nDigite '-1' para sair ");

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

                break;
            case 2:
                 for (int i=0; i<10; i++)
                    {
                        printf("%c\n", ID[i]);
                    }
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
    //fila_liberar(comum);
    //fila_liberar(emergencia);
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

