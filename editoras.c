#include "editoras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 5
//estrutura de editoras
typedef struct{
    int id; //pk
    char nome[50]; //unique
    char sigla[25]; //unique
    char obs[500];
} editora;

//criando vetores
editora _editoras[TAM];


//////////////////////
//salva dados no banco de dados .txt
void gravarEditorasBD()
{
    FILE* arq;
    char proxLinha[1] = {"\n"};

    if((arq = fopen("table_editoras.txt", "w")) == NULL){
        printf("Erro ao ler arquivo!\n");
        return;
    }

    for (int i = 0; i < TAM; i++)
    {
        fprintf(arq, "%05d", _editoras[i].id);
        fprintf(arq, "%-50s", _editoras[i].nome);
        fprintf(arq, "%-25s", _editoras[i].sigla);
        fprintf(arq, "%-500s", _editoras[i].obs);
        fputc(proxLinha[0], arq);


    }
    printf("editoras salvo!\n");
    fclose(arq);

}

void carregareditorasBD()
{
    FILE* arq;
    char proxLinha[1] = {"\n"};

    if((arq = fopen("table_editoras.txt", "r")) == NULL){
        printf("Erro ao ler arquivo! Nao existe BD para Editoras\n");
        return;
    }
    int i = 0;
    while( i < TAM)
    {

        fscanf(arq, "%5d", &_editoras[i].id);
        fgets(_editoras[i].nome, 50, arq);
        fgets(_editoras[i].sigla, 25, arq);
        fgets(_editoras[i].obs, 500, arq);
        fscanf(arq, "\n");
        i++;
    }
    printf("BD Editoras carregado!\n");
    fclose(arq);

}


////////////////////


//obtem o tamanho do vetor _editoras de forma dinâmica
int obterTamanhoEditora()
{
    int tamanho = sizeof(_editoras) / sizeof(editora);
    return tamanho;

}

//inicializando vetor editoras com id 0 e nome e sigla nulo
void inicializarVetorEditoras()
{
    int i = 0;
    int tamvet = obterTamanhoEditora();

    for(i = 0; i <= tamvet; i++){
        _editoras[i].id = 0;
        strcpy(_editoras[i].nome, "NU");
        strcpy(_editoras[i].sigla, "NU");
        strcpy(_editoras[i].obs, "");
    }
}

//obtendo posição vazia em vetor editoras
int obterPosicaoVaziaEditoras()
{
   int i = 0;
   int tamvet = obterTamanhoEditora();

   for(i = 0; i <= tamvet; i++)
   {
       if(_editoras[i].id == 0)
        //DEBUG
        return i;
   }
   //retorna -1 caso não obter posição vazia
   return -1;
}

void cadastrarEditora()
{
    int tamvet = obterTamanhoEditora();
    int pos = obterPosicaoVaziaEditoras();
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
            scanf("%d", &_editoras[pos].id);
            if(_editoras[pos].id <= 0)
                printf("\nErro! Entre com um valor maior que 0!\n");
            else
                break;
        }

        printf("Digite o nome: \n");
        fflush(stdin);
        gets(_editoras[pos].nome);

        printf("Digite a sigla: \n");
        fflush(stdin);
        gets(_editoras[pos].sigla);

        printf("Digite uma observacao: \n");
        fflush(stdin);
        gets(_editoras[pos].obs);

        printf("\n\nCadastrado com sucesso!");
    }
}

void imprimirEditoras()
{
    int existeDb = obterPosicaoVaziaEditoras();
    int tamDb = obterTamanhoEditora();

    if(existeDb == -1)
        printf("\nNão há registros no banco de dados para imprimir!\n");
    else
    {
        for(int i = 0; i <= tamDb; i++)
        {
            if(_editoras[i].id != 0)
                printf("id: %d | codigo: %d | sigla: %s | nome: %s | Obs.: %s\n", i, _editoras[i].id, _editoras[i].sigla, _editoras[i].nome, _editoras[i].obs);
        }
    }
}

//Usado para testes, alimenta valores no banco da Editora
void debug_AlimentaEditora(){
    _editoras[0].id = 1;
    strcpy(_editoras[0].nome, "Teste 1");
    strcpy(_editoras[0].sigla, "te1");
    strcpy(_editoras[0].obs, "Observacao qualquer");

    _editoras[1].id = 3;
    strcpy(_editoras[1].nome, "o vaqueiro teste");
    strcpy(_editoras[1].sigla, "te2");
    strcpy(_editoras[1].obs, "Observacao qualsdaasquer");

    _editoras[3].id = 4;
    strcpy(_editoras[3].nome, "moises manchado tes");
    strcpy(_editoras[3].sigla, "te3 22");
    strcpy(_editoras[3].obs, "Observasdaasddcao qualsdaasquer");

    printf("\n--deBug: Vetor _editoras alimentada!--\n");

}
//////////////////////////////////////////////////////////




//Pesquisar editora por nome
void pesquisarPorNomeEditora()
{
    int i = 0;
    int tamVet = obterTamanhoEditora();
    char valDigitado[50];
    int achou = 0;

    fflush(stdout);

    printf("\nDigite o nome que deseja pesquisar: ");

    fflush(stdin);
    gets(valDigitado);

    printf("\nResultado da pesquisa:\n");
    for(i = 0; i <= tamVet; i++)
    {
        if(strstr(_editoras[i].nome, valDigitado))
        {
            printf("id: %d | codigo: %d | sigla: %s | nome: %s | Obs.: %s\n", i, _editoras[i].id, _editoras[i].sigla, _editoras[i].nome, _editoras[i].obs);
            achou = 1;
        }
    }

    if(!achou)
        printf("Nenhum resultado encontrado...\n");

    if(obterPosicaoVaziaEditoras() == -1)
        printf("Nao ha registros no banco...\n");
}

//Pesquisar editora por sigla
void pesquisarPorSigla()
{
    int i = 0;
    int tamVet = obterTamanhoEditora();
    char valDigitado[25];
    int achou = 0;

    fflush(stdout);

    printf("\nDigite o nome que deseja pesquisar: ");
    fflush(stdin);
    gets(valDigitado);

    printf("\nResultado da pesquisa:\n");
    for(i = 0; i <= tamVet; i++)
    {
        if(strstr(_editoras[i].sigla, valDigitado))
        {
            printf("id: %d | codigo: %d | sigla: %s | nome: %s | Obs.: %s\n", i, _editoras[i].id, _editoras[i].sigla, _editoras[i].nome, _editoras[i].obs);
            achou = 1;
        }
    }

    if(!achou)
        printf("Nenhum resultado encontrado...\n");

    if(obterPosicaoVaziaEditoras())
        printf("Nao ha registros no banco...\n");
}


//altera o nome da editora de uma determinada id
void alterarEditora()
{
//ff //para retornar erro e achar quando compilar
    int tamVet = obterTamanhoEditora();
    printf("Digite o codigo da editora\n");
    int edID;
    scanf("%d", &edID);

        if(edID > 0 && findEdtraById(edID) >= 0)//sucesso!
        {

            printf("\nO campo de Nome atual e: %s\n", _editoras[edID].nome);
            printf("Novo nome? ([-1] para o mesmo):\n");
            char campoNome[50];
            fflush(stdin);
            gets(campoNome);

            if (strcmp(campoNome, "-1") != 0)
            {
                strcpy(_editoras[edID].nome, campoNome);

            }
            printf("\nO campo de Sigla atual e: %s\n", _editoras[edID].sigla);
            printf("Nova sigla? ([-1] para o mesmo):\n");
            char campoSigla[25];
            fflush(stdin);
            gets(campoSigla);

            if (strcmp(campoSigla, "-1") != 0)
            {
                strcpy(_editoras[edID].sigla, campoSigla);

            }

            printf("\nO campo de Obs. atual e: %s\n", _editoras[edID].obs);
            printf("Nova observacao? ([-1] para o mesmo):\n");
            char camposObs[500];
            fflush(stdin);
            gets(camposObs);

            if (strcmp(camposObs, "-1") != 0)
            {
                strcpy(_editoras[edID].obs, camposObs);

            }
            fflush(stdin);
            printf("Alteracoes salvas!\n");


        }
        else
        {
        printf("Nao existe!!");
        }


}

int findEdtraById(int id)
{
    int tamVet = obterTamanhoEditora();
    for (int i = 0; i <= tamVet; i++)
    {
       if (_editoras[i].id == id && _editoras[i].id > 0)
       {
           //printf("EXISTE!");
            return i;

       }


    }
    //printf("NAO EXISTE!!");
    return -1;

}

void excluirEditora()
{
        printf("Escolha qual excluir: \n");
        imprimirEditoras();
        printf("Digite o codigo: ");
        int idOpc;
        scanf("%d", &idOpc);
        int idBanco = findEdtraById(idOpc);
        if(idOpc > 0 && idBanco >= 0)//sucesso!
        {

            _editoras[idBanco].id = 0;
            strcpy(_editoras[idBanco].nome, "NU");
            strcpy(_editoras[idBanco].sigla, "NU");
            strcpy(_editoras[idBanco].obs, "");
        }
        else
        {
            printf("Nao Existe!\n");
        }
}

void pesquisarEditora()
{
        int opMenu;

        printf("Voce deseja pesquisar por\n");
        printf("1.Nome\n");
        printf("2.Sigla\n");
        scanf("%d", &opMenu);

        if(opMenu == 1)
        {
            pesquisarPorNomeEditora();
        }else if(opMenu == 2)
        {
            pesquisarPorSigla();
        }else
        {
            printf("Por favor, insira um dado valido!\n");
        }
}

