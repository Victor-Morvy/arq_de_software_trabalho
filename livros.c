#include "livros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 5

#define CID 5
#define CNOME 50
#define PUB 15
#define ISBN 15
#define OBS 500
#define EDITID 5

int const totalCharacter = CID + CNOME + PUB + ISBN + OBS + EDITID + 1;


//estrutura de livros
typedef struct{
	int id; //pk
	char nome[50]; //unique
	int publicacao; //unique
	int isbn; //unique
	char obs[500];
	int edi_id; //fk
} livro;

livro _livros[TAM];

//salva dados no banco de dados .txt
void gravarLivrosBD()
{
    FILE* arq;
    char proxLinha[1] = {"\n"};

    if((arq = fopen("table_livros.txt", "w")) == NULL){
        printf("Erro ao ler arquivo!\n");
        return;
    }

    for (int i = 0; i < TAM; i++)
    {
        fprintf(arq, "%05d", _livros[i].id);
        fprintf(arq, "%-50s", _livros[i].nome);
        fprintf(arq, "%015d", _livros[i].publicacao);
        fprintf(arq, "%015d", _livros[i].isbn);
        fprintf(arq, "%-500s", _livros[i].obs);
        fprintf(arq, "%05d", _livros[i].edi_id);
        fputc(proxLinha[0], arq);


    }
    printf("Livros salvo!\n");
    fclose(arq);

}

void carregarLivrosBD()
{
    FILE* arq;
    char proxLinha[1] = {"\n"};

    if((arq = fopen("table_livros.txt", "r")) == NULL){
        printf("Erro ao ler arquivo! Nao existe BD para Livros\n");
        return;
    }
    int i = 0;
    while(!feof(arq))
    {

        fscanf(arq, "%5d", &_livros[i].id);
        fgets(_livros[i].nome, 50, arq);
        fscanf(arq, "%15d%15d", &_livros[i].publicacao, &_livros[i].isbn);
        fgets(_livros[i].obs, 500, arq);
        fscanf(arq, "%d\n", &_livros[i].edi_id);
        i++;
    }
    printf("BD Livros carregado!\n");
    fclose(arq);

}

//obtem o tamanho do vetor _livros de forma dinâmica
int obterTamanholivro()
{
    int tamanho = sizeof(_livros) / sizeof(livro);
    return tamanho;

}

//inicializando vetor livros com id 0 e nome e sigla nulo
void inicializarVetorlivros()
{
    int i = 0;
    int tamvet = obterTamanholivro();

    for(i = 0; i <= tamvet; i++){
        _livros[i].id = 0;
        strcpy(_livros[i].nome, "NU");
    }
}

//obtendo posição vazia em vetor livros
int obterPosicaoVazialivros()
{
   int i = 0;
   int tamvet = obterTamanholivro();

   for(i = 0; i <= tamvet; i++)
   {
       if(_livros[i].id == 0)
        //DEBUG
        return i;
   }
   //retorna -1 caso não obter posição vazia
   return -1;
}

void cadastrarlivro()
{


    int tamvet = obterTamanholivro();
    int pos = obterPosicaoVazialivros();
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
            scanf("%d", &_livros[pos].id);
            if(_livros[pos].id <= 0)
                printf("\nErro! Entre com um valor maior que 0!\n");
            else
                break;
        }

        printf("Digite o nome: \n");
        fflush(stdin);
        gets(_livros[pos].nome);

        printf("Digite a publicacao: \n");
        scanf("%d", &_livros[pos].publicacao);

        printf("Digite o isbn: \n");
        scanf("%d", &_livros[pos].isbn);

        printf("Digite o id de uma editora existente: \n");
        scanf("%d", &_livros[pos].edi_id);

        printf("Digite uma observacao: \n");
        fflush(stdin);
        gets(_livros[pos].obs);

        printf("\nCadastrado com sucesso!\n");
    }
}

void imprimirlivros()
{


    int existeDb = obterPosicaoVazialivros();
    int tamDb = obterTamanholivro();

    if(existeDb == -1)
        printf("\nNão há registros no banco de dados para imprimir!\n");
    else
    {
        for(int i = 0; i <= tamDb; i++)
        {
            if(_livros[i].id != 0)
                printf("id: %d | cod: %d | nome: %s | pub.: %d | isbn: %d | edit_id: %d | Obs.: %s\n", i, _livros[i].id, _livros[i].nome, _livros[i].publicacao, _livros[i].isbn, _livros[i].edi_id, _livros[i].obs);
        }
    }
}

//Usado para testes, alimenta valores no banco da livro
void debug_Alimentalivro(){
    _livros[0].id = 1;
    strcpy(_livros[0].nome, "as dasd asd");
    strcpy(_livros[0].obs, "asd asd  qualquer");

    _livros[1].id = 3;
    strcpy(_livros[1].nome, "asd asd asd asd asd");
    strcpy(_livros[1].obs, "asd asd asd  qualsdaasquer");

    _livros[3].id = 4;
    strcpy(_livros[3].nome, "oxe asd asd asd ");
    strcpy(_livros[3].obs, "ads sad asda qualsdaasquer");

    printf("\n--deBug: Vetor _livros alimentada!--\n");

}
//////////////////////////////////////////////////////////


//Pesquisar livro por nome
void pesquisarPorNomeLivros()
{
    int i = 0;
    int tamVet = obterTamanholivro();
    char valDigitado[50];
    int achou = 0;

    fflush(stdout);

    printf("\nDigite o nome que deseja pesquisar: ");
    fflush(stdin);
    gets(valDigitado);

    printf("\nResultado da pesquisa:\n");
    for(i = 0; i <= tamVet; i++)
    {
        if(strstr(_livros[i].nome, valDigitado))
        {
            printf("id: %d | cod: %d | nome: %s | pub.: %d | isbn: %d | edit_id: %d | Obs.: %s\n", i, _livros[i].id, _livros[i].nome, _livros[i].publicacao, _livros[i].isbn, _livros[i].edi_id, _livros[i].obs);
            achou = 1;
        }
    }

    if(!achou)
        printf("Nenhum resultado encontrado...\n");

    if(obterPosicaoVazialivros() == -1)
        printf("Nao ha registros no banco...\n");
}


int findlvroById(int id)
{
    int tamVet = obterTamanholivro();
    for (int i = 0; i <= tamVet; i++)
    {
       if (_livros[i].id == id && _livros[i].id > 0)
       {
           //printf("EXISTE!");
            return i;

       }


    }
    //printf("NAO EXISTE!!");
    return -1;

}

//altera o nome da livro de uma determinada id
void alterarlivro()
{
//ff //para retornar erro e achar quando compilar
    int tamVet = obterTamanholivro();
    printf("Digite o codigo do livro\n");
    int edID;
    scanf("%d", &edID);

        if(edID > 0 && findlvroById(edID) >= 0)//sucesso!
        {
            int campoInt;

            //////////////////CAMPO NOME
            printf("\nO campo de Nome atual e: %s\n", _livros[edID].nome);
            printf("Novo nome? ([-1] para o mesmo):\n");
            char campoNome[50];
            fflush(stdin);
            gets(campoNome);

            if (strcmp(campoNome, "-1") != 0)
            {
                strcpy(_livros[edID].nome, campoNome);

            }

            //////////////CAMPO PUBLICACAO
            printf("\nO campo de publicacao e: %d\n", _livros[edID].publicacao);
            printf("Nova publicacao? ([-1] para o mesmo):\n");
            scanf("%d", &campoInt);

            if (campoInt != -1)
                _livros[edID].publicacao = campoInt;

            //////////////CAMPO isbn
            printf("\nO campo ISBN e: %d\n", _livros[edID].isbn);
            printf("Novo numero isbn? ([-1] para o mesmo):\n");
            scanf("%d", &campoInt);

            if (campoInt != -1)
                _livros[edID].isbn = campoInt;

            //////////////CAMPO isbn
            printf("\nO campo id_editora e: %d\n", _livros[edID].edi_id);
            printf("Nova editora? ([-1] para o mesmo):\n");
            scanf("%d", &campoInt);

            if (campoInt != -1)
                _livros[edID].isbn = campoInt;

            /////////////////////CAMPO OBS
            printf("\nO campo de Obs. atual e: %s\n", _livros[edID].obs);
            printf("Nova observacao? ([-1] para o mesmo):\n");
            char camposObs[500];
            fflush(stdin);
            gets(camposObs);

            if (strcmp(camposObs, "-1") != 0)
            {
                strcpy(_livros[edID].obs, camposObs);

            }



            printf("Alteracoes salvas!\n");


        }
        else
        {
        printf("Nao existe!!");
        }


}



void excluirlivro()
{
        printf("Escolha qual excluir: \n");
        imprimirlivros();
        printf("Digite o codigo: ");
        int idOpc;
        scanf("%d", &idOpc);
        int idBanco = findlvroById(idOpc);
        if(idOpc > 0 && idBanco >= 0)//sucesso!
        {

            _livros[idBanco].id = 0;
            strcpy(_livros[idBanco].nome, "NU");
        }
        else
        {
            printf("Nao Existe!\n");
        }
}

void pesquisarlivro()
{
    pesquisarPorNomeLivros();

}

