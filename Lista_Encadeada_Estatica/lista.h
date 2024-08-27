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
#define MAX 100

//Tipo de dado
typedef struct{
    int matricula;
    char nome[30];
    float nota1, nota2, nota3;
}tipo_elem;

//Estrutura de dados
typedef struct{
    tipo_elem A[MAX];
    int nelem;
}Lista;

int Gravar_Dados(Lista *L);
int Ler_Dados(Lista *L);
//Operacoes
void Iniciar(Lista *L);
int Vazia(Lista *L);
int Cheia(Lista *L);
int Tamanho(Lista *L);
int Verificar_Chave(Lista *L, int chave);
int Ler_Dados(Lista *L);
//Grava, em um arquivo de texto chamado alunos.txt, todos os dados dos alunos da lista
int Gravar_Dados(Lista *L);
// Inserir aluno;
int Inserir_Aluno_Inicio(Lista *L, tipo_elem v);
int Inserir_Aluno_Final(Lista *L, tipo_elem v);
int Inserir_Aluno_Ordenado(Lista *L, tipo_elem v);
int Inserir_Aluno_Apos(Lista *L, tipo_elem v, int k);
// Remover aluno
int Remover_Aluno(Lista *L, int chave);
// Alterar cadastro do aluno
int Alterar_Cadastro(Lista *L, tipo_elem v, int k);
// Excluir a lista
void Excluir_Lista(Lista *L);
// Buscar dados de um aluno, fornecendo o dado de matricula
int Buscar_Aluno(Lista *L, int chave);
// Exibir todos os dados de todos os alunos
void Exibir_Tudo(Lista *L);
// Encontrar o aluno com maior nota da primeira prova
void Maior_Nota1(Lista *L);
// Encontrar aluno com maior média geral
void Maior_Media(Lista *L);
// Encontrar aluno com menor média geral
void Menor_Media(Lista *L);
// Listar os alunos aprovados e reprovados, considerando o valor 6 para aprovação
void Listar_Situacao(Lista *L);
//Verificar se a lista está ordenada ou não (a ordem pode ser crescente ou decrescente);
int Verificar_Ordem(Lista *L);
// Fazer uma cópia da lista L1 em uma outra lista L2;
int Copia_Lista(Lista *L, Lista *L2);
// Inverter uma lista L1 colocando o resultado em L2;
int Inverter_Lista(Lista *L, Lista *L2);
// Intercalar duas listas, L1 e L2, gerando uma lista L3. Considere que L1, L2 e L3 estão ordenadas.
int Intercalar_Listas(Lista *L1, Lista *L2, Lista *L3);
