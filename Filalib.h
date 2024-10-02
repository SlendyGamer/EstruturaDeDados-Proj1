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
    double horaAtualConvertida = (horaAtual.dias * 1440) + (horaAtual.horas * 60) + (horaAtual.minutos); //transforma para tempo equivalente em horas
    double horaPrevistaConvertida = (horaPrevista.dias * 1440) + (horaPrevista.horas * 60) + (horaPrevista.minutos); //transforma para tempo equivalente em horas
    printf("%.0f\n", horaAtualConvertida);
    printf("%.0f\n", horaPrevistaConvertida);
    if ((horaPrevistaConvertida + 15) >= horaAtualConvertida) //adiciona 15 minutos de tolerancia e se esta dentro do horario, nao esta atrasado
    {
        printf("pontual");  //apagar
        return 1;
    }
    printf("atrasado");  //apagar
    return 0; //esta atrasado
}

void printMenu()
{
        printf("\n\nEscolha uma das opções abaixo:"

               "\n\n\t1- Registrar nova requisição de pouso"

               "\n\n\t2- Autorizar próximo avião"

               "\n\n\t3- Observar filas atuais"

               "\n\n\t4- Indicar próximo a pousar"

               "\n\n\t5- Observar pousos já realizados"

               "\n\n\t6- Estimar pousos que ainda serão feitos"

        "\n\nDigite '-1' para sair ");
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

/*
no* inserir(no *ult_pos, int novo_valor) //apagar
{
    no *no_aux = (no*) malloc(sizeof(no));
    no_aux->valor = novo_valor;
    no_aux->prox = NULL;

    if (ult_pos != NULL)
        ult_pos->prox = no_aux;

    return no_aux;
}

void fila_inserir(fila *f, int v) //apagar
{
    f->last = inserir(f->last, v);

    if (f->first == NULL)
        f->first = f->last;
}

no* retirar(no *pri_pos)
{
    no *no_aux = pri_pos->prox;
    free(pri_pos);
    return no_aux;
} */

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

/*
int fila_retirar(fila *f)
{
    int v;
    if (fila_vazia(f))
    {
        printf("\nFila vazia!\n");
        exit(0);
    }
    v = f->first->valor;
    f->first = retirar(f->first);
    if (f->first == NULL)
        f->last = NULL;
    return v;
} */

void fila_printAllInfo(fila *f)
{
    no* pos;
    printf("\n\n");
    for (pos=f->first; pos!=NULL; pos=pos->prox)
    {
        printf("ID:\t%.*s\n", 4, pos->info.ID);
        printf("Num pass:\t%d\n", pos->info.passageiros);
        printf("Status:\t %d\n", pos->info.status);
        printf("hora prevista:\t%d : %d\n", pos->info.hora_prevista.horas, pos->info.hora_prevista.minutos);
    }
    printf("\n\n");
}

void fila_printNextInfo(fila *f)
{
    no* pos = f->first;
    printf("\n\n");
    if (pos != NULL)
    {
        printf("ID:\t%.*s\n", 4, pos->info.ID);
        printf("Num pass:\t%d\n", pos->info.passageiros);
        printf("Status:\t %d\n", pos->info.status);
        printf("hora prevista:\t%d : %d\n", pos->info.hora_prevista.horas, pos->info.hora_prevista.minutos);
    }
}

void fila_printAll(fila *f)
{
    no* pos;
    printf("\n\n");
    for (pos=f->first; pos!=NULL; pos=pos->prox)
    {
        printf("%d - ", pos->valor);
    }
    printf("\n\n");
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
        if (strncmp(pos->info.ID, ID, 4) != 0)   //strncmp compara os 4 primeiros digitos de ID e compara se existe algum ID igual na fila atual, se existir ele retorna 1
            return 1;
        pos = pos->prox;
    }
    return 0;
}
#endif // FILAS_H_INCLUDED
