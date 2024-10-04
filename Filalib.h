#ifndef FILAS_H_INCLUDED
#define FILAS_H_INCLUDED
#define SEED 23698

typedef struct horario
{
    int dias;  //para separar horarios de dias diferentes 0 - ??
    int horas; //0 - 23
    int minutos; //0 - 59
}data;

typedef struct voo
{
    char ID[5];    //id 4 caracteres alfanum e ! ou nao(emergencial)
    int passageiros; //num passageiros
    int status;   //0 atrasado, 1 on time, -1 emergencia
    data hora_prevista;
}voo;

typedef struct no
{
    voo info;
    int valor;
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
    int minutos = rand()%1440;         //1440 minutos representa 24h

    horarioAtual.dias = 0;
    horarioAtual.horas = (int) (minutos/60);      //converte tempo em minutos para horas
    horarioAtual.minutos = minutos % 60;          //o resto são os minutos

    return horarioAtual;
}

void showHorario(data horario)
{
    printf("%02d : %02d\n", horario.horas, horario.minutos);   //printa horario recebido formatado
}

void printMenu()
{
        printf("\n\t\tO que deseja fazer?"

               "\n\n\t1 - Registrar nova requisição de pouso"

               "\n\n\t2 - Autorizar próxima aeronave"

               "\n\n\t3 - Observar filas de aeronaves"

               "\n\n\t4 - Indicar próxima aeronave que será liberada"

               "\n\n\t5 - Aterrissagens já realizadas"

               "\n\n\t6 - Simular futuras aterrissagens"

        "\n\nDigite '0' para sair\n");
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
    long horaAtualConvertida = (horaAtual.dias * 1440) + (horaAtual.horas * 60) + (horaAtual.minutos); //transforma para tempo equivalente em horas
    long horaPrevistaConvertida = (horaPrevista.dias * 1440) + (horaPrevista.horas * 60) + (horaPrevista.minutos);
    if ((horaPrevistaConvertida + 15) >= horaAtualConvertida) //adiciona 15 minutos de tolerancia e se esta dentro do horario, nao esta atrasado
    {
        return 0;
    }
    return 1; //esta atrasado
}

void showStatus(int n)
{
    if (n == 1)
    {
        printf("SEM ATRASO!\n\n");
    }
    else if (n == 0)
    {
        printf("ATRASADO!\n\n");
    }
    else
    {
        printf("EMERGÊNCIA!\n\n");
    }

}

void printInfo(no *n)
{
    printf("\n\tCÓDIGO DO VOO: %.*s\n", 4, n->info.ID);
    printf("\tPASSAGEIROS À BORDO: %d\n", n->info.passageiros);
    printf("\tTIPO DO VOO: ");
    if (n->info.status == -1)
        showStatus(n->info.status);              //nunca vai querer saber o status??
    else
        printf("COMUM!\n");
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
    printf("\n");
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

    return 0;                  //funciona?
}






no* inserirVoo(no *ult_pos, voo infoVoo) // data hora_prev
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

void fila_inserirVoo(fila *f, voo infoVoo) //data hora_prev
{
    f->last = inserirVoo(f->last, infoVoo); //data hora_prev

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

void fila_printAllInfo(fila *f, int printType)   //printType - 0 (oculta tipo do voo) - 1 (oculta status e mostra tipo) - 2 (oculta tipo e status)
{
    no* pos;
    for (pos=f->first; pos!=NULL; pos=pos->prox)
    {
        printf("\tCÓDIGO DO VOO: %.*s\n", 4, pos->info.ID);
        printf("\tPASSAGEIROS À BORDO: %d\n", pos->info.passageiros);
        printf("\tHORA DE CHEGADA PREVISTA: ");
            showHorario(pos->info.hora_prevista);
        if (printType == 1)
        {
            printf("\tTIPO DO VOO: ");
            if (pos->info.status == -1)
                showStatus(pos->info.status);              //nunca vai querer saber o status??
            else
                printf("COMUM!\n");
        }
        else if (printType == 0)
        {
            printf("\tSTATUS: ");
                showStatus(pos->info.status);
        }
        printf("\n");
    }
}

void fila_printNextInfo(fila *f, int printType)   //printType - 0 (oculta tipo do voo e mostra status) - 1 (oculta hora prevista, mostra tipo e oculta status) - 2 (oculta tipo e status)
{
    no* pos = f->first;
    if (pos != NULL)
    {
        printf("\tCÓDIGO DO VOO: %.*s\n", 4, pos->info.ID);
        printf("\tPASSAGEIROS À BORDO: %d\n", pos->info.passageiros);
        if (printType != 1)
        {
            printf("\tHORA DE CHEGADA PREVISTA: ");
                showHorario(pos->info.hora_prevista);
        }
        if (printType != 0)
        {
            printf("\tTIPO DO VOO: ");
            if (pos->info.status == -1)
                showStatus(pos->info.status);              //nunca vai querer saber o status??
            else
                printf("COMUM!\n");
        }
        else
        {
            printf("\tSTATUS: ");
            showStatus(pos->info.status);
        }
    }
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
    printf("\nfila liberada\n");
    return NULL;
}

int fila_duplicata(fila *f, char ID[]) //correta?
{
    no *pos = f->first;
    while (pos != NULL)
    {
        if (strncmp(pos->info.ID, strupr(ID), 4) == 0)   //strncmp compara os 4 primeiros digitos de ID e compara se existe algum ID igual na fila atual, se existir ele retorna 1
        {
            printf("\nERRO: Voo já registrado no sistema!\n");
            return 1;
        }
        pos = pos->prox;
    }
    return 0;
}
#endif // FILAS_H_INCLUDED
