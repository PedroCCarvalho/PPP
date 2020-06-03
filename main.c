#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "estruturas.h"
#define MAX 500

    int idglobal=1;

    void InserePessoas(ListaP *lPessoas, Pessoa *p){
        ListaP *l= lPessoas;
        while(l->next!=NULL){
            l=l->next;
        }
        ListaP *atual=(ListaP*)malloc(sizeof(ListaP));
        atual->pessoa=p;
        atual->next=NULL;
        l->next=atual;
    }

    void AtribuiPessoas(ListaP *lPessoas,int idp, Tarefa *tar){
        ListaP *p=lPessoas;
        while (p!=NULL && idp!=p->pessoa->id){
            p=p->next;
        }
        if(idp==p->pessoa->id){
            tar->atribuida=p->pessoa;
        }else{
            printf("Pessoa nao econtrada!");
        }
    }



    void listaPessoas(ListaP *lPessoas){
        ListaP *l=lPessoas;
        Pessoa *nova;
        FILE *file;
        file = fopen("C:\\Users\\utilizador\\CLionProjects\\Projeto\\listapessoas.txt", "r");
        char linha[MAX], *nome, *email, *ids;
        int id;
        if(file == NULL){
            printf("Ficheiro nao encontrado.\n");
        }
        while(!feof(file)){
            nova = (Pessoa*)malloc(sizeof(Pessoa));
            fgets(linha, MAX, file);
            nome=strtok(linha, "-");
            strcpy(nova->nome,nome);
            email=strtok(NULL, "-");
            strcpy(nova->email,email);
            ids=strtok(NULL, "-");
            id=atoi(ids);
            nova->id=id;
            InserePessoas(l, nova);
        }
        fclose(file);
        printf("\n");
    }

    void nova_tarefa(ListaTar *lOriginal, Tarefa *tar){
        ListaTar *l = lOriginal;
        while(l->next != NULL){
            l = l->next;
        }
        ListaTar *atual = (ListaTar*) malloc(sizeof(ListaTar));
        atual->tarefa = tar;
        l->next = atual;
        atual->next = NULL;
    }

    void FillToDo(ListaTar *lOriginal, ListaTar *lToDo){
        ListaTar *l = lOriginal;
        ListaTar *td = lToDo;
        while (l!=NULL){
            if(l->tarefa->estado==1){
                while(td->next != NULL){
                    td = td->next;
                }
                ListaTar *atual = (ListaTar*)malloc(sizeof(ListaTar));
                atual->tarefa = l->tarefa;
                td->next = atual;
                atual->next=NULL;
            }
            l=l->next;
        }
    }

    void insereToDo(ListaTar *lToDo, Tarefa *tnova){
        ListaTar *ant = lToDo;
        ListaTar *prev = lToDo->next;
        ListaTar *atual = (ListaTar*) malloc(sizeof(ListaTar));
        atual->tarefa = tnova;
        atual->next = NULL;
        if(prev == NULL) {
            ant->next = atual;
        } else {
            while(prev != NULL) {
                if(prev->tarefa->prioridade <= atual->tarefa->prioridade) {
                    atual->next = prev;
                    ant->next = atual;
                    break;
                }
                prev = prev->next;
                ant = ant->next;
            }
        }
    }

    void insereDoing(ListaTar *lDoing, Tarefa *tnova){
        ListaTar *l = lDoing;
        while(l->next != NULL){
            l = l->next;
        }
        ListaTar *atual = (ListaTar*) malloc(sizeof(ListaTar));
        atual->tarefa = tnova;
        l->next=atual;
        atual->next = NULL;
    }

    void insereDone(ListaTar *lDone, Tarefa *tnova){
        ListaTar *l = lDone;
        while(l->next != NULL){
            l = l->next;
        }
        ListaTar *atual = (ListaTar*) malloc(sizeof(ListaTar));
        atual->tarefa = tnova;
        l->next=atual;
        atual->next = NULL;
    }

    Tarefa* elimina_listatd (ListaTar *lToDo, Tarefa *tar){
        ListaTar *l = lToDo->next;
        ListaTar *ant = lToDo;
        while ((l) != NULL && (l)->tarefa->id != tar->id){
            ant = ant->next;
            l=l->next;
        }
        if (l!=NULL){
            ant->next=l->next;
            return l->tarefa;
        }
        return NULL;
    }

    Tarefa* elimina_listadg (ListaTar *lDoing, Tarefa *tar){
        ListaTar *l = lDoing->next;
        ListaTar *ant = lDoing;
        while ((l) != NULL && (l)->tarefa->id != tar->id){
            ant = ant->next;
            l=l->next;
        }
        if (l!=NULL){
            ant->next=l->next;
            return l->tarefa;
        }
        return NULL;
    }

    Tarefa* elimina_listade (ListaTar *lDone, Tarefa *tar){
        ListaTar *l = lDone->next;
        ListaTar *ant = lDone;
        while ((l) != NULL && (l)->tarefa->id != tar->id){
            ant = ant->next;
            l=l->next;
        }
        if (l!=NULL){
            ant->next=l->next;
            return l->tarefa;
        }
        return NULL;
    }

    int TestaData(int ano, int mes, int dia){
        int aux=1;
        if(ano<2010 || ano>2020){
            aux=2;
        }
        if(mes>12 || mes<1){
            aux=2;
        }
        switch (mes){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if(dia<0 || dia>31){
                    aux=2;
                    break;
                }
            case 2:
                if(ano/4==0){
                    if(dia<0 || dia>29){
                        aux=2;
                        break;
                    }
                }
                else{
                    if(dia<0 || dia>28){
                        aux=2;
                        break;
                    }
                }
            case 4:
            case 6:
            case 9:
            case 11:
                if(dia<0 || dia>30){
                    aux=2;
                    break;
                }
            default:
                break;
        }
        return aux;
    }

    void reatribuirTarefas(ListaTar *lDoing, ListaP *lPessoas){
        ListaTar *l = lDoing->next;
        ListaP *p = lPessoas->next;
        int aux, id;
        printf("Insira o id da tarefa à qual quer reatribuir a tarefa: ");
        scanf("%d", &aux);
        while ((l) != NULL && (l)->tarefa->id != aux){
            l=l->next;
        }
        if (l!=NULL){
            printf("Insira o id do novo responsavel pela tarefa");
            scanf("%d", &id);
            while(p!=NULL && p->pessoa->id!=id){
                p=p->next;
            }
            if (p!=NULL){
                l->tarefa->atribuida=p->pessoa;
            }
        }
    }

    void addtarefa(ListaTar *lOriginal, ListaTar *lToDo){
        int id, teste;
        ListaTar *l = lOriginal;
        ListaTar *td = lToDo;
        Tarefa *nova = (Tarefa*) malloc(sizeof(Tarefa));
        fflush(stdin);
        nova->estado=1;
        printf("Insira o nome da tarefa: ");
        scanf("%s", &nova->descricao);
        nova->id=idglobal;
        printf("Insira a prioridade da nova tarefa: ");
        scanf("%d", &nova->prioridade);
        while (nova->prioridade>10 || nova->prioridade<1){
            printf("Insira uma prioridade valida (1 a 10): ");
            fflush(stdin);
            scanf("%d", &nova->prioridade);
        }
        printf("Insira a data de inicio desta tarefa(dd mm aa): ");
        scanf("%d %d %d", &nova->diai, &nova->mesi, &nova->anoi);
        teste=TestaData(nova->anoi, nova->mesi, nova->diai);
        while(teste==2){
            printf("Insira uma data valida! (dd mm aa): ");
            scanf("%d %d %d", &nova->diai, &nova->mesi, &nova->anoi);
            teste=TestaData(nova->anoi, nova->mesi, nova->diai);
        }
        nova_tarefa(l, nova);
        insereToDo(td, nova);
        idglobal+=1;
    }

    void ImprimeTarefas(ListaTar *lOriginal){
        ListaTar *l = lOriginal->next;
        while(l!=NULL){
            printf("Nome: %s \n", l->tarefa->descricao);
            printf("ID: %d \n", l->tarefa->id);
            printf("Prioridade: %d \n", l->tarefa->prioridade);
            printf("Data de inicio: %d/%d/%d\n",l->tarefa->diai, l->tarefa->mesi, l->tarefa->anoi);
            if(l->tarefa->estado==2){
                printf("Responsavel==> Nome: %s; email: %s; id:%d\n", l->tarefa->atribuida->nome, l->tarefa->atribuida->email, l->tarefa->atribuida->id);
                printf("Prazo:: %d/%d/%d\n", l->tarefa->diai, l->tarefa->mesi, l->tarefa->anoi);
            }else if(l->tarefa->estado==3){
                printf("Data de conclusão: %d/%d/%d\\n\", l->tarefa->diap, l->tarefa->mesp, l->tarefa->anop");
            }
            l=l->next;
            printf("--------------------------------\n");
        }
    }

    void TarefaPessoal(ListaTar *lDoing, ListaP *lPessoas) {
        ListaTar *l = lDoing->next;
        ListaP *lp = lPessoas->next;
        int idp;
        printf("Insira o id da pessoa: ");
        scanf("%d", &idp);
        while (lp != NULL && lp->pessoa->id != idp) {
            lp = lp->next;
        }
        if (lp != NULL) {
            while (l != NULL) {
                printf("Ola");
                if (l->tarefa->atribuida->id == idp) {
                    printf("Nome: %s \n", l->tarefa->descricao);
                    printf("ID: %d \n", l->tarefa->id);
                    printf("Prioridade: %d \n", l->tarefa->prioridade);
                    printf("Data de inicio: %d/%d/%d\n", l->tarefa->diai, l->tarefa->mesi, l->tarefa->anoi);
                    printf("Responsavel==> Nome: %s; email: %s; id:%d\n", l->tarefa->atribuida->nome, l->tarefa->atribuida->email, l->tarefa->atribuida->id);
                    printf("Prazo:: %d/%d/%d\n", l->tarefa->diai, l->tarefa->mesi, l->tarefa->anoi);
                    printf("--------------------------------\n");
                }
            l = l->next;
            }
        }else{
            printf("Pessoa nao encontrada!");
        }
    }


    /*int MaximoTarefas(maxtar){
        int aux;
        printf("Insira o numero maximo de tarefas que cada pessoa pode executar: ");
        scanf("%d", &aux);
        while (aux<maxtar){
            printf("Ha pessoas com %d tarefas. Tem de inserir um numero maior.\n", maxtar);
            scanf("%d", &aux);
        }
        printf("O maximo de tarefas atribuido e: %d", aux);
        return aux;
    }*/


    void ImprimePessoas(ListaP *lPessoas){
        ListaP *l = lPessoas->next;
        while(l!=NULL){
            printf("Nome: %s\n",l->pessoa->nome);
            printf("Email: %s\n", l->pessoa->email);
            printf("ID: %d\n", l->pessoa->id);
            printf("============================\n");
            l=l->next;
        }
    }

    int VerificaSalto(int Novo,int Atual){
        int aux=1;
        switch(Atual){
            case 1:
                if (Novo==3){
                    printf("Mudanca impossivel!\n");
                    aux=2;
                    break;
                }else{
                    printf("Mudanca concluida!\n");
                    break;
                }
            case 2:
                if (Novo==1){
                    printf("Mudanca impossivel!\n");
                    aux=2;
                    break;
                }else{
                    printf("Mudanca concluida!\n");
                    break;
                }
            case 3:
                if (Novo==2){
                    printf("Mudanca impossivel!\n");
                    aux=2;
                    break;
                }else{
                    printf("Mudanca concluida!\n");
                    break;
                }
        }
        return aux;
    }

    void MoverTarefas(ListaTar *lOriginal, ListaTar *lToDo, ListaTar *lDoing, ListaTar *lDone, ListaP *lPessoa){
        ListaTar *l = lOriginal;
        ListaTar *ToDo = lToDo;
        ListaTar *Doing = lDoing;
        ListaTar *Done = lDone;
        ListaP *Pessoas = lPessoa;
        Tarefa *tar = (Tarefa*) malloc(sizeof(Tarefa));
        int aux, idtar, idp, teste;
        printf("Insira o id da tarefa a alterar: ");
        scanf("%d", &idtar);
        printf("Insira para que fase quer meter a tarefa:\n [1]=To DO \n [2]=Doing \n [3]=Done\n    ");
        scanf("%d", &aux);
        while (l->next!=NULL){
            l=l->next;
            if (l->tarefa->id==idtar){
                tar=l->tarefa;
                while(VerificaSalto(aux, l->tarefa->estado)==2){
                    printf("Insira outra mudança: ");
                    scanf("%d", &aux);
                }
                switch(aux){
                    case 1:
                        elimina_listade(Done, tar);
                        insereToDo(ToDo, l->tarefa);
                        l->tarefa->estado=1;
                        break;
                    case 2:
                        elimina_listatd(ToDo, tar);
                        insereDoing(Doing, l->tarefa);
                        l->tarefa->estado=2;
                        printf("Insira o id da pessoa a quem quer atribuir esta tarefa: ");
                        scanf("%d", &idp);
                        AtribuiPessoas(Pessoas, idp, l->tarefa);
                        printf("Insira o prazo final da tarefa(dd mm aa): ");
                        scanf("%d %d %d", &l->tarefa->diap, &l->tarefa->mesp, &l->tarefa->anop);
                        teste=TestaData(l->tarefa->anop, l->tarefa->mesp, l->tarefa->diap);
                        while(teste==2){
                            printf("Insira uma data valida! (dd mm aa): ");
                            scanf("%d %d %d", &l->tarefa->diap, &l->tarefa->mesp, &l->tarefa->anop);
                            teste=TestaData(l->tarefa->anop, l->tarefa->mesp, l->tarefa->diap);
                        }
                        break;
                    case 3:
                        elimina_listadg(Doing, tar);
                        insereDone(Done, l->tarefa);
                        l->tarefa->estado=3;
                        printf("Insira a data de conclusao da tarefa: (dd/mm/aa)");
                        scanf("%d %d %d", &l->tarefa->diaf, &l->tarefa->mesf, &l->tarefa->anof);
                        teste=TestaData(l->tarefa->anof, l->tarefa->mesf, l->tarefa->diaf);
                        while(teste==2){
                            printf("Insira umda data valida! \n");
                            scanf("%d %d %d", &l->tarefa->diaf, &l->tarefa->mesf, &l->tarefa->anof);
                            teste=TestaData(l->tarefa->anof, l->tarefa->mesf, l->tarefa->diaf);
                        }
                        break;
                }
            }
        }
    }

    void menu(){
        ListaTar* lOriginal = cria_lista();
        ListaTar* lToDo = cria_lista();
        ListaTar* lDoing = cria_lista();
        ListaTar* lDone = cria_lista();
        ListaP* lPessoas = cria_listaP();
        listaPessoas(lPessoas);
        int escolha;
        system("cls");
        while(1){
            printf("MENU:\n [1] Adicionar uma tarefa\n [2] Mover uma tarefa\n [3] Defenir o numero maximo de tarefas\n [4] Reatribuir tarefa\n [5] Mostrar tarefas\n [6] Mostrar pessoas\n [7] Lista de Tarefas de uma pessoa\n [8] Sair da aplicacao\n ");
            scanf("%d", &escolha);
            fflush(stdin);
            switch (escolha){
                case 1:
                    addtarefa(lOriginal, lToDo);
                    break;
                case 2:
                    MoverTarefas(lOriginal, lToDo, lDoing, lDone, lPessoas);
                    break;
                case 3:
                    /*MaximoTarefas(l);*/
                    break;
                case 4:
                    reatribuirTarefas(lDoing, lPessoas);
                    break;
                case 5:
                    printf("\n-------------------------------- To do\n");
                    ImprimeTarefas(lToDo);
                    printf("\n-------------------------------- Doing\n");
                    ImprimeTarefas(lDoing);
                    printf("\n-------------------------------- Done\n");
                    ImprimeTarefas(lDone);
                    break;
                case 6:
                    ImprimePessoas(lPessoas);
                    break;
                case 7:
                    TarefaPessoal(lDoing, lPessoas);
                    break;
                case 8:
                    guardaInfo(lOriginal);
                    printf("Programa terminado com sucesso!\n");
                    exit(0);
                default:
                    printf("Insira uma opcao correta.\n");
                    break;
            }
        }
}

int main(){
    menu();
    return 0;
}
