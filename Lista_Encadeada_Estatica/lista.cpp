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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#define MAX 100

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
        if(!Cheia(L))
            Inserir_Aluno_Final(L, v);
    }
    //Remover_Aluno(L, v.matricula);
    fclose(arquivo);
    return 1;
}

//Grava, em um arquivo de texto chamado alunos.txt, todos os dados dos alunos da lista
//Retorna 1 se gravou com sucesso
//Retorna 0 se nao pode gravar
int Gravar_Dados(Lista *L){
    int i = 0;
    FILE *arquivo;
    arquivo = fopen("alunos.txt", "w");
    if(arquivo == NULL)
        return 0;
    while(i < L->nelem){
        fprintf(arquivo, "%d %.2f %.2f %.2f %s\n", L->A[i].matricula, L->A[i].nota1, L->A[i].nota2, L->A[i].nota3, L->A[i].nome);
        i++;
    }
    fclose(arquivo);
    return 1;
}

//Inicia a lista, ajusta o numero de elementos igual a 0
void Iniciar(Lista *L){
    L->nelem = 0;
}

//Verifica se a lista esta vazia
//Retorna 1 se a lista esta vazia
//Retorna 0 se a lista nao esta vazia
int Vazia(Lista *L){
    return (L->nelem == 0);
}

//Verifica se a lista esta cheia
//Retorna 1 se a lista esta cheia
//Retorna 0 se a lista nao esta cheia
int Cheia(Lista *L){
    return (L->nelem == MAX);
}

//Retorna o tamanho da lista (ou seja, o numero de elementos)
int Tamanho(Lista *L){
    return (L->nelem);
}

//Verifica se a matricula a ser cadastrada ja esta em uso
//Retorna 1 caso a matricula digitada ja exista
//Retorna 0 caso a matricula esteja disponivel para uso
int Verificar_Chave(Lista *L, int chave){
    int i;
    if(Vazia(L))
        return 0;
    for(i = 0; i < L->nelem; i++){
        if(L->A[i].matricula == chave)
            return 1;
    }
    return 0;
}

// Inserir aluno;
//Insere um novo aluno no inicio da lista
//Retorna 0 se o aluno nao pode ser inserido
//Retorna 1 se o aluno foi inserido com sucesso
int Inserir_Aluno_Inicio(Lista *L, tipo_elem v){
    int i;
    if(Cheia(L))
        return 0;
    for(i = L->nelem; i > 0; i--){
        L->A[i] = L->A[i-1];
    }
    L->A[0] = v;
    L->nelem++;
    return 1;
}

//Funcao auxiliar, insere um novo aluno no final da lista
//Retorna 0 se nao pode inserir o aluno na lista
//Retorna 1 se o aluno foi inserido com sucesso
int Inserir_Aluno_Final(Lista *L, tipo_elem v){
    if(Cheia(L))
        return 0;
    L->A[L->nelem] = v;
    L->nelem++;
    return 1;
}

//Insere um novo aluno na lista ordenando pela matricula
//Retorna 0 se a lista esta cheia e nao se pode mais inserir novos elementos
int Inserir_Aluno_Ordenado(Lista *L, tipo_elem v){
    int i;
    if(Cheia(L))
        return 0;
    if(Verificar_Ordem(L) == 1){//lista esta em ordem decrescente
        while(i < L->nelem && v.matricula < L->A[i].matricula){
            i++;
        }
    }else if(Verificar_Ordem(L) == 2){//lista esta em ordem crescente
        while(i < L->nelem && v.matricula > L->A[i].matricula){
            i++;
        }
    }
    return Inserir_Aluno_Apos(L, v, i);
}

//Funcao auxiliar para inserir um novo aluno na lista
//Retorna 0 se a lista esta cheia e nao se pode inserir novos alunos
//Retorna 1 se o novo aluno foi inserido com sucesso
int Inserir_Aluno_Apos(Lista *L, tipo_elem v, int k){
    int i;
    if(Cheia(L))
        return 0;
    for(i = L->nelem; i > k; i--){
        L->A[i] = L->A[i-1];
    }
    L->A[k] = v;
    L->nelem++;
    return 1;
}

// Remover aluno
//Retorna 0 se o aluno nao pode ser removido
//Retorna 1 se o aluno foi removido com sucesso
int Remover_Aluno(Lista *L, int chave){
    int i;
    if(Vazia(L))
        return 0;
    for(i = 0; i < L->nelem; i++){
        if(L->A[i].matricula == chave)
            break;
    }
    if(i == L->nelem)
        return 0;
    while(i < L->nelem-1){
        L->A[i] = L->A[i+1];
        i++;
    }
    L->nelem--;
    return 1;
}

// Alterar cadastro do aluno
//Retorna 1 se o cadastro do aluno foi alterado com sucesso
//Retorna 0 se nao foi possivel fazer a alteracao
int Alterar_Cadastro(Lista *L, tipo_elem v, int k){
    int i;
    for(i = 0; i < L->nelem; i++){
        if(L->A[i].matricula == k){
            if(strcmp(v.nome, " ") != 0)
                strcpy(L->A[i].nome, v.nome);
            if(v.matricula != -1)
                L->A[i].matricula = v.matricula;
            if(v.nota1 != -1)
                L->A[i].nota1 = v.nota1;
            if(v.nota2 != -1)
                L->A[i].nota2 = v.nota2;
            if(v.nota3 != -1)
                L->A[i].nota3 = v.nota3;
            return 1;
        }
    }
    return 0;
}

// Excluir a lista
//Atribui 0 a todos os atributos numericos (notas e matricula) e atribui espaco-em-branco ao atributo nome
//Numero de elementos no final da execucao do procedimento e igual a 0
void Excluir_Lista(Lista *L){
    while(L->nelem > 0){
        L->A[L->nelem-1].matricula = 0;
        strcpy(L->A[L->nelem-1].nome, " ");
        L->A[L->nelem-1].nota1 = 0.0;
        L->A[L->nelem-1].nota2 = 0.0;
        L->A[L->nelem-1].nota3 = 0.0;
        L->nelem--;
    }
}

// Buscar dados de um aluno, fornecendo o numero de matricula
//Retorna 0 se nao pode encontrar o aluno
//Retorna 1 se o aluno foi encontrado e se seus dados foram exibidos
int Buscar_Aluno(Lista *L, int chave){
    int i;
    if(Vazia(L))
        return 0;
    for(i = 0; i < L->nelem; i++){
        if(L->A[i].matricula == chave){
            printf("\nALUNO(A) ENCONTRADO(A)\n");
            printf("- Matricula: %d\n", L->A[i].matricula);
            printf("- Nome: %s\n", L->A[i].nome);
            printf("- Nota 1: %.2f\n", L->A[i].nota1);
            printf("- Nota 2: %.2f\n", L->A[i].nota2);
            printf("- Nota 3: %.2f\n", L->A[i].nota3);
            return 1;
        }
    }
    return 0;
}

// Exibir todos os dados de todos os alunos
void Exibir_Tudo(Lista *L){
    int i;
    if(Vazia(L))
        printf("Nao ha elementos na lista\n");
    for(i = 0; i < L->nelem; i++){
        printf("%d - %s - %.2f, %.2f, %.2f\n", L->A[i].matricula, L->A[i].nome, L->A[i].nota1, L->A[i].nota2, L->A[i].nota3);
    }
}

// Encontrar o aluno com maior nota da primeira prova
void Maior_Nota1(Lista *L){
    int i;
    float maior_nota;
    maior_nota = L->A[0].nota1;
    for(i = 0; i < L->nelem; i++){
        if(L->A[i].nota1 > maior_nota)
            maior_nota = L->A[i].nota1;
    }
    printf("\nMAIOR NOTA:\n");
    for(i = 0; i < L->nelem; i++){
        if(L->A[i].nota1 == maior_nota){
            printf("- (%d) %s tirou %.2f na primeira prova\n", L->A[i].matricula, L->A[i].nome, L->A[i].nota1);
        }
    }
}

// Encontrar aluno com maior média geral
void Maior_Media(Lista *L){
    int i;
    float maior_media, med_atual;
    maior_media = (L->A[0].nota1 + L->A[0].nota2 + L->A[0].nota3) / 3;
    for(i = 0; i < L->nelem; i++){
        med_atual = (L->A[i].nota1 + L->A[i].nota2 + L->A[i].nota3) / 3;
        if(med_atual > maior_media)
            maior_media = med_atual;
    }
    printf("\nMAIOR MEDIA:\n");
    for(i = 0; i < L->nelem; i++){
        med_atual = (L->A[i].nota1 + L->A[i].nota2 + L->A[i].nota3) / 3;
        if(med_atual == maior_media){
            printf("- (%d) %s teve media %.2f\n", L->A[i].matricula, L->A[i], med_atual);
        }
    }
}

// Encontrar aluno com menor média geral
void Menor_Media(Lista *L){
    int i;
    float menor_media, med_atual;
    menor_media = (L->A[0].nota1 + L->A[0].nota2 + L->A[0].nota3) / 3;
    for(i = 0; i < L->nelem; i++){
        med_atual = (L->A[i].nota1 + L->A[i].nota2 + L->A[i].nota3) / 3;
        if(med_atual < menor_media)
            menor_media = med_atual;
    }
    printf("\nMENOR MEDIA:\n");
    for(i = 0; i < L->nelem; i++){
        med_atual = (L->A[i].nota1 + L->A[i].nota2 + L->A[i].nota3) / 3;
        if(med_atual == menor_media){
            printf("- (%d) %s teve media %.2f\n", L->A[i].matricula, L->A[i].nome, med_atual);
        }
    }
}

//j) Listar os alunos aprovados e reprovados, considerando o valor 6 para aprovação
void Listar_Situacao(Lista *L){
    int i;
    float med_atual;
    printf("\nALUNOS APROVADOS:\n");
    for(i = 0; i < L->nelem; i++){
        med_atual = (L->A[i].nota1 + L->A[i].nota2 + L->A[i].nota3) / 3;
        if(med_atual >= 6.0){
            printf("- (%d) %s teve media: %.2f\n", L->A[i].matricula, L->A[i].nome, med_atual);
        }
    }
    printf("\nALUNOS REPROVADOS:\n");
    for(i = 0; i < L->nelem; i++){
        med_atual = (L->A[i].nota1 + L->A[i].nota2 + L->A[i].nota3) / 3;
        if(med_atual < 6.0){
            printf("- (%d) %s teve media: %.2f\n", L->A[i].matricula, L->A[i].nome, med_atual);
        }
    }
}

// Verificar se a lista está ordenada ou não (a ordem pode ser crescente ou decrescente)
//Retorna 1 se a lista esta em ordem DECRESCENTE
//Retorna 2 se a lista esta em ordem CRESCENTE
//Retorna 3 se a lista esta tem apenas 1 elemento
//Retorna 0 se a lista esta desordenada
int Verificar_Ordem(Lista *L){
    int i = 0;
    //se a lista esta vazia, ela e tratada como uma lista em ordem decrescente (para fins de verificacao de ordem)
    if(L->nelem == 0)
        return 1;
    if(L->nelem == 1)
        return 3;
    while(i < L->nelem-1 && L->A[i].matricula < L->A[i+1].matricula)
        i++;
    if(i == L->nelem-1)
        return 2;
    i = 0;
    while(i < L->nelem-1 && L->A[i].matricula > L->A[i+1].matricula)
        i++;
    if(i == L->nelem-1)
        return 1;
    return 0;
}

// Fazer uma cópia da lista L1 em uma outra lista L2;
//Retorna 1 se a lista L1 foi copiada para L2 com sucesso
//Retorna 0 se a lista nao pode ser copiada, porque esta vazia
int Copia_Lista(Lista *L, Lista *L2){
    if(Vazia(L))
        return 0;
    int i;
    L2->nelem = L->nelem;
    for(i = 0; i < L2->nelem; i++){
        L2->A[i] = L->A[i];
    }
    return 1;
}

// Inverter uma lista L1 colocando o resultado em L2;
//Retorna 1 se a lista foi invertida com sucesso
//Retorna 0 se a lista nao pode ser invertida, porque esta vazia
int Inverter_Lista(Lista *L, Lista *L2){
    if(Vazia(L))
        return 0;
    int i;
    L2->nelem = L->nelem;
    for(i = 0; i < L2->nelem; i++){
        L2->A[i] = L->A[L2->nelem - i - 1];
    }
    return 1;
}

//n) Intercalar duas listas, L1 e L2, gerando uma lista L3. Considere que L1, L2 e L3 estão ordenadas.
//Retorna 0 se as listas nao puderam ser intercaladas
//Retorna 1 se as listas foram intercaladas com sucesso
int Intercalar_Listas(Lista *L1, Lista *L2, Lista *L3){
    if(L1->nelem + L2->nelem > MAX)
        return 0;
    int a = 0, b = 0, c = 0;

    if(Verificar_Ordem(L1) == 2 && Verificar_Ordem(L1) == Verificar_Ordem(L2)){//listas em ordem crescente
        while(a < L1->nelem && b < L2->nelem){
            //esse if evita que elementos repetidos sejam postos na lista intercalada
            if(L1->A[a].matricula != L2->A[b].matricula){
                //esse if garante que os elementos vao ser dispostos em ordem crescente
                if(L1->A[a].matricula < L2->A[b].matricula){
                    L3->A[c] = L1->A[a];
                    a++;
                }else{
                    L3->A[c] = L2->A[b];
                    b++;
                }
                c++;
                L3->nelem++;
            }else{
                a++;
            }
        }
        while(a < L1->nelem){
            L3->A[c] = L1->A[a];
            c++;
            a++;
            L3->nelem++;
        }
        while(b < L2->nelem){
            L3->A[c] = L2->A[b];
            c++;
            b++;
            L3->nelem++;
        }
        return 1;
    }//fim do if que confere se as listas estao em ordem crescente

    if(Verificar_Ordem(L1) == 1 && Verificar_Ordem(L1) == Verificar_Ordem(L2)){//listas em ordem decrescente
        while(a < L1->nelem && b < L2->nelem){
            //esse if evita que elementos repetidos sejam postos na lista intercalada
            if(L1->A[a].matricula != L2->A[b].matricula){
                //esse if garante que os elementos vao ser dispostos em ordem decrescente
                if(L1->A[a].matricula > L2->A[b].matricula){
                    L3->A[c] = L1->A[a];
                    a++;
                }else{
                    L3->A[c] = L2->A[b];
                    b++;
                }
                c++;
                L3->nelem++;
            }else{
                a++;
            }
        }
        while(a < L1->nelem){
            L3->A[c] = L1->A[a];
            c++;
            a++;
            L3->nelem++;
        }
        while(b < L2->nelem){
            L3->A[c] = L2->A[b];
            c++;
            b++;
            L3->nelem++;
        }
        return 1;
    }//fim do if que confere se as listas estao em ordem decrescente

    if(Verificar_Ordem(L1) == 1 && Verificar_Ordem(L2) == 2){//lista 1 em ordem decrescente e lista 2 em ordem crescente
        while(a < L1->nelem && b < L2->nelem){
            //esse if evita que elementos repetidos sejam postos na lista intercalada
            if(L1->A[L1->nelem-a-1].matricula != L2->A[b].matricula){
                //esse if garante que os elementos vao ser dispostos em ordem decrescente
                if(L1->A[L1->nelem-a-1].matricula < L2->A[b].matricula){
                    L3->A[c] = L1->A[L1->nelem-a-1];
                    a++;
                }else{
                    L3->A[c] = L2->A[b];
                    b++;
                }
                c++;
                L3->nelem++;
            }else{
                a++;
            }
        }
        while(a < L1->nelem){
            L3->A[c] = L1->A[L1->nelem-a-1];
            c++;
            a++;
            L3->nelem++;
        }
        while(b < L2->nelem){
            L3->A[c] = L2->A[b];
            c++;
            b++;
            L3->nelem++;
        }
        return 1;
    }//fim do if que confere quando uma lista esta em ordem decrescente e a segunda esta em ordem crescente

    if(Verificar_Ordem(L1) == 2 && Verificar_Ordem(L2) == 1){//lista 1 em ordem crescente e lista 2 em ordem decrescente
        while(a < L1->nelem && b < L2->nelem){
            //esse if evita que elementos repetidos sejam postos na lista intercalada
            if(L1->A[a].matricula != L2->A[L2->nelem-b-1].matricula){
                //esse if garante que os elementos vao ser dispostos em ordem decrescente
                if(L1->A[a].matricula < L2->A[L2->nelem-b-1].matricula){
                    L3->A[c] = L1->A[a];
                    a++;
                }else{
                    L3->A[c] = L2->A[L2->nelem-b-1];
                    b++;
                }
                c++;
                L3->nelem++;
            }else{
                a++;
            }
        }
        while(a < L1->nelem){
            L3->A[c] = L1->A[a];
            c++;
            a++;
            L3->nelem++;
        }
        while(b < L2->nelem){
            L3->A[c] = L2->A[L2->nelem-b-1];
            c++;
            b++;
            L3->nelem++;
        }
        return 1;
    }

    //se em nenhum dos quatro if's anteriores foi possivel intercalar, retorna 0
    return 0;
}

   

