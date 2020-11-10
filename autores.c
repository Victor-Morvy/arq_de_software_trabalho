#include "autores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 5
//estrutura de autores
typedef struct{
	int id; //pk
	char nome[50]; //unique
	char dominio[50]; //unique
	char obs[500];
} autor;

autor _autores[TAM];



//////////////////////
//salva dados no banco de dados .txt
void gravarAutoresBD()
{
    FILE* arq;
    char proxLinha[1] = {"\n"};

    if((arq = fopen("table_autores.txt", "w")) == NULL){
        printf("Erro ao ler arquivo!\n");
        return;
    }

    for (int i = 0; i < TAM; i++)
    {
        fprintf(arq, "%05d", _autores[i].id);
        fprintf(arq, "%-50s", _autores[i].nome);
        fprintf(arq, "%-50s", _autores[i].dominio);
        fprintf(arq, "%-500s", _autores[i].obs);
        fputc(proxLinha[0], arq);


    }
    printf("autores salvo!\n");
    fclose(arq);

}

void carregarAutoresBD()
{
    FILE* arq;
    char proxLinha[1] = {"\n"};

    if((arq = fopen("table_autores.txt", "r")) == NULL){
        printf("Erro ao ler arquivo! Nao existe BD para Autores\n");
        return;
    }
    int i = 0;
    while( i < TAM)
    {

        fscanf(arq, "%5d", &_autores[i].id);
        fgets(_autores[i].nome, 50, arq);
        fgets(_autores[i].dominio, 50, arq);
        fgets(_autores[i].obs, 500, arq);
        fscanf(arq, "\n");
        i++;
    }
    printf("BD Autores carregado!\n");
    fclose(arq);

}


////////////////////

//obtem o tamanho do vetor _autores de forma dinâmica
int obterTamanhoautor()
{
    int tamanho = sizeof(_autores) / sizeof(autor);
    return tamanho;

}

//inicializando vetor autores com id 0 e nome e sigla nulo
void inicializarVetorautores()
{
    int i = 0;
    int tamvet = obterTamanhoautor();

    for(i = 0; i <= tamvet; i++){
        _autores[i].id = 0;
        strcpy(_autores[i].nome, "NU");
    }
}

//obtendo posição vazia em vetor autores
int obterPosicaoVaziaautores()
{
   int i = 0;
   int tamvet = obterTamanhoautor();

   for(i = 0; i <= tamvet; i++)
   {
       if(_autores[i].id == 0)
        //DEBUG
        return i;
   }
   //retorna -1 caso não obter posição vazia
   return -1;
}

void cadastrarautor()
{
    int tamvet = obterTamanhoautor();
    int pos = obterPosicaoVaziaautores();
    //DEBUG
    //printf("\n\nPOSICAO: %d\n\n", pos);

    if(pos == -1)
        printf("\nBase de dados cheia!\n");
    else
    {
        fflush(stdout);
        while(1)
        {
            printf("\nDigite o codigo: \n");

            scanf("%d", &_autores[pos].id);
            if(_autores[pos].id <= 0)
                printf("\nErro! Entre com um valor maior que 0!\n");
            else
                break;
        }

        printf("Digite o nome: \n");
        fflush(stdin);
        gets(_autores[pos].nome);

        printf("Digite o dominio: \n");
        fflush(stdin);
        gets(_autores[pos].dominio);

        printf("Digite uma observacao: \n");
        fflush(stdin);
        gets(_autores[pos].obs);

        printf("\n\nCadastrado com sucesso!");
    }
}

void imprimirautores()
{
    int existeDb = obterPosicaoVaziaautores();
    int tamDb = obterTamanhoautor();

    if(existeDb == -1)
        printf("\nNão há registros no banco de dados para imprimir!\n");
    else
    {
        for(int i = 0; i <= tamDb; i++)
        {
            if(_autores[i].id != 0)
                printf("id: %d | cod: %d | nome: %s | dominio: %s | Obs.: %s\n", i, _autores[i].id, _autores[i].nome, _autores[i].dominio, _autores[i].obs);
        }
    }
}

//Usado para testes, alimenta valores no banco da autor
void debug_Alimentaautor(){
    _autores[0].id = 1;
    strcpy(_autores[0].nome, "oxi 1");
    strcpy(_autores[0].obs, "Observacao qualquer");

    _autores[1].id = 3;
    strcpy(_autores[1].nome, "maquecosa");
    strcpy(_autores[1].obs, "Observacao qualsdaasquer");

    _autores[3].id = 4;
    strcpy(_autores[3].nome, "oxe gente");
    strcpy(_autores[3].obs, "Observasdaasddcao qualsdaasquer");

    printf("\n--deBug: Vetor _autores alimentada!--\n");

}
//////////////////////////////////////////////////////////




//Pesquisar autor por nome
void pesquisarPorNomeAutores()
{
    int i = 0;
    int tamVet = obterTamanhoautor();
    char valDigitado[50];
    int achou = 0;

    fflush(stdout);

    printf("\nDigite o nome que deseja pesquisar: ");
    fflush(stdin);
    gets(valDigitado);

    printf("\nResultado da pesquisa:\n");
    for(i = 0; i <= tamVet; i++)
    {
        if(strstr(_autores[i].nome, valDigitado))
        {
            printf("id: %d | cod: %d | nome: %s | dominio: %s | Obs.: %s\n", i, _autores[i].id, _autores[i].nome, _autores[i].dominio, _autores[i].obs);
            achou = 1;
        }
    }

    if(!achou)
        printf("Nenhum resultado encontrado...\n");

    if(obterPosicaoVaziaautores() == -1)
        printf("Nao ha registros no banco...\n");
}


//altera o nome da autor de uma determinada id
void alterarautor()
{
//ff //para retornar erro e achar quando compilar
    int tamVet = obterTamanhoautor();
    printf("Digite o codigo do autor\n");
    int edID;
    scanf("%d", &edID);

        if(edID > 0 && findautorsById(edID) >= 0)//sucesso!
        {
            /////////nome
            printf("\nO campo de Nome atual e: %s\n", _autores[edID].nome);
            printf("Novo nome? ([-1] para o mesmo):\n");
            char campoNome[50];
            fflush(stdin);
            gets(campoNome);

            if (strcmp(campoNome, "-1") != 0)
            {
                strcpy(_autores[edID].nome, campoNome);

            }

            /////////////dominio
            printf("\nO campo de dominio atual e: %s\n", _autores[edID].dominio);
            printf("Novo dominio? ([-1] para o mesmo):\n");
            fflush(stdin);
            gets(campoNome);

            if (strcmp(campoNome, "-1") != 0)
            {
                strcpy(_autores[edID].dominio, campoNome);

            }

            /////////////obs

            printf("\nO campo de Obs. atual e: %s\n", _autores[edID].obs);
            printf("Nova observacao? ([-1] para o mesmo):\n");
            char camposObs[500];
            fflush(stdin);
            gets(camposObs);

            if (strcmp(camposObs, "-1") != 0)
            {
                strcpy(_autores[edID].obs, camposObs);

            }
            fflush(stdin);
            printf("Alteracoes salvas!\n");


        }
        else
        {
        printf("Nao existe!!");
        }


}

int findautorsById(int id)
{
    int tamVet = obterTamanhoautor();
    for (int i = 0; i <= tamVet; i++)
    {
       if (_autores[i].id == id && _autores[i].id > 0)
       {
           //printf("EXISTE!");
            return i;

       }


    }
    //printf("NAO EXISTE!!");
    return -1;

}

void excluirautor()
{
        printf("Escolha qual excluir: \n");
        imprimirautores();
        printf("Digite o codigo: ");
        int idOpc;
        scanf("%d", &idOpc);
        int idBanco = findautorsById(idOpc);
        if(idOpc > 0 && idBanco >= 0)//sucesso!
        {

            _autores[idBanco].id = 0;
            strcpy(_autores[idBanco].nome, "NU");
        }
        else
        {
            printf("Nao Existe!\n");
        }
}

void pesquisarautor()
{
    pesquisarPorNomeAutores();

}

