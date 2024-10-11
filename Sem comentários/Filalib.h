#ifndef FILAS_H_INCLUDED
#define FILAS_H_INCLUDED
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define CRESET   "\x1b[0m"
#define SEED 23698

/*
    Os defines s�o os c�digos ANSI para as respectivas cores listadas e CRESET restaura a cor para a padr�o do terminal do dispositivo.
    exemplo de uso: printf(RED "texto vermelho" CRESET);
    A seed serve para semear as fun��es randomicas e permite uma aleaoriedade "controlada".

    FUN��ES DE FILA:
- fila fila_criar(): RETORNA NOVA FILA
- int fila_vazia(fila): RETORNA 1 SE ESTIVER VAZIA, SE N�O, RETORNA 0
- void fila_inserirVoo(fila, voo): INSERE INFORMA��ES DO VOO NA �LTIMA POSI��O DA FILA
- voo fila_retirarVoo(fila): RETIRA E RETORNA INFORMA��ES DO VOO DA PRIMEIRA POSI��O DA FILA
- void fila_printAllInfo(fila, int): PRINTA INFORMA��O DE TODOS OS VOOS COM LAYOUT DEFINIDO PELO INT:
                                    0 - (oculta tipo do voo)
                                    1 - (oculta status e mostra tipo)
                                    2 - (oculta tipo e status)
- void fila_printNextInfo(fila, int): PRINTA INFORMA��O DE TODOS OS VOOS COM LAYOUT DEFINIDO PELO INT:
                                    0 - (oculta tipo do voo e mostra status)
                                    1 - (oculta hora prevista, mostra tipo e oculta status)
                                    2 - (oculta tipo e status)
- int fila_duplicata(fila, char[]): RETORNA 1 SE ENCONTRAR VOO COM ID IGUAL NA FILA PASSADA, SE N�O, RETORNA 0
- fila_liberar(fila): LIBERA A FILA PASSADA POR COMPLETO

    FUN��ES DE USO INTERNO:
- no inserirVoo(no, voo): CHAMADO POR fila_inserirVoo PARA REALIZAR A INSER��O DOS DADOS NA �LTIMA POSI��O DA FILA
- no retirarVoo(no): CHAMADO POR fila_retiraVoo PARA REALIZAR A REMO��O DOS DADOS NA PRIMEIRA POSI��O DA FILA

    FUN��ES DE USO GERAL:
- data setHorarioAtual(): GERA UM HORARIO V�LIDO ALEAT�RIO
- void showHorario(data): RETORNA UMS STRING FORMATADA CONTENDO O HOR�RIO
- void printMenu(): PRINTA O MENU PRINCIPAL DE SELE��O
- int setPassageiros(): DEFINE ALEATORIAMENTE OS PASSAGEIROS ENTRE 50|-|200
- data setHoraPrevista(data): DEFINE A HORA PREVISTA DE UM VOO ALEATORIAMENTE, MAS PR�XIMA DO HORARIO ATUAL
- data addHora(data, int): SOMA UMA QUANTIDADE DE MINUTOS A HORA ATUAL E A FORMATA NOVAMENTE, SE NECESS�RIO
- int estaAtrasado(data, data): TRANSFORMA AS DATAS EM MINUTOS E COMPARA AS DUAS PARA VER SE VOO ESTA ATRASADO OU NO HOR�RIO. RETORNA 1 PARA VOO ATRASADO, SE N�O, RETORNA 0
- void showStatus (int): PRINTA UM TEXTO RESPECTIVO AO VALOR DO STATUS
- void printInfo(no): PRINTA A INFORMA��O DO NO PASSADO
- void printQuant(fila, fila, int): PRINTA UM NUMERO ESPEC�FICO DE INFORMA��ES NA ORDEM QUE OCORRERIA CASO VOOS FOSSEM LIBERADOS
*/

typedef struct horario
{
    int dias;
    int horas;
    int minutos;
}data;

typedef struct voo
{
    char ID[5];
    int passageiros;
    int status;
    data hora_prevista;
}voo;

typedef struct no
{
    voo info;
    struct no *prox;
} no;

typedef struct fila
{
    no *first;
    no *last;
}fila;

data setHorarioAtual()
{
    data horarioAtual;
    int minutos = rand()%1440;

    horarioAtual.dias = 0;
    horarioAtual.horas = (int) (minutos/60);
    horarioAtual.minutos = minutos % 60;

    return horarioAtual;
}

void showHorario(data horario)
{
    printf("%02d : %02d\n", horario.horas, horario.minutos);
}

void printMenu()
{
        printf("\n\t\tO que deseja fazer?"

               "\n\n\t1 - Registrar nova requisi��o de pouso"

               "\n\n\t2 - Autorizar pr�xima aeronave"

               "\n\n\t3 - Observar filas de aeronaves"

               "\n\n\t4 - Indicar pr�xima aeronave que ser� liberada"

               "\n\n\t5 - Aterrissagens j� realizadas"

               "\n\n\t6 - Simular futuras aterrissagens"

        YELLOW "\n\n\tDigite '0' para sair\n" CRESET);
}

int setPassageiros()
{
    int passageiros = 50 + rand() % 151;
    return passageiros;
}

data setHoraPrevista(data horaAtual)
{
    data horaPrevista;

    horaPrevista.dias = 0;
    horaPrevista.minutos = (horaAtual.minutos -30 + rand() % 61);
    horaPrevista.horas = horaAtual.horas;

    if (horaPrevista.minutos >=60)
    {
        horaPrevista.horas++;
        horaPrevista.minutos -= 60;
        if(horaPrevista.horas > 23)
        {
            horaPrevista.dias++;
            horaPrevista.horas -= 24;
        }
    }
    else if (horaPrevista.minutos < 0)
    {
        horaPrevista.horas--;
        horaPrevista.minutos += 60;
        if(horaPrevista.horas < 0)
        {
            horaPrevista.dias--;
            horaPrevista.horas += 24;
        }
    }

    return horaPrevista;
}

data addHora(data horaAtual, int minutos)
{
    data horaPrevista;

    horaPrevista.dias = 0;
    horaPrevista.minutos = (horaAtual.minutos + minutos);
    horaPrevista.horas = horaAtual.horas;

    if (horaPrevista.minutos >=60)
    {
        horaPrevista.horas++;
        horaPrevista.minutos -= 60;
        if(horaPrevista.horas > 23)
        {
            horaPrevista.dias++;
            horaPrevista.horas -= 24;
        }
    }
    else if (horaPrevista.minutos < 0)
    {
        horaPrevista.horas--;
        horaPrevista.minutos += 60;
        if(horaPrevista.horas < 0)
        {
            horaPrevista.dias--;
            horaPrevista.horas += 24;
        }
    }

    return horaPrevista;
}

int estaAtrasado(data horaAtual, data horaPrevista)
{
    long horaAtualConvertida = (horaAtual.dias * 1440) + (horaAtual.horas * 60) + (horaAtual.minutos);
    long horaPrevistaConvertida = (horaPrevista.dias * 1440) + (horaPrevista.horas * 60) + (horaPrevista.minutos);
    if ((horaPrevistaConvertida + 15) >= horaAtualConvertida)
    {
        return 0;
    }
    return 1;
}

void showStatus(int n)
{
    if (n == 1)
    {
        printf(GREEN "SEM ATRASO!\n\n" CRESET);
    }
    else if (n == 0)
    {
        printf(YELLOW "ATRASADO!\n\n" CRESET);
    }
    else
    {
        printf(RED "EMERG�NCIA!\n\n" CRESET);
    }

}

void printInfo(no *n)
{
    printf("\tC�DIGO DO VOO: %.*s\n", 4, n->info.ID);
    printf("\tPASSAGEIROS � BORDO: %d\n", n->info.passageiros);
    printf("\tTIPO DO VOO: ");
    if (n->info.status == -1)
        showStatus(n->info.status);
    else
        printf(BLUE "COMUM!\n\n" CRESET);
}

void printQuant(fila *c, fila *e, int q)
{
    no* auxC = c->first;
    no* auxE = e->first;
    int i = 0;
    while (auxE != NULL && i<q)
    {
        printInfo(auxE);
        auxE = auxE->prox;
        i++;
    }
    while (auxC != NULL && i<q)
    {
        printInfo(auxC);
        auxC = auxC->prox;
        i++;
    }
}

fila* fila_criar()
{
    fila* nova_fila = (fila*) malloc(sizeof(fila));
    nova_fila->first = NULL;
    nova_fila->last = NULL;
    return nova_fila;
}

int fila_vazia(fila *f)
{
    if (f->first == NULL)
        return 1;

    return 0;
}






no* inserirVoo(no *ult_pos, voo infoVoo)
{
    no *no_aux = (no*) malloc(sizeof(no));
    strcpy(no_aux->info.ID, infoVoo.ID);
    no_aux->info.passageiros = infoVoo.passageiros;
    no_aux->info.status = infoVoo.status;
    no_aux->info.hora_prevista = infoVoo.hora_prevista;
    no_aux->prox = NULL;

    if (ult_pos != NULL)
        ult_pos->prox = no_aux;

    return no_aux;
}

void fila_inserirVoo(fila *f, voo infoVoo)
{
    f->last = inserirVoo(f->last, infoVoo);

    if (f->first == NULL)
        f->first = f->last;
}

no* retirarVoo(no *pri_pos)
{
    no *no_aux = pri_pos->prox;
    free(pri_pos);
    return no_aux;
}

voo fila_retirarVoo(fila *f)
{
    voo v;
    if (fila_vazia(f))
    {
        printf("\nFila vazia!\n");
        exit(0);
    }
    v = f->first->info;
    f->first = retirarVoo(f->first);
    if (f->first == NULL)
        f->last = NULL;
    return v;
}

void fila_printAllInfo(fila *f, int printType)
{
    no* pos;
    for (pos=f->first; pos!=NULL; pos=pos->prox)
    {
        printf("\tC�DIGO DO VOO: %.*s\n", 4, pos->info.ID);
        printf("\tPASSAGEIROS � BORDO: %d\n", pos->info.passageiros);
        printf("\tHORA DE CHEGADA PREVISTA: ");
            showHorario(pos->info.hora_prevista);
        if (printType == 1)
        {
            printf("\tTIPO DO VOO: ");
            if (pos->info.status == -1)
                showStatus(pos->info.status);
            else
                printf(BLUE "COMUM!\n" CRESET);
        }
        else if (printType == 0)
        {
            printf("\tSTATUS: ");
                showStatus(pos->info.status);
        }
        printf("\n");
    }
}

void fila_printNextInfo(fila *f, int printType)
{
    no* pos = f->first;
    if (pos != NULL)
    {
        printf("\tC�DIGO DO VOO: %.*s\n", 4, pos->info.ID);
        printf("\tPASSAGEIROS � BORDO: %d\n", pos->info.passageiros);
        if (printType != 1)
        {
            printf("\tHORA DE CHEGADA PREVISTA: ");
                showHorario(pos->info.hora_prevista);
        }
        if (printType != 0)
        {
            printf("\tTIPO DO VOO: ");
            if (pos->info.status == -1)
                showStatus(pos->info.status);
            else
                printf(BLUE "COMUM!\n\n" CRESET);
        }
        else
        {
            printf("\tSTATUS: ");
            showStatus(pos->info.status);
        }
    }
}

int fila_duplicata(fila *f, char ID[])
{
    no *pos = f->first;
    while (pos != NULL)
    {
        if (strncmp(pos->info.ID, strupr(ID), 4) == 0)
        {
            printf(RED "\n\tERRO: Voo j� registrado no sistema!\n\n" CRESET);
            return 1;
        }
        pos = pos->prox;
    }
    return 0;
}

fila* fila_liberar(fila *f)
{
    no* elemento = f->first;
    while (elemento != NULL)
    {
        no* aux = elemento->prox;
        free(elemento);
        elemento = aux;
    }
    free(f);
    printf(YELLOW "." CRESET);
    return NULL;
}
#endif // FILAS_H_INCLUDED
