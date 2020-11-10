#ifndef AUTORES_H_INCLUDED
#define AUTORES_H_INCLUDED

int obterTamanhoautor();
void inicializarVetorautores();
int obterPosicaoVaziaautores();
void cadastrarautor();
void imprimirautores();
//Usado para testes, alimenta valores no banco da autor
void debug_Alimentaautor();
void pesquisarPorNomeAutores();
void pesquisarPorSigla();
void alterarautor();
int findautorsById(int id);
void excluirautor();
void pesquisarautor();


void gravarAutoresBD();
void carregarAutoresBD();


#endif // AUTORES_H_INCLUDED
