#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED
#define MAX 500

typedef struct pessoa Pessoa;
typedef struct tarefa Tarefa;
typedef struct lista ListaTar;
typedef struct Lista_pessoas ListaP;

struct tarefa{
    int id;
    int prioridade;
    int estado;
    Pessoa *atribuida;
    int estado;
    int diai, mesi, anoi;
    char descricao[100];
    int diap, mesp, anop;
    int diaf, mesf, anof;
};

struct pessoa{
    char nome[MAX];
    char email[MAX];
    int id;
};

struct lista{
    Tarefa *tarefa;
    ListaTar *next;
};

struct Lista_pessoas{
    Pessoa *pessoa;
    ListaP *next;
};


ListaTar* cria_lista(){
    ListaTar *l = (ListaTar*)malloc(sizeof(ListaTar));
    l->tarefa = (Tarefa*)malloc(sizeof(Tarefa));
    l->next=NULL;
    return l;
}

ListaP* cria_listaP(){
    ListaP *l = (ListaP*)malloc(sizeof(ListaP));
    l->pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    l->next=NULL;
    return l;
}

#endif // ESTRUTURAS_H_INCLUDED
