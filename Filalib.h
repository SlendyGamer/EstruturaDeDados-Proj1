#ifndef FILAS_H_INCLUDED
#define FILAS_H_INCLUDED

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







no* inserirVoo(no *ult_pos, char ID[], int pass, int stts) // data hora_prev
{
    no *no_aux = (no*) malloc(sizeof(no));
    strcpy(no_aux->info.ID, ID);
    no_aux->info.passageiros = pass;
    no_aux->info.status = stts;
    //no_aux->info.hora_prevista = hora_prev;
    no_aux->prox = NULL;

    if (ult_pos != NULL)
        ult_pos->prox = no_aux;

    return no_aux;
}

void fila_inserirVoo(fila *f, char ID[], int pass, int stts) //data hora_prev
{
    f->last = inserirVoo(f->last, ID, pass, stts); //data hora_prev

    if (f->first == NULL)
        f->first = f->last;
}


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
}

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
}

void fila_printAllInfo(fila *f)
{
    no* pos;
    printf("\n\n");
    for (pos=f->first; pos!=NULL; pos=pos->prox)
    {
        printf("ID:\t%.*s\n", 4, pos->info.ID);
        printf("Num pass:\t%d\n", pos->info.passageiros);
        printf("Status:\t %d\n", pos->info.status);
        printf("hora prevista:\t%d\n", pos->info.hora_prevista);
    }
    printf("\n\n");
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
