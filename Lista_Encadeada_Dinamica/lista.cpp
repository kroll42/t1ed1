/**********************************************************
*****
* Alunos: Deivison Correia Lima e Karolyne Imaculada Andrade Muniz
* Curso: Ciencia da Computacao - DACC/UNIR
* Trabalho 1: Listas Lineares
* Estrutura de Dados I-- 2022 -- DACC/UNIR, Profa. Carolina
* Watanabe
* Compilador: Dev-C++ 5.11
* IDE: Dev-C++
* Sistema Operacional: Windows 10 - Sistema operacional de 64 bits, processador baseado em x64
***********************************************************
****/

//Lista encadeada dinamica

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

//Le os dados de um arquivo texto e os insere na lista principal
//na mesma ordem como estao distribuidos no arquivo texto
//Retorna 1 se leu com sucesso
//Retorna 0 se nao pode ler
int Ler_Dados(Lista *L){
    tipo_elem v;
    FILE *arquivo;
    arquivo = fopen("alunos.txt", "r");
    if(arquivo == NULL)
        return 0;
    while(!feof(arquivo)){
        fscanf(arquivo, "%d %[^\n]s %f %f %f ", &v.matricula, &v.nome,&v.nota1, &v.nota2, &v.nota3);
        Inserir_Aluno_Final(L, v);
    }
    fclose(arquivo);
    return 1;
}

//Grava, em um arquivo de texto chamado alunos.txt, todos os dados dos alunos da lista principal
//Retorna 1 se gravou com sucesso
//Retorna 0 se nao pode gravar
int Gravar_Dados(Lista *L){
    FILE *arquivo;
    arquivo = fopen("alunos.txt", "w");
    if(arquivo == NULL)
        return 0;
    No *p;
    p = L->Inicio;
    while(p != NULL){
        fprintf(arquivo, "%d %.2f %.2f %.2f %s\n", p->info.matricula, p->info.nota1, p->info.nota2, p->info.nota3, p->info.nome);
        p = p->prox;
    }
    fclose(arquivo);
    return 1;
}


//Inicia a lista atribuindo NULL ao inicio
void Iniciar(Lista *L){
    L->Inicio = NULL;
}

//Verifica se a lista esta vazia
//Retorna 1 se estiver vazia
//Retorna 0 se nao estiver vazia
int Vazia(Lista *L){
    return (L->Inicio == NULL);
}

//Verifica se a matricula a ser cadastrada ja esta em uso
//Retorna 1 caso a matricula digitada ja exista
//Retorna 0 caso a matricula esteja disponivel para uso
int Verificar_Chave(Lista *L, int chave){
    No *p;
    p = L->Inicio;
    while(p != NULL){
        if(p->info.matricula == chave)
            return 1;
        p = p->prox;
    }
    return 0;
}

//Inserir aluno
//Insere um novo aluno no inicio da lista
//Retorna 0 se o aluno nao pode ser inserido
//Retorna 1 se o aluno foi inserido com sucesso
int Inserir_Aluno_Inicio(Lista *L, tipo_elem v){
    No *p, *aluno;
    p = L->Inicio;
    aluno = (No *) malloc(sizeof(No));
    if(aluno == NULL)
        return 0;
    aluno->info.matricula = v.matricula;
    strcpy(aluno->info.nome, v.nome);
    aluno->info.nota1 = v.nota1;
    aluno->info.nota2 = v.nota2;
    aluno->info.nota3 = v.nota3;
    L->Inicio = aluno;
    if(Vazia(L))
        aluno->prox = NULL;
    else
        aluno->prox = p;
    return 1;
}

//Funcao auxiliar, insere um novo aluno no final da lista
//Insere no inicio da lista se ela esta vazia
//Se nao estiver vazia, insere no final, chamando para isso a funcao Inserir_Aluno_Apos
int Inserir_Aluno_Final(Lista *L, tipo_elem v){
    if(Vazia(L))
        return Inserir_Aluno_Inicio(L, v);
    No *p, *q;
    p = L->Inicio;
    q = NULL;
    while(p != NULL){
        q = p;
        p = p->prox;
    }
    return Inserir_Aluno_Apos(L, v, q);
}

//Insere um novo aluno na lista ordenando pela matricula
int Inserir_Aluno_Ordenado(Lista *L, tipo_elem v){
    if(Vazia(L))
        return Inserir_Aluno_Inicio(L, v);
    No *p, *q;
    p = L->Inicio;
    q = NULL;
    if(Verificar_Ordem(L) == 1){//se a lista esta em ordem descrecente
        while(p != NULL && p->info.matricula > v.matricula){
            q = p;
            p = p->prox;
        }
    }else if(Verificar_Ordem(L) == 2){//se a lista esta em ordem crecente
        while(p != NULL && p->info.matricula < v.matricula){
            q = p;
            p = p->prox;
        }
    }
    if(q == NULL)
        return Inserir_Aluno_Inicio(L, v);
    return Inserir_Aluno_Apos(L, v, q);
}

//Funcao auxiliar para inserir um novo aluno na lista
//Retorna 0 se nao pode inserir o aluno
//Retorna 1 se o aluno foi inserido com sucesso
int Inserir_Aluno_Apos(Lista *L, tipo_elem v, No *k){
    No *aluno;
    aluno = (No *) malloc(sizeof(No));
    if(aluno == NULL)
        return 0;
    aluno->info.matricula = v.matricula;
    strcpy(aluno->info.nome, v.nome);
    aluno->info.nota1 = v.nota1;
    aluno->info.nota2 = v.nota2;
    aluno->info.nota3 = v.nota3;
    if(k->prox == NULL){
        aluno->prox = NULL;
        k->prox = aluno;
        return 1;
    }
    aluno->prox = k->prox;
    k->prox = aluno;
    return 1;
}

//Remover aluno
//Remove um aluno da lista, por meio da sua matricula
//Retorna 1 se removeu o aluno com sucesso
//Retorna 0 se a matricula informada nao consta na lista (nao foi possivel remover o aluno, pois ele nao esta na lista)
int Remover_Aluno(Lista *L, int chave){
    No *p, *q;
    p = q = L->Inicio;
    //se a matricula for a do primeiro aluno, rearranja L->Inicio
    if(q->prox == p->prox && p->info.matricula == chave){
        L->Inicio = p->prox;
        free(p);
        return 1;
    }
    while(p != NULL){
        if(p->info.matricula == chave){
            q->prox = p->prox;
            free(p);
            return 1;
        }
        q = p;
        p = p->prox;
    }
    return 0;
}

//Alterar cadastro do aluno
//Os dados que devem ser alterados sao indicados pelo usuario na funcao main
//Retorna 1 se alterou o cadastro do aluno com sucesso
//Retorna 0 se nao acho a matricula, o que significa que nao e possivel alterar o cadastro (o aluno nao esta na lista)
int Alterar_Cadastro(Lista *L, tipo_elem v, int k){
    No *p;
    p = L->Inicio;
    while(p != NULL){
        if(p->info.matricula == k){
            if(strcmp(p->info.nome, " ") != 0)
                strcpy(p->info.nome, v.nome);
            if(v.matricula != -1)
                p->info.matricula = v.matricula;
            if(v.nota1 != -1)
                p->info.nota1 = v.nota1;
            if(v.nota2 != -1)
                p->info.nota2 = v.nota2;
            if(v.nota3 != -1)
                p->info.nota3 = v.nota3;
            return 1;
        }
        p = p->prox;
    }
    return 0;
}

//Excluir a lista
//Aplica free em todos os nos, L->Inicio acaba apontando para NULL
void Excluir_Lista(Lista *L){
    No *p, *q;
    p = q = L->Inicio;
    while(p != NULL){
        p = p->prox;
        L->Inicio = p;
        free(q);
        q = p;
    }
}

//Buscar dados de um aluno, fornecendo o dado de matricula
//Retorna 1 se exibiu o aluno desejado
//Retorna 0 se nao ha a matricula procurada, o que significa que nao ha aluno para exibir (pois ele nao esta na lista)
int Buscar_Aluno(Lista *L, int chave){
    No *p;
    p = L->Inicio;
    while(p != NULL){
        if(p->info.matricula == chave){
            printf("\nALUNO(A) ENCONTRADO(A)\n");
            printf("- Matricula: %d\n", p->info.matricula);
            printf("- Nome: %s\n", p->info.nome);
            printf("- Nota 1: %.2f\n", p->info.nota1);
            printf("- Nota 2: %.2f\n", p->info.nota2);
            printf("- Nota 3: %.2f\n", p->info.nota3);
            return 1;
        }
        p = p->prox;
    }
    return 0;
}

//Exibir todos os dados de todos os alunos
void Exibir_Tudo(Lista *L){
    No *atual;
    if(Vazia(L))
        printf("A lista esta vazia. Nao ha alunos cadastrados.\n\n");
    else{
        atual = L->Inicio;
        while(atual != NULL){
            printf("%d - %s - %.2f, %.2f, %.2f\n", atual->info.matricula, atual->info.nome, atual->info.nota1, atual->info.nota2, atual->info.nota3);
            atual = atual->prox;
        }
        printf("\n");
    }
}

//Encontrar o aluno com maior nota da primeira prova
void Maior_Nota1(Lista *L){
    No *p;
    p = L->Inicio;
    float maior_nota;
    maior_nota = p->info.nota1;
    //varre toda a lista em busca da maior nota 1 e a guarda
    while(p != NULL){
        if(p->info.nota1 > maior_nota){
            maior_nota = p->info.nota1;
        }
        p = p->prox;
    }
    p = L->Inicio;
    printf("\nMAIOR NOTA DA PRIMEIRA PROVA:\n");
    while(p != NULL){
        if(p->info.nota1 == maior_nota){
            //caso haja mais de um aluno com a mesma nota, todos aparecerao nessa lista
            printf("- %s tirou %.2f\n", p->info.nome, maior_nota);
        }
        p = p->prox;
    }
    printf("\n");
}

//Encontrar aluno com maior média geral
void Maior_Media(Lista *L){
    No *p;
    float maior_med, med_atual;
    p = L->Inicio;
    maior_med = (p->info.nota1 + p->info.nota2 + p->info.nota3) / 3;
    //varre a lista em busca da maior media geral
    while(p != NULL){
        med_atual = (p->info.nota1 + p->info.nota2 + p->info.nota3) / 3;
        if(med_atual > maior_med) maior_med = med_atual;
        p = p->prox;
    }
    p = L->Inicio;
    //busca todos os estudantes que obtiveram essa maior media
    printf("\nMAIOR MEDIA:\n");
    while(p != NULL){
        med_atual = (p->info.nota1 + p->info.nota2 + p->info.nota3) / 3;
        if(med_atual == maior_med){
            printf("- %s teve media %.2f\n", p->info.nome, maior_med);
        }
        p = p->prox;
    }
    printf("\n");
}

//Encontrar aluno com menor média geral
void Menor_Media(Lista *L){
    No *p;
    float menor_med, med_atual;
    p = L->Inicio;
    menor_med = (p->info.nota1 + p->info.nota2 + p->info.nota3) / 3;
    //varre a lista em busca da menor média geral
    while(p != NULL){
        med_atual = (p->info.nota1 + p->info.nota2 + p->info.nota3) / 3;
        if(med_atual < menor_med) menor_med = med_atual;
        p = p->prox;
    }
    p = L->Inicio;
    //busca todos os estudantes que obtiveram essa menor media
    printf("\nMENOR MEDIA:\n");
    while(p != NULL){
        med_atual = (p->info.nota1 + p->info.nota2 + p->info.nota3) / 3;
        if(med_atual == menor_med){
            printf("- %s teve media %.2f\n", p->info.nome, menor_med);
        }
        p = p->prox;
    }
    printf("\n");
}

//Listar os alunos aprovados e reprovados, considerando o valor 6 para aprovacao
void Listar_Situacao(Lista *L){
    No *p;
    p = L->Inicio;
    float med;
    printf("\nALUNOS APROVADOS (MEDIA >= 6):\n");
    while(p != NULL){
        med = (p->info.nota1 + p->info.nota2 + p->info.nota3) / 3;
        if(med >= 6.0) printf("- (%d) %s teve media: %.2f\n", p->info.matricula, p->info.nome, med);
        p = p->prox;
    }
    p = L->Inicio;
    printf("\nALUNOS REPROVADOS (MEDIA < 6):\n");
    while(p != NULL){
        med = (p->info.nota1 + p->info.nota2 + p->info.nota3) / 3;
        if(med < 6.0) printf("- (%d) %s teve media: %.2f\n", p->info.matricula, p->info.nome, med);
        p = p->prox;
    }
    printf("\n");
}

//Verificar se a lista está ordenada ou não (a ordem pode ser crescente ou decrescente)
//Retorna 3 se a lista tem apenas um elemento
//Retorna 2 se a lista esta na ordem crescente
//Retorna 1 se a lista esta em ordem decrescente
//Retorna 0 se a lista nao esta ordenada
int Verificar_Ordem(Lista *L){
    if(Vazia(L))
        return 1;//num caso pratico, retorna 4 quando se deseja inserir um elemento na lista de forma ordenada, mas a lista esta vazia, assim, insere no inicio
    No *p, *q;
    q = L->Inicio;
    p = q->prox;
    if(q->prox == NULL)
        return 3;
    //verifica se esta em ordem crescente
    while(p != NULL && p->info.matricula > q->info.matricula){
        q = p;
        p = p->prox;
    }
    if(p == NULL)
        return 2;
    q = L->Inicio;
    p = q->prox;
    //verifica se esta em ordem decrescente
    while(p != NULL && p->info.matricula < q->info.matricula){
        q = p;
        p = p->prox;
    }
    if(p == NULL)
        return 1;
    return 0;
}

//Fazer uma cópia da lista L1 em uma outra lista L2
//a Lista L será copiada para L2
//Retorna 1 se a lista L1 foi copiada para L2 com sucesso
//Retorna 0 se um elemento nao pode ser alocado, logo a lista ficou incompleta ou nem foi iniciada
int Copia_Lista(Lista *L, Lista *L2){
    No *p, *q, *r;
    q = (No *) malloc(sizeof(No));
    if(q == NULL)
        return 0;
    L2->Inicio = q;
    p = L->Inicio;
    while(p != NULL){
        q->info = p->info;
        r = (No *) malloc(sizeof(No));
        if(r == NULL)
            return 0;
        q->prox = r;
        if(p->prox == NULL)
            q->prox = NULL;
        q = r;
        p = p->prox;
    }
    return 1;
}

//Inverter uma lista L1 colocando o resultado em L2
//Retorna 0 se a lista nao pode ser invertida
//Retorna 1 se a lista foi invertida com sucesso
int Inverter_Lista(Lista *L, Lista *L2){
    No *p, *q, *r;
    p = L->Inicio;
    q = NULL;
    while(p != NULL){
        r = q;
        q = (No *) malloc(sizeof(No));
        if(q == NULL)
            return 0;
        q->info = p->info;
        p = p->prox;
        q->prox = r;
    }
    L2->Inicio = q;
    return 1;
}

// Intercalar duas listas, L1 e L2, gerando uma lista L3. Considere que L1, L2 e L3 estão ordenadas
//Retorna 0 se as listas nao puderam ser intercaladas
//Retorna 1 se as listas foram intercaladas com sucesso
int Intercalar_Listas(Lista *L1, Lista *L2, Lista *L3){
    No *p, *q, *r, *s;
    p = L1->Inicio;
    q = L2->Inicio;
    r = (No *) malloc(sizeof(No));
    if(r == NULL)
        return 0;
    L3->Inicio = r;
    if(Verificar_Ordem(L1) == 1 && Verificar_Ordem(L2) == 1){//se as listas sao decrescente
        while(p != NULL && q != NULL){
            if(p->info.matricula > q->info.matricula){
                r->info = p->info;
                p = p->prox;
            }else{
                r->info = q->info;
                q = q->prox;
            }
            s = r;
            r = (No *) malloc(sizeof(No));
            if(r == NULL)
                return 0;
            s->prox = r;
        }
    }else{//se uma for crescente e a outra decrescente, ou as duas crescentes, entre outros casos
        if(Verificar_Ordem(L1) != Verificar_Ordem(L2)){
            Inverter_Lista(L2, L2);
            while(p != NULL && q != NULL){
                if(p->info.matricula < q->info.matricula){
                    r->info = p->info;
                    p = p->prox;
                }else{
                    r->info = q->info;
                    q = q->prox;
                }
                s = r;
                r = (No *) malloc(sizeof(No));
                if(r == NULL)
                    return 0;
                s->prox = r;
            }
            Inverter_Lista(L2, L2);
        }else{
            while(p != NULL && q != NULL){
                if(p->info.matricula < q->info.matricula){
                    r->info = p->info;
                    p = p->prox;
                }else{
                    r->info = q->info;
                    q = q->prox;
                }
                s = r;
                r = (No *) malloc(sizeof(No));
                if(r == NULL)
                    return 0;
                s->prox = r;
            }
        }
    }
    //a lista L1 nao acabou (a L2 sim acabou), copia o resto de L1 em L3
    if(p != NULL){
        while(p->prox != NULL){
            r->info = p->info;
            p = p->prox;
            s = r;
            r = (No *) malloc(sizeof(No));
            if(r == NULL)
                return 0;
            s->prox = r;
        }
        r->info = p->info;
        r->prox = NULL;
    }
    //a lista L2 nao acabou (a L1 sim acabou), copia o resto de L2 em L3
    if(q != NULL){
        while(q->prox != NULL){
            r->info = q->info;
            q = q->prox;
            s = r;
            r = (No *) malloc(sizeof(No));
            if(r == NULL)
                return 0;
            s->prox = r;
        }
        r->info = q->info;
        r->prox = NULL;
    }
    r = L3->Inicio;
    s = r->prox;
    //Remove repeticoes na lista intercalada
    while(s != NULL){
        if(r->info.matricula == s->info.matricula){
            Remover_Aluno(L3, r->info.matricula);
        }
        r = s;
        s = s->prox;
    }
    return 1;
}
