#ifndef LIVROS_H_INCLUDED
#define LIVROS_H_INCLUDED

int obterTamanholivro();
void inicializarVetorlivros();
int obterPosicaoVazialivros();
void cadastrarlivro();
void imprimirlivros();
//Usado para testes, alimenta valores no banco da livro
void debug_Alimentalivro();
void pesquisarPorNomeLivros();
void pesquisarPorSigla();
void alterarlivro();
int findlvroById(int id);
void excluirlivro();
void pesquisarlivro();

void gravarLivrosBD();
void carregarLivrosBD();

#endif // LIVROS_H_INCLUDED
