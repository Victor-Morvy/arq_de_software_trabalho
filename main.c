#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "editoras.h"
#include "livros.h"
#include "autores.h"

//tamanho máximo dos vetores
#define TAM 5

//variáveis de controle de menu
int opc1 = -1, opc2 = -1;

//função para imprimir menu principal e suas pequenas funcionalidades de controle
void imprimeMenuPrincipal(){
    do{
        printf("\n.::MENU PRINCIPAL::.\n");
        printf("1. EDITORAS\n");
        printf("2. LIVROS\n");
        printf("3. AUTORES\n");
        printf("9. SAIR\n");
        printf("Digite a opcao desejada:\n");
        scanf("%d", &opc1);

        if(opc1 >= 1 && opc1 <= 3)
            imprimeSubMenu();
        else if(opc1 == 9)
            continue;
        else
            printf("\n!Digite uma opcao valida!.\n");
    }while(opc1 != 9);

    //reseta a opção 1 para o estado de -1;
    opc1 = -1;
}



//função para imprimir submenu e pequenas funcionalidades de controle
void imprimeSubMenu(){
    do{
        //definindo o título do submenu
        char subMenuStr[25];
        switch(opc1){
            case 1:
                strcpy(subMenuStr, "\n.::EDITORAS::.\n");
                break;
            case 2:
                strcpy(subMenuStr, "\n.::LIVROS::.\n");
                break;
            case 3:
                strcpy(subMenuStr, "\n.::AUTORES::.\n");
                break;
            default:
                strcpy(subMenuStr, "\nOCORREU UM ERRO!\n");
        }

        printf("%s", subMenuStr);
        printf("1. INSERIR\n");
        printf("2. ALTERAR\n");
        printf("3. EXCLUIR\n");
        printf("4. PESQUISAR\n");
        printf("5. IMPRIMIR TODOS\n");
        printf("9. SAIR PARA O MENU PRINCIPAL\n");
        printf("Digite a opcao desejada:\n");
        scanf("%d", &opc2);

        if(opc2 >= 1 && opc2 <= 5)
            subMenuControl();
        else if(opc2 == 9)
            continue;
        else
            printf("\n!Digite uma opcao valida!.\n");

    }while(opc2 != 9);

    //reseta a opção do submenu para o estado de -1
    //opc2 = -1;

}

//controle de submenu, com vetor apontado
void subMenuControl(){
    //Editoras
    if (opc1 == 1 && opc2 == 1){
        cadastrarEditora();
        gravarEditorasBD();
    }
    else if (opc1 == 1 && opc2 == 2)
    {

        alterarEditora();
        gravarEditorasBD();
    }

    else if (opc1 == 1 && opc2 == 3)
    {
        excluirEditora();
        gravarEditorasBD();
    }

    else if (opc1 == 1 && opc2 == 4)
    {
        pesquisarEditora();
    }
    else if (opc1 == 1 && opc2 == 5)
    {

        imprimirEditoras();
    }


    //Livros
    else if (opc1 == 2 && opc2 == 1)
    {
        printf("\n:::Teste:::n");
        cadastrarlivro();
        gravarLivrosBD();
    }
    else if (opc1 == 2 && opc2 == 2)
    {
        alterarlivro();
        gravarLivrosBD();
    }
    else if (opc1 == 2 && opc2 == 3)
    {
        excluirlivro();
        gravarLivrosBD();
    }
    else if (opc1 == 2 && opc2 == 4)
    {
        pesquisarlivro();
    }
    else if (opc1 == 2 && opc2 == 5)
    {
        imprimirlivros();

    }

    //Autores
    else if (opc1 == 3 && opc2 == 1)
    {
        cadastrarautor();
        gravarAutoresBD();
    }
    else if (opc1 == 3 && opc2 == 2)
    {
        alterarautor();
        gravarAutoresBD();
    }
    else if (opc1 == 3 && opc2 == 3)
    {
        excluirautor();
        gravarAutoresBD();
    }
    else if (opc1 == 3 && opc2 == 4)
    {
        pesquisarautor();
    }
    else if (opc1 == 3 && opc2 == 5)
    {
        imprimirautores();
    }
}

int main(int argc, char *argv[]) {
    inicializarVetorEditoras();
    inicializarVetorautores();
    inicializarVetorlivros();

    //debug_AlimentaEditora();
    //debug_Alimentalivro();
    //debug_Alimentaautor();

    //gravarLivrosBD();
    //gravarAutoresBD();
    //gravarEditorasBD();

    carregarLivrosBD();
    carregarAutoresBD();
    carregareditorasBD();

    imprimeMenuPrincipal();

	return 0;
}
