#define MAX 500

typedef struct tarefa{
    int id;
    int prioridade;
    Pessoa *atribuida;
    int estado;
    int diai, mesi, anoi;
    char descricao[100];
    int diap, mesp, anop;
    int diaf, mesf, anof;
}Tarefa;

typedef struct pessoa{
    char nome[MAX];
    char email[MAX];
    int id;
    ListaTar* tarefas;
}Pessoa;

typedef struct lista{
    Tarefa tarefa;
    struct lista *next;
}NodeListaTar;

typedef struct Lista_pessoas{
    Pessoa pessoal;
    struct List1 *next;
}NodeListaP;

typedef Tarefa *Tarefa;
typedef Pessoa *Pessoa;
typedef NodeListaTar *ListaTar;


ListaTar* cria_lista(){
    ListaTar l = (ListaTar)malloc(sizeof(NodeListaTar));
    l->Tarefa->atribuida=(Pessoa)malloc(sizeof(Pessoa));
    l->next=NULL;
    return l;
}


