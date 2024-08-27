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

int main(){
    int opcao, aux1;
    tipo_elem v;
    char op;
    Lista L1, L2, L3, L4;

    Iniciar(&L1); //Lista principal
    Iniciar(&L2); //Lista copiada
    Iniciar(&L3); //Lista invertida
    Iniciar(&L4); //Lista intercalada
    if(Ler_Dados(&L1) == 0){
        printf("Nao foi possivel acessar o arquivo \"alunos.txt\". Por favor, certifique-se que ele foi\nsalvo na mesma pasta dos demais arquivos.\n");
        getchar();
    }

    do{
        system("cls");
        printf("\n*****************************- Lista Encadeada Dinamica -*******************************************");
        printf("\n 1 - Inserir novo aluno\n");
        printf(" 2 - Remover aluno da lista\n");
        printf(" 3 - Alterar cadastro de aluno\n");
        printf(" 4 - Excluir a lista\n");
        printf(" 5 - Buscar dados de um aluno\n");
        printf(" 6 - Exibir todos os alunos\n");
        printf(" 7 - Encontrar aluno com MAIOR nota da PRIMEIRA PROVA\n");
        printf(" 8 - Encontrar aluno com MAIOR MEDIA geral\n");
        printf(" 9 - Encontrar aluno com MENOR MEDIA geral\n");
        printf("10 - Listar alunos APROVADOS e REPROVADOS\n");
        printf("11 - Verificar se a LISTA esta ORDENADA ou nao\n");
        printf("12 - Fazer uma COPIA da lista\n");
        printf("13 - INVERTER uma lista\n");
        printf("14 - INTERCALAR duas listas\n");
        printf("15 - SAIR\n");
        printf("  Opcao: ");
        scanf("%d", &opcao);
        system("cls");
        switch(opcao){
            case 1:
                printf("\nCADASTRAR ALUNO (na lista principal)\n");
                printf("\nDeseja inserir o novo aluno em qual posicao:\n");
                printf("1 - Inicio da Lista\n");
                printf("2 - Final da Lista\n");
                printf("3 - Inserir ordenando (automaticamente) pela matricula\n");
                printf("  Opcao: ");
                scanf("%d", &aux1);
                //impede que o usuario digite uma entrada invalida
                while(aux1 > 3 || aux1 < 1){
                    printf("Digite uma opcao entre 1 e 3: ");
                    scanf("%d", &aux1);
                }
                if(aux1 == 3 && Verificar_Ordem(&L1) == 0){
                    printf("\nNao e possivel inserir ordenadamente, pois a lista esta desordenada\n");
                }else{
                    printf("\nDigite a matricula: ");
                    scanf("%d", &v.matricula);
                    while(Verificar_Chave(&L1, v.matricula)){
                        printf("Atencao. A matricula digitada ja esta em uso. Por favor, digite uma nova: ");
                        scanf("%d", &v.matricula);
                    }
                    printf("\nDigite o nome do aluno: ");
                    fflush(stdin);
                    gets(v.nome);
                    printf("\nDigite a nota 1: ");
                    scanf("%f", &v.nota1);
                    printf("\nDigite a nota 2: ");
                    scanf("%f", &v.nota2);
                    printf("\nDigite a nota 3: ");
                    scanf("%f", &v.nota3);
                    if(aux1 == 1){
                        if(Inserir_Aluno_Inicio(&L1, v))
                            printf("\nAluno inserido no INICIO da lista com sucesso\n");
                        else
                            printf("\nAluno nao pode ser inserido\n");
                    }else if(aux1 == 2){
                        if(Inserir_Aluno_Final(&L1, v))
                            printf("\nAluno inserido no FINAL da lista com sucesso\n");
                        else
                            printf("\nAluno nao pode ser inserido\n");
                    }else if(aux1 == 3){
                        if(Inserir_Aluno_Ordenado(&L1, v))
                            printf("\nAluno inserido ORDENADAMENTE com sucesso\n");
                        else
                            printf("\nAluno nao pode ser inserido\n");
                    }
                }
                if(!Gravar_Dados(&L1))
                    printf("Nao foi possivel gravar os dados num arquivo texto.\nPor favor, certifique-se que \"alunos.txt\" esta salvo na mesma pasta que os demais arquivos");
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 2:
                printf("\nREMOVER ALUNO (da lista principal)\n");
                if(Vazia(&L1))
                    printf("A lista esta vazia. Nao e possivel remover elementos\n");
                else{
                    printf("Digite a matricula do aluno a ser removido: ");
                    scanf("%d", &aux1);
                    if(Remover_Aluno(&L1, aux1))
                        printf("Aluno removido com sucesso\n");
                    else
                        printf("A matricula inserida nao existe na lista\n");
                }
                if(!Gravar_Dados(&L1))
                    printf("Nao foi possivel gravar os dados num arquivo texto.\nPor favor, certifique-se que \"alunos.txt\" esta salvo na mesma pasta que os demais arquivos");
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 3:
                v.nota1 = v.nota2 = v.nota3 = -1;
                v.matricula = -1;
                strcpy(v.nome, " ");
                printf("\nALTERAR DADOS DE ALUNO (na lista principal)\n");
                if(Vazia(&L1))
                    printf("\nA lista esta vazia. Nao e possivel alterar cadastros\n");
                else{
                    printf("Digite a matricula do aluno a ter seus dados alterados: ");
                    scanf("%d", &aux1);
                    if(Verificar_Chave(&L1, aux1) == 0)
                        printf("A matricula inserida nao existe na lista\n");
                    else{
                        printf("\nDeseja alterar a matricula do aluno? [S/N]: ");
                        fflush(stdin);
                        scanf("%c", &op);
                        if(op == 's' || op == 'S'){
                            printf("Digite a nova matricula do aluno: ");
                            scanf("%d", &v.matricula);
                            while(Verificar_Chave(&L1, v.matricula)){
                                printf("A matricula digitada ja esta em uso. Por favor, digite uma nova: ");
                                scanf("%d", &v.matricula);
                            }
                        }
                        printf("\nDeseja alterar o nome do aluno? [S/N]: ");
                        fflush(stdin);
                        scanf("%c", &op);
                        if(op == 's' || op == 'S'){
                            printf("Digite o novo nome do aluno: ");
                            fflush(stdin);
                            gets(v.nome);
                        }
                        printf("\nDeseja alterar a nota 1 do aluno? [S/N]: ");
                        fflush(stdin);
                        scanf("%c", &op);
                        if(op == 's' || op == 'S'){
                            printf("Digite a nova nota 1 do aluno: ");
                            scanf("%f", &v.nota1);
                        }
                        printf("\nDeseja alterar a nota 2 do aluno? [S/N]: ");
                        fflush(stdin);
                        scanf("%c", &op);
                        if(op == 's' || op == 'S'){
                            printf("Digite a nova nota 2 do aluno: ");
                            scanf("%f", &v.nota2);
                        }
                        printf("\nDeseja alterar a nota 3 do aluno? [S/N]: ");
                        fflush(stdin);
                        scanf("%c", &op);
                        if(op == 's' || op == 'S'){
                            printf("Digite a nova nota 3 do aluno: ");
                            scanf("%f", &v.nota3);
                        }
                        if(Alterar_Cadastro(&L1, v, aux1))
                            printf("\nCadastro alterado com sucesso\n");
                        else
                            printf("\nNao foi encontrado(a) o(a) aluno(a) com a matricula informada\n");
                    }
                }
                if(!Gravar_Dados(&L1))
                    printf("Nao foi possivel gravar os dados num arquivo texto.\nPor favor, certifique-se que \"alunos.txt\" esta salvo na mesma pasta que os demais arquivos");
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 4:
                printf("\nQual lista deseja excluir?\n");
                printf("1 - Lista principal\n");
                printf("2 - Lista copiada\n");
                printf("3 - Lista invertida\n");
                printf("4 - Lista intercalada\n");
                printf(" Opcao: ");
                scanf("%d", &aux1);
                while(aux1 > 4 || aux1 < 1){
                    printf("Digite um valor entre 1 e 4: ");
                    scanf("%d", &aux1);
                }
                switch(aux1){
                    case 1:
                        Excluir_Lista(&L1);
                        if(!Gravar_Dados(&L1))
                            printf("Nao foi possivel gravar os dados num arquivo texto.\nPor favor, certifique-se que \"alunos.txt\" esta salvo na mesma pasta que os demais arquivos");
                        printf("Lista principal excluida com sucesso\n");
                        break;
                    case 2:
                        Excluir_Lista(&L2);
                        printf("Lista copiada excluida com sucesso\n");
                        break;
                    case 3:
                        Excluir_Lista(&L3);
                        printf("Lista invertida excluida com sucesso\n");
                        break;
                    case 4:
                        Excluir_Lista(&L4);
                        printf("Lista intercalada excluida com sucesso\n");
                        break;
                }
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 5:
                printf("\nBUSCAR DADOS DE UM ALUNO (na lista principal)\n");
                if(Vazia(&L1))
                    printf("A lista esta vazia. Nao e possivel buscar alunos\n");
                else{
                    printf("\nDigite a matricula do aluno a ser buscado: ");
                    scanf("%d", &aux1);
                    if(!Buscar_Aluno(&L1, aux1))
                        printf("A matricula informada nao existe\n");
                }
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 6:
                printf("\nEXIBIR TODOS OS ALUNOS\n");
                printf("\nLista Principal\n");
                Exibir_Tudo(&L1);
                printf("\nLista Copiada\n");
                Exibir_Tudo(&L2);
                printf("\nLista Invertida\n");
                Exibir_Tudo(&L3);
                printf("\nLista Intercalada\n");
                Exibir_Tudo(&L4);
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 7:
                if(Vazia(&L1))
                    printf("A Lista esta vazia\n");
                else
                    Maior_Nota1(&L1);
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 8:
                if(Vazia(&L1))
                    printf("A Lista esta vazia\n");
                else
                    Maior_Media(&L1);
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 9:
                if(Vazia(&L1))
                    printf("A Lista esta vazia\n");
                else
                    Menor_Media(&L1);
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 10:
                if(Vazia(&L1))
                    printf("A Lista esta vazia\n");
                else
                    Listar_Situacao(&L1);
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 11:
                if(Vazia(&L1))
                    printf("\nA lista principal esta vazia\n");
                else{
                    aux1 = Verificar_Ordem(&L1);
                    if (aux1 == 3) printf("\nA lista principal tem apenas 1 elemento\n");
                    else if(aux1 == 2) printf("\nA lista principal esta em ordem CRESCENTE\n");
                    else if(aux1 == 1) printf("\nA lista principal esta em ordem DECRESCENTE\n");
                    else if(aux1 == 0) printf("\nA lista principal NAO esta ORDENADA\n");
                }
                if(Vazia(&L2))
                    printf("A lista copiada esta vazia\n");
                else{
                    aux1 = Verificar_Ordem(&L2);
                    if (aux1 == 3) printf("A lista copiada tem apenas 1 elemento\n");
                    else if(aux1 == 2) printf("A lista copiada esta em ordem CRESCENTE\n");
                    else if(aux1 == 1) printf("A lista copiada esta em ordem DECRESCENTE\n");
                    else if(aux1 == 0) printf("A lista copiada NAO esta ORDENADA\n");
                }
                if(Vazia(&L3)) printf("A lista invertida esta vazia\n");
                else{
                    aux1 = Verificar_Ordem(&L3);
                    if (aux1 == 3) printf("A lista invertida tem apenas 1 elemento\n");
                    else if(aux1 == 2) printf("A lista invertida esta em ordem CRESCENTE\n");
                    else if(aux1 == 1) printf("A lista invertida esta em ordem DECRESCENTE\n");
                    else if(aux1 == 0) printf("A lista invertida NAO esta ORDENADA\n");
                }
                if(Vazia(&L4)) printf("A lista intercalada esta vazia\n");
                else{
                    aux1 = Verificar_Ordem(&L4);
                    if (aux1 == 3) printf("A lista intercalada tem apenas 1 elemento\n");
                    else if(aux1 == 2) printf("A lista intercalada esta em ordem CRESCENTE\n");
                    else if(aux1 == 1) printf("A lista intercalada esta em ordem DECRESCENTE\n");
                    else if(aux1 == 0) printf("A lista intercalada NAO esta ORDENADA\n");
                }
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 12:
                printf("\nQual lista deseja copiar?\n");
                printf("1 - Lista Principal\n");
                printf("2 - Lista Invertida\n");
                printf("3 - Lista Intercalada\n");
                printf("  Opcao: ");
                scanf("%d", &aux1);
                while(aux1 > 3 || aux1 < 1){
                    printf("\nDigite uma opcao entre 1 e 3: ");
                    scanf("%d", &aux1);
                }
                switch(aux1){
                    case 1:
                        if(Vazia(&L1))
                            printf("\nA Lista principal esta vazia. Nao e possivel copia-la\n");
                        else{
                            if(Copia_Lista(&L1, &L2))
                                printf("\nLista copiada com sucesso\n");
                            else
                                printf("\nNao foi possivel copiar a lista\n");
                        }
                        break;
                    case 2:
                        if(Vazia(&L3))
                            printf("\nA Lista invertida esta vazia. Nao e possivel copia-la\n");
                        else{
                            if(Copia_Lista(&L3, &L2))
                                printf("\nLista copiada com sucesso\n");
                            else
                                printf("\nNao foi possivel copiar a lista\n");
                        }
                        break;
                    case 3:
                        if(Vazia(&L4))
                            printf("\nA Lista intercalada esta vazia. Nao e possivel copia-la\n");
                        else{
                            if(Copia_Lista(&L4, &L2))
                                printf("\nLista copiada com sucesso\n");
                            else
                                printf("\nNao foi possivel copiar a lista\n");
                        }
                        break;
                }
                Exibir_Tudo(&L2);
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 13:
                if(Vazia(&L1))
                    printf("\nA lista principal esta vazia, nao e possivel aplicar inversao\n");
                else{
                    if(Inverter_Lista(&L1, &L3))
                        printf("\nLista invertida com sucesso\n");
                    else
                        printf("\nNao foi possivel inverter a lista\n");
                }
                Exibir_Tudo(&L3);
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
            case 14:
                printf("\nA lista INTERCALADA e formada pelas listas PRINCIPAL e COPIADA\n");
                if(Vazia(&L1) || Vazia(&L2))
                    printf("\nNao e possivel intercalar as listas, pois uma delas, ou as duas, esta vazia\n");
                else if(Verificar_Ordem(&L1) == 0 || Verificar_Ordem(&L2) == 0)
                    printf("\nNao e possivel intercalar as listas, pois uma delas, ou as duas, esta desordenada\n");
                else{
                    if(Intercalar_Listas(&L1, &L2, &L4))
                        printf("\nListas intercaladas com sucesso\n");
                    else
                        printf("\nNao foi possivel intercalar as listas\n");
                }
                Exibir_Tudo(&L4);
                printf("\nAperte uma tecla para retornar ao menu");
                getchar();
                getchar();
                break;
        }
    }while(opcao != 15);

    return 0;
}
