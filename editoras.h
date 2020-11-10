#ifndef EDITORA_H_INCLUDED
#define EDITORA_H_INCLUDED

int obterTamanhoEditora();
void inicializarVetorEditoras();
int obterPosicaoVaziaEditoras();
void cadastrarEditora();
void imprimirEditoras();
//Usado para testes, alimenta valores no banco da Editora
void debug_AlimentaEditora();

void pesquisarPorNomeEditora();
void pesquisarPorSigla();
void alterarEditora();
int findEdtraById(int id);
void excluirEditora();
void pesquisarEditora();

void gravarEditorasBD();
void carregareditorasBD();

#endif // EDITORA_H_INCLUDED
